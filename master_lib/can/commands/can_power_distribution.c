#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "uart/commands/uart_cmd.h"

void Cmd_Bus_PowerDistribution_VoltageResponse(uint8_t* data){
    Cmd_UART_PowerDistribution_VoltageResponse(data);
}

void Cmd_Bus_PowerDistribution_SensorResponse(uint8_t* data){
    Cmd_UART_PowerDistribution_SensorResponse(data);
}
