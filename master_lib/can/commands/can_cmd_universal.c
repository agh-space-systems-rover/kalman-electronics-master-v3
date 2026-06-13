#include <string.h>
#include "can_cmd.h"
#include "hw/hw.h"
#include "uart/commands/uart_cmd.h"

/*
 *  RX Frames
 */



/*
 *  TX Frames
 */
void Cmd_Bus_Universal_SetDigitalOutput(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_DIGITAL_OUTPUT,
            .arg_count = CAN_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetPWMOutput(uint8_t* data) {
    can_packet_t msg = {
            .cmd  = CAN_CMD_UNIVERSAL_SET_PWM_OUTPUT,
            .arg_count = CAN_ARG_UNIVERSAL_SET_PWM_OUTPUT
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_PWM_OUTPUT);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetLEDDriver(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_LED_DRIVER,
            .arg_count =  CAN_ARG_UNIVERSAL_SET_LED_DRIVER
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_LED_DRIVER);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetHBridge(uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_HBRIDGE,
            .arg_count = CAN_ARG_UNIVERSAL_SET_HBRIDGE
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_HBRIDGE);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetStepperPosition(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_SET_STEPPER_POSITION,
            .arg_count = CAN_ARG_UNIVERSAL_SET_STEPPER_POSITION
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_SET_STEPPER_POSITION);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_StepperHomingRequest(uint8_t* data) {
    // can_packet_t msg = {
    //         .cmd = CAN_CMD_UNIVERSAL_STEPPER_HOMING_REQUEST,
    //         .arg_count = CAN_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST,
    // };
    // memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST);

    // Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_WeightRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_WEIGHT_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_WEIGHT_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_WEIGHT_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_WeightTareRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_WEIGHT_TARE_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_WEIGHT_TARE_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_WEIGHT_TARE_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_InputRequest(uint8_t* data) {
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_INPUT_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_INPUT_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_INPUT_REQUEST);

    Queues_SendCANFrame(&msg);
}
void Cmd_Bus_Universal_StepperPositionRequest(uint8_t* data) {
    // can_packet_t msg = {
    //         .cmd = CAN_CMD_UNIVERSAL_STEPPER_POSITION_REQUEST,
    //         .arg_count = CAN_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST
    // };
    // memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST);

    // Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_AutomationSequenceBeginRequest(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST,
        .arg_count = CAN_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST
    };

    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_AutomationSequenceStateRequest(uint8_t* data) {
    can_packet_t msg = {
        .cmd = CAN_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_REQUEST,
        .arg_count = CAN_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_REQUEST
    };

    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_REQUEST);

    Queues_SendCANFrame(&msg);
}

void Cmd_Bus_Universal_SetDistanceMeasurement(const uint8_t* data){
    can_packet_t msg = {
            .cmd = CAN_CMD_UNIVERSAL_DISTANCE_REQUEST,
            .arg_count = CAN_ARG_UNIVERSAL_DISTANCE_REQUEST
    };
    memcpy(&msg.args, data, CAN_ARG_UNIVERSAL_DISTANCE_REQUEST);

    Queues_SendCANFrame(&msg);

}


void Cmd_Bus_Universal_SetResponse(uint8_t* data) {
    Cmd_UART_Universal_SetResponse(data);
}
void Cmd_Bus_Universal_WeightResponse(uint8_t *data) {
    Cmd_UART_Universal_WeightResponse(data);
}
void Cmd_Bus_Universal_InputResponse(uint8_t *data) {
    Cmd_UART_Universal_InputResponse(data);
}
void Cmd_Bus_Universal_StepperPositionResponse(uint8_t *data) {
    Cmd_UART_Universal_StepperPositionResponse(data);
}
void Cmd_Bus_Universal_AutomationSequenceStateResponse(uint8_t* data) {
    Cmd_UART_Universal_AutomationSequenceStateResponse(data);
}
void Cmd_Bus_Universal_DistanceResponse(uint8_t* data) {
    Cmd_UART_Universal_DistanceResponse(data);
}