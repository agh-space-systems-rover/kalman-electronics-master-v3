#include <string.h>
#include "can_cmd.h"
#include "uart/commands/uart_cmd.h"

void Cmd_Bus_Drill_A_Bridge_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
         .cmd = CAN_CMD_DRILL_A_BRIDGE_SET,
         .arg_count = CAN_ARG_DRILL_A_BRIDGE_SET,
         .args[0] = direction,
         .args[1] = speed
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_B_Bridge_Set(uint8_t direction, uint8_t speed){
    can_packet_t msg = {
            .cmd = CAN_CMD_DRILL_B_BRIDGE_SET,
            .arg_count = CAN_ARG_DRILL_B_BRIDGE_SET,
            .args[0] = direction,
            .args[1] = speed
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_C_Bridge_Set(uint8_t direction, uint8_t speed){
	can_packet_t msg = {
			.cmd = CAN_CMD_DRILL_C_BRIDGE_SET,
			.arg_count = CAN_ARG_DRILL_C_BRIDGE_SET,
			.args[0] = direction,
			.args[1] = speed
	};

	Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_Autonomy(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_DRILL_AUTONOMY,
        .arg_count = CAN_ARG_DRILL_AUTONOMY,
        .args = {data[0]}
    };

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_GetWeightRequest(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_DRILL_GET_WEIGHT,
            .arg_count = CAN_ARG_DRILL_GET_WEIGHT,
            .args = {data[0]}
	};

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Drill_GetWeight(uint8_t* data){
    int32_t weight;

    memcpy(&weight, data, sizeof(int32_t));

    Cmd_UART_Drill_GetWeight(weight);
}

void Cmd_Bus_Drill_Telemetry(uint8_t* data){
    struct DrillTelemetry {
        uint8_t limit_sw_up;
        uint8_t limit_sw_down;
        uint8_t autonomy_state;
        uint8_t based_status;
        int32_t reserved; // for future use
    } __attribute__((packed)) telemetry;

    memcpy(&telemetry, data, sizeof(struct DrillTelemetry));

    Cmd_UART_Drill_Telemetry((uint8_t*)&telemetry);
}