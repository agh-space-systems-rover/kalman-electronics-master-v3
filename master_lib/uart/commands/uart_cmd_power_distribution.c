#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"


void Cmd_UART_PowerDistribution_GetVoltage(uint8_t* data, uart_packet_link_t link_type)
{
    Cmd_Bus_PowerDistribution_VoltageResponse(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_PowerDistribution_GetSensor(uint8_t* data, uart_packet_link_t link_type)
{
    Cmd_Bus_PowerDistribution_SensorResponse(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_PowerDistribution_SensorResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_SENSOR_RESPONSE,
            .arg_count = UART_ARG_SENSOR_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_SENSOR_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

void Cmd_UART_PowerDistribution_VoltageResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_VOLTAGE_RESPONSE,
            .arg_count = UART_ARG_VOLTAGE_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_VOLTAGE_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}