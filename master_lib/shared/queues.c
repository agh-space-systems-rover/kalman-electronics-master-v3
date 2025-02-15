#include "queues.h"
#include "common.h"

QueueHandle_t uart_handler_incoming_packet_queue;
QueueHandle_t uart_handler_outgoing_packet_queue;

QueueHandle_t can_handler_incoming_packet_queue;
QueueHandle_t can_handler_outgoing_packet_queue;

void Queues_Init() {
    uart_handler_incoming_packet_queue = xQueueCreate(16, sizeof(uart_packet_t));
    uart_handler_outgoing_packet_queue = xQueueCreate(16, sizeof(uart_packet_t));

    can_handler_incoming_packet_queue = xQueueCreate(16, sizeof(can_packet_t));
	can_handler_outgoing_packet_queue = xQueueCreate(16, sizeof(can_packet_t));
}

BaseType_t Queues_SendCANFrame(can_packet_t* packet) {
    BaseType_t res = xQueueSend(can_handler_outgoing_packet_queue, packet, 0);

    if(!res) {
	    debug_printf("CAN encode queue full\n");
    }

    return res;
}
BaseType_t Queues_SendUARTFrame(uart_packet_t* packet) {
    BaseType_t res = pdFAIL;

    // check if silent mode detected
    if(RF_status == RF_OFF && packet->origin == LINK_RF_UART) {
        return res;
    }

    res = xQueueSend(uart_handler_outgoing_packet_queue, packet, 0);

    if(!res) {
	    debug_printf("UART encode queue full\n");
    }

    return res;
}
