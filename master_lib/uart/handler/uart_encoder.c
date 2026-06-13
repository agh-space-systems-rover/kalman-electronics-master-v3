#include <string.h>
#include "uart_encoder.h"


StaticTask_t UARTEncoderTaskBuffer;
StackType_t UARTEncoderTaskStack[UART_ENCODER_TASK_STACK_SIZE];

uart_encoder_t encoder_defs[UART_DEFS_COUNT];

void UARTEncoder_EncodePacket(uart_encoder_t* encoder, uart_packet_t* msg);
void UARTEncoder_EncodeToBuf(uart_encoder_t* encoder, uart_packet_t* msg);

void HAL_UART_TxCpltCallback(UART_HandleTypeDef* huart) {
    uart_encoder_t* encoder = NULL;
 
    // Find corresponding encoder
    for (int i = 0; i < UART_DEFS_COUNT; i++) {
        if (encoder_defs[i].uart->uart_handle == huart) {
            encoder = &encoder_defs[i];
            break;
        }
    }

    // Check if parser is valid
    if (encoder == NULL) {
        debug_printf("Unknown UART ID\n");
        return;
    }

    // Update

    // If there is new data, transmit it
    if (encoder->tx_dma_buf_head != encoder->tx_dma_buf_tail) {
        uint16_t len = encoder->tx_dma_buf_head - encoder->tx_dma_buf_tail;

        HAL_UART_Transmit_DMA(
                encoder->uart->uart_handle,
                encoder->tx_dma_buf + encoder->tx_dma_buf_tail,
                len);
        encoder->tx_dma_buf_tail += len;
    } else {
        encoder->status = UART_ENCODER_IDLE;
    }
}

void UARTEncoder_Task(void *argument) {
    // Disable DMA HT interrupt and prepare encoder structure
    for (int i = 0; i < UART_DEFS_COUNT; i++) {
        encoder_defs[i].uart = &uart_defs[i];
        __HAL_DMA_DISABLE_IT(uart_defs[i].uart_handle->hdmatx, DMA_IT_HT);
    }

    while(1) {
        uart_packet_t msg;
        xQueueReceive(uart_handler_outgoing_packet_queue, &msg, portMAX_DELAY);

        // Encode packets on all target UARTs
        uint8_t uart_id = 0;
        uart_packet_link_t uart_targets = msg.origin;

        while (uart_targets & LINK_UART_ANY) {
            // Check every bit (UART) until all are cleared
            if(uart_targets & (1 << uart_id)) {
                // Encode packet to buffer
                UARTEncoder_EncodePacket(&encoder_defs[uart_id], &msg);

                // Clear bit
                uart_targets &= ~(1 << uart_id);
            }

            uart_id++;
        }
    }
}

void UARTEncoder_EncodePacket(uart_encoder_t* encoder, uart_packet_t* msg) {
    //TODO: implement circular buffer

    // Reset pointers when all previously queued data has been transmitted
    if (encoder->tx_dma_buf_head >= encoder->tx_dma_buf_tail && encoder->status == UART_ENCODER_IDLE) {
        encoder->tx_dma_buf_head = 0;
        encoder->tx_dma_buf_tail = 0;
    }

    uint16_t packet_len = 4 + msg->arg_count + 2; // Header + data + crc + urc

    taskENTER_CRITICAL();

    // Abort transaction if there is no space in tx buffer
    if (encoder->tx_dma_buf_head + packet_len >= UART_ENCODER_DMA_BUF_SIZE) {
        debug_printf("TX buffer overrun\n");
        taskEXIT_CRITICAL();
        return;
    }

    // Encode packet to buffer
    UARTEncoder_EncodeToBuf(encoder, msg);

    // Start DMA if it is not running
    if (encoder->status == UART_ENCODER_IDLE) {
        encoder->status = UART_ENCODER_TX;
        uint16_t len = encoder->tx_dma_buf_head - encoder->tx_dma_buf_tail;

        HAL_UART_Transmit_DMA(
                encoder->uart->uart_handle,
                encoder->tx_dma_buf + encoder->tx_dma_buf_tail,
                len);
        encoder->tx_dma_buf_tail += len;
    }

    taskEXIT_CRITICAL();
}

void UARTEncoder_EncodeToBuf(uart_encoder_t* encoder, uart_packet_t* msg) {
    // CRC calculation
    uint8_t crc = msg->cmd ^ msg->arg_count;
    for (uint8_t i = 0; i < msg->arg_count; i++)
        crc ^= msg->args[i];

    // ÜRC calculation - additional "CRC" - for the received packet
    uint8_t urc = 0;
    for (uint8_t i = 0; i < msg->arg_count; i++)
		urc += (msg->args[i] + i) * ((i & 0b11) + 1);

    uint8_t* addr = encoder->tx_dma_buf + encoder->tx_dma_buf_head;

    addr[0] = '<';                               // Start
    addr[1] = msg->cmd;                          // Command
    addr[2] = msg->arg_count;                    // Len
    addr[3] = msg->cmd + msg->arg_count;         // HRC - header checksum

    memcpy(addr + 4, msg->args, msg->arg_count); // Data
    addr[msg->arg_count + 4] = crc;              // CRC
    addr[msg->arg_count + 5] = urc;              // ÜRC


    // Buffer overflow has been checked before
    encoder->tx_dma_buf_head += 4 + msg->arg_count + 2;
}
