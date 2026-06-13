#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

void Cmd_UART_Drill_A_Bridge_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_A_Bridge_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_B_Bridge_Set(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_B_Bridge_Set(data[0], data[1]);

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_C_Bridge_Set(uint8_t* data, uart_packet_link_t link_type){
	if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
		Cmd_Bus_Drill_C_Bridge_Set(data[0], data[1]);

		Cmd_UART_BlinkLed(link_type);
	}
}



void Cmd_UART_Drill_GetWeightRequest(uint8_t* data, uart_packet_link_t link_type){
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_GetWeightRequest();

        Cmd_UART_BlinkLed(link_type);
    }
}

void Cmd_UART_Drill_Autonomy(uint8_t* data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) || (link_type == logic.link_type)) {
        Cmd_Bus_Drill_Autonomy(data);

        Cmd_UART_BlinkLed(link_type);
    }
}


void Cmd_UART_Drill_GetWeight(int32_t weight){
    uart_packet_t msg = {
            .cmd = UART_CMD_DRILL_SEND_WEIGHT,
            .arg_count = UART_ARG_DRILL_SEND_WEIGHT,
            .origin = logic.link_type
    };

    memcpy(&msg.args, (void*)&weight, sizeof(int32_t));

    Queues_SendUARTFrame(&msg);
}
\
void Cmd_UART_Drill_Telemetry(uint8_t* data) {
    uart_packet_t msg = {
            .cmd = UART_CMD_DRILL_TELEMETRY,
            .arg_count = UART_ARG_DRILL_TELEMETRY,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_DRILL_TELEMETRY);

    Queues_SendUARTFrame(&msg);
}