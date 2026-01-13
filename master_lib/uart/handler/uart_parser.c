#include <stdlib.h>
#include "uart_parser.h"
#include "uart/uart_packet_defs.h"
#include "string.h"

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define PARSER_READ_BYTE() (parser->rx_parser_buf[parser->rx_parser_buf_tail++])

uart_parser_t parser_defs[UART_DEFS_COUNT];

StaticTask_t UARTParserTaskBuffer;
StackType_t UARTParserTaskStack[UART_PARSER_TASK_STACK_SIZE];

void UARTParser_ParseBuf(uart_parser_t* parser);

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
	uart_parser_t* parser = NULL;

	// Find corresponding parser
	for (int i = 0; i < UART_DEFS_COUNT; i++) {

		if (parser_defs[i].uart->uart_handle == huart) {
			parser = &parser_defs[i];
			break;
		}
	}


	// Check if parser is valid
	if (parser == NULL) {
		debug_printf("Unknown UART ID\n");
		return;
	}

	// Calculate current transfer size
	uint16_t dataLen = Size - parser->rx_dma_buf_tail;

	while(dataLen) {
		// Calculate maximum bytes that can be copied in one continuous block
		uint16_t toCopy = MIN(
				MIN(UART_PARSER_PARSER_BUF_SIZE - parser->rx_parser_buf_head, dataLen),
				MIN(UART_PARSER_DMA_BUF_SIZE    - parser->rx_dma_buf_tail   , dataLen));

		// If it is possible, copy data block and increment pointers
		if (toCopy) {
			memcpy(parser->rx_parser_buf + parser->rx_parser_buf_head, parser->rx_dma_buf + parser->rx_dma_buf_tail, toCopy);

            parser->rx_parser_buf_head += toCopy;
            parser->rx_dma_buf_tail += toCopy;

			dataLen -= toCopy;
		}

		// Loop over
		if (parser->rx_parser_buf_head == UART_PARSER_PARSER_BUF_SIZE)
            parser->rx_parser_buf_head = 0;

		if (parser->rx_dma_buf_tail== UART_PARSER_DMA_BUF_SIZE)
            parser->rx_dma_buf_tail = 0;
	}

	// Notify parser about new data on specific UART channel to be processed and yield
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	xTaskNotifyFromISR(UARTParserTaskHandle, 1 << parser->uart->id, eSetBits, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void UARTParser_ParseBuf(uart_parser_t* parser) {
	uint8_t crc;

	while(parser->rx_parser_buf_head != parser->rx_parser_buf_tail) {
		switch (parser->state) {
            // Wait for packet start char
            case UART_PARSER_WAITING:
                if(PARSER_READ_BYTE() == UART_PARSER_KBX_START_CHAR)
                    parser->state = UART_PARSER_HEADER_CMD;
                break;

            // Parse header cmd
            case UART_PARSER_HEADER_CMD:
                parser->packet.cmd = PARSER_READ_BYTE();
                parser->state = UART_PARSER_HEADER_LEN;
                break;

            // Calculate data length / remaining data to read
            case UART_PARSER_HEADER_LEN:
                parser->packet.arg_count = PARSER_READ_BYTE();
				parser->state = UART_PARSER_HEADER_CRC;
                break;

			// Calculate CRC for the packet's header
			// TODO: Additional check - Deduce len from cmd field in message def
			case UART_PARSER_HEADER_CRC:
				crc = PARSER_READ_BYTE();

				if (crc != (uint8_t)(parser->packet.cmd + parser->packet.arg_count)) {
					parser->state = UART_PARSER_WAITING;
					break;
				}

				// Drop regular packets over 16 bytes long as they SHOULD not appear
				#warning "Parser drops frames over 16 bytes long - URC hotfix"
                if (parser->packet.arg_count > 16 && !UART_PACKET_IS_CUSTOM(parser->packet.cmd)) {
                	parser->state = UART_PARSER_WAITING;
                	break;
                }

                // For packet without arguments skip data acq phase
                if (parser->packet.arg_count != 0) {
                    parser->state = UART_PARSER_DATA;
                } else {
                    parser->state = UART_PARSER_CRC;
                }
				break;

            case UART_PARSER_DATA:
                parser->packet.args[parser->data_writen++] = PARSER_READ_BYTE();

                if (parser->data_writen == parser->packet.arg_count) {
                	parser->data_writen = 0;
                    parser->state = UART_PARSER_CRC;
                }

                break;

            case UART_PARSER_CRC:
                // Calculate CRC for the received packet
            	crc = parser->packet.cmd ^ parser->packet.arg_count;
                for (uint8_t i = 0; i < parser->packet.arg_count; i++)
                    crc ^= parser->packet.args[i];

                // Compare calculated CRC with a received one
				if (crc != PARSER_READ_BYTE()) {
					parser->state = UART_PARSER_WAITING;
					debug_printf("CRC Error\n");
					break;
				}

                parser->state = UART_PARSER_ÜRC;
                break;

			case UART_PARSER_ÜRC:
				// Calculate ÜRC - additional "CRC" - for the received packet
				crc = 0;
                for (uint8_t i = 0; i < parser->packet.arg_count; i++)
                    crc += (parser->packet.args[i] + i) * ((i & 0b11) + 1);

                // Compare calculated ÜRC with a received one
                if (crc == PARSER_READ_BYTE()) {
                	parser->packet.origin = UARTPacket_UARTIDToLink(parser->uart->id);

					if (!xQueueSend(uart_handler_incoming_packet_queue, &(parser->packet), 0)) {
						debug_printf("UART msg queue full\n");
					}
                } else {
					debug_printf("CRC Error\n");
                }

                parser->state = UART_PARSER_WAITING;
                break;
        }

        // Loop over
        if (parser->rx_parser_buf_tail == UART_PARSER_PARSER_BUF_SIZE) {
	        parser->rx_parser_buf_tail = 0;
        }
	}
}

void UARTParser_Task(void *argument) {
	// Start DMA reception and disable HT interrupt
	for (int i = 0; i < UART_DEFS_COUNT; i++) {
        parser_defs[i].uart = &uart_defs[i];

		HAL_UARTEx_ReceiveToIdle_DMA(uart_defs[i].uart_handle, parser_defs[i].rx_dma_buf, 32);
		__HAL_DMA_DISABLE_IT(uart_defs[i].uart_handle->hdmarx, DMA_IT_HT);
	}

	// Processing loop
	while(1) {
		// Wait for new data in the parser's buffer
		// UART id is encoded as a bit position (one's hot encoding)
		uint32_t uarts_to_process = ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        // Do some parsing if there is data available
		uint8_t uart_id = 0;
		while(uarts_to_process) {
			// Check every bit until all are cleared
			if(uarts_to_process & (1 << uart_id)) {
				// Parse buffer
				UARTParser_ParseBuf(&parser_defs[uart_id]);

				// Clear bit
				uarts_to_process &= ~(1 << uart_id);
			}

			uart_id++;
		}
    }
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
	uint8_t uart_id = 255;

	for (int i = 0; i < UART_DEFS_COUNT; i++) {
		if (uart_defs[i].uart_handle == huart) {
			uart_id = i;
			break;
		}

	}

	if (uart_id == 255) {
		__asm__ volatile ("BKPT");
		while(1) {}
	}

	if (huart->RxState == 32 && huart->ErrorCode & HAL_UART_ERROR_FE) {
		HAL_UARTEx_ReceiveToIdle_DMA(huart, parser_defs[uart_id].rx_dma_buf, 32);
		__HAL_DMA_DISABLE_IT(huart->hdmarx, DMA_IT_HT);
	}
	else {

	}
}
