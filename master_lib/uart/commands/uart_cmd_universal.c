#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"


void Cmd_UART_Universal_SetDigitalOutput(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetDigitalOutput(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetPWMOutput(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetPWMOutput(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetLEDDriver(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetLEDDriver(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetHBridge(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetHBridge(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_SetStepperPosition(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetStepperPosition(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_StepperHomingRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_StepperHomingRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_WeightRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_WeightRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_WeightTareRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_WeightTareRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_InputRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_InputRequest(data);
    Cmd_UART_BlinkLed(link_type);
}
void Cmd_UART_Universal_StepperPositionRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_StepperPositionRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_AutomationSequenceBeginRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_AutomationSequenceBeginRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_AutomationSequenceStateRequest(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_AutomationSequenceStateRequest(data);
    Cmd_UART_BlinkLed(link_type);
}

void Cmd_UART_Universal_SetDistanceMeasurement(uint8_t* data, uart_packet_link_t link_type) {
    Cmd_Bus_Universal_SetDistanceMeasurement(data);
    Cmd_UART_BlinkLed(link_type);
}


void Cmd_UART_Universal_SetResponse(uint8_t* data) {
    uart_packet_t msg = {
        .cmd = UART_CMD_UNIVERSAL_SET_RESPONSE,
        .arg_count = UART_ARG_UNIVERSAL_SET_RESPONSE,
        .origin = logic.link_type
};

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_SET_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

void Cmd_UART_Universal_WeightResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_WEIGHT_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_WEIGHT_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_WEIGHT_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}
void Cmd_UART_Universal_InputResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_INPUT_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_INPUT_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_INPUT_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}
void Cmd_UART_Universal_StepperPositionResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE,
            .origin = logic.link_type
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}

void Cmd_UART_Universal_AutomationSequenceStateResponse(uint8_t* data){
    uart_packet_t msg = {
        .cmd = UART_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE,
        .arg_count = UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE,
        .origin = logic.link_type
};

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}


void Cmd_UART_Universal_DistanceResponse(uint8_t* data){
    uart_packet_t msg = {
            .cmd = UART_CMD_UNIVERSAL_DISTANCE_RESPONSE,
            .arg_count = UART_ARG_UNIVERSAL_DISTANCE_RESPONSE,
            // .origin = logic.link_type
            .origin = logic.link_type | LINK_RF_UART // Allow response to be sent to any link, as distance measurement might be requested by different modules
    };

    memcpy(&msg.args, data, UART_ARG_UNIVERSAL_DISTANCE_RESPONSE);

    Queues_SendUARTFrame(&msg);
    Cmd_UART_BlinkLed(logic.link_type);
}