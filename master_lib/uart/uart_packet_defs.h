#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H

#include "uart_packet.h"
#include "uart/commands/uart_cmd.h"

#define UART_PACKET_DEFS_LEN (sizeof(uart_packet_defs)/sizeof(uart_packet_def_t))

// it's not unused, but it's included in multiple files, so it's not detected. __unused is used to suppress the warning
__unused static uart_packet_def_t uart_packet_defs[] = {
        // --- Master ---
        {
            .cmd = UART_CMD_MASTER_SET_LINK,
            .arg_count = UART_ARG_MASTER_SET_LINK,
            .execute = Cmd_UART_Master_SetLink,
        },
        // --- Motor ---
        {
            .cmd = UART_CMD_MOTOR_SET_WHEELS,
            .arg_count = UART_ARG_MOTOR_SET_WHEELS,
            .execute = Cmd_UART_Motor_SetWheels,
        },
        {
            .cmd = UART_CMD_MOTOR_CALIBRATE,
            .arg_count = UART_ARG_MOTOR_CALIBRATE,
            .execute = Cmd_UART_Motor_Calibrate,
        },
        {
			.cmd = UART_CMD_MOTOR_REMOTE_ESTOP,
			.arg_count = UART_ARG_MOTOR_REMOTE_ESTOP,
			.execute = CMD_UART_Motor_RemoteEstop,
		},

        // --- Arm 6DoF ---
        {
            .cmd = UART_CMD_ARM_6DOF_SET_POS,
            .arg_count = UART_ARG_ARM_6DOF_SET_POS,
            .execute = Cmd_UART_Arm6DOF_SetPos,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_POS_VEL,
            .arg_count = UART_ARG_ARM_6DOF_SET_POS_VEL,
            .execute = Cmd_UART_Arm6DOF_SetPosVel,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_TORQUE,
            .arg_count = UART_ARG_ARM_6DOF_SET_TORQUE,
            .execute = Cmd_UART_Arm6DOF_SetTorque,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_VELOCITY,
            .arg_count = UART_ARG_ARM_6DOF_SET_VELOCITY,
            .execute = Cmd_UART_Arm6DOF_SetVelocity,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_GRIPPER,
            .arg_count = UART_ARG_ARM_6DOF_SET_GRIPPER,
            .execute = Cmd_UART_Arm6DOF_SetGripper,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_GET_POS,
            .arg_count = UART_ARG_ARM_6DOF_GET_POS,
            .execute = Cmd_UART_Arm6DOF_GetPos,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_POSITIONING_START,
            .arg_count = UART_ARG_ARM_6DOF_POSITIONING_START,
            .execute = Cmd_UART_Arm6DOF_PositioningStart,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_POSITIONING_ABORT,
            .arg_count = UART_ARG_ARM_6DOF_POSITIONING_ABORT,
            .execute = Cmd_UART_Arm6DOF_PositioningAbort,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_SET_ACTUAL_POS,
            .arg_count = UART_ARG_ARM_6DOF_SET_ACTUAL_POS,
            .execute = Cmd_UART_Arm6DOF_SetActualPos,
        },
		{
			.cmd = UART_CMD_ARM_6DOF_KEYBOARD_CLICK,
			.arg_count = UART_ARG_ARM_6DOF_KEYBOARD_CLICK,
			.execute = Cmd_UART_Arm6DOF_KeyboardClick,
		},
		{
			.cmd = UART_CMD_ARM_6DOF_SOFT_RESET,
			.arg_count = UART_ARG_ARM_6DOF_SOFT_RESET,
			.execute = Cmd_UART_Arm6DOF_SoftReset,
		},
        {
            .cmd = UART_CMD_ARM_6DOF_GET_PROBE_REQUEST,
            .arg_count = UART_ARG_ARM_6DOF_GET_PROBE_REQUEST,
            .execute = Cmd_UART_Arm6DOF_GetProbeRequest,
        },
        {
            .cmd = UART_CMD_ARM_6DOF_AUTOCLICK_SET_POS,
            .arg_count = UART_ARG_ARM_6DOF_AUTOCLICK_SET_POS,
            .execute = Cmd_UART_Arm6DOF_Autoclick_SetPos,
        },
		{
			.cmd = UART_CMD_ARM_6DOF_GET_PROBE_ESP,
			.arg_count = UART_ARG_ARM_6DOF_GET_PROBE_ESP,
			.execute = Cmd_UART_Arm6DOF_GetProbeEsp,
		},

        // --- Drill ---
        {
            .cmd = UART_CMD_DRILL_A_BRIDGE_SET,
            .arg_count = UART_ARG_DRILL_A_BRIDE_SET,
            .execute = Cmd_UART_Drill_A_Bridge_Set
        },
        {
            .cmd = UART_CMD_DRILL_B_BRIDGE_SET,
            .arg_count = UART_ARG_DRILL_B_BRIDE_SET,
            .execute = Cmd_UART_Drill_B_Bridge_Set
        },
        {
			.cmd = UART_CMD_DRILL_C_BRIDGE_SET,
			.arg_count = UART_ARG_DRILL_C_BRIDE_SET,
			.execute = Cmd_UART_Drill_C_Bridge_Set
		},
        {
            .cmd = UART_CMD_DRILL_GET_WEIGHT,
            .arg_count = UART_ARG_DRILL_GET_WEIGHT,
            .execute = Cmd_UART_Drill_GetWeightRequest
        },
     {
            .cmd = UART_CMD_DRILL_AUTONOMY,
            .arg_count = UART_ARG_DRILL_AUTONOMY,
            .execute = Cmd_UART_Drill_Autonomy
        },

        // --- UEUOS v2 ---
        {
            .cmd = UART_CMD_UEUOS_SET_STATE,
            .arg_count = UART_ARG_UEUOS_SET_STATE,
            .execute = Cmd_UART_Ueuos_SetState,
        },
        {
            .cmd = UART_CMD_UEUOS_SET_COLOR,
            .arg_count = UART_ARG_UEUOS_SET_COLOR,
            .execute = Cmd_UART_Ueuos_SetColor,
        },
        {
            .cmd = UART_CMD_UEUOS_SET_EFFECT,
            .arg_count = UART_ARG_UEUOS_SET_EFFECT,
            .execute = Cmd_UART_Ueuos_SetEffect,
        },

        // --- Universal ---
        {
			.cmd = UART_CMD_UNIVERSAL_SET_DIGITAL_OUTPUT,
			.arg_count = UART_ARG_UNIVERSAL_SET_DIGITAL_OUTPUT,
			.execute = Cmd_UART_Universal_SetDigitalOutput
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_PWM_OUTPUT,
            .arg_count = UART_ARG_UNIVERSAL_SET_PWM_OUTPUT,
            .execute = Cmd_UART_Universal_SetPWMOutput
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_LED_DRIVER,
            .arg_count = UART_ARG_UNIVERSAL_SET_LED_DRIVER,
            .execute = Cmd_UART_Universal_SetLEDDriver
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_HBRIDGE,
            .arg_count = UART_ARG_UNIVERSAL_SET_HBRIDGE,
            .execute = Cmd_UART_Universal_SetHBridge
        },
        {
            .cmd = UART_CMD_UNIVERSAL_SET_STEPPER_POSITION,
            .arg_count = UART_ARG_UNIVERSAL_SET_STEPPER_POSITION,
            .execute = Cmd_UART_Universal_SetStepperPosition
        },
        // {
        //     .cmd = UART_CMD_UNIVERSAL_STEPPER_HOMING_REQUEST,
        //     .arg_count = UART_ARG_UNIVERSAL_STEPPER_HOMING_REQUEST,
        //     .execute = Cmd_UART_Universal_StepperHomingRequest
        // },
        {
            .cmd = UART_CMD_UNIVERSAL_WEIGHT_REQUEST,
            .arg_count = UART_ARG_UNIVERSAL_WEIGHT_REQUEST,
            .execute = Cmd_UART_Universal_WeightRequest
        },
        {
            .cmd = UART_CMD_UNIVERSAL_WEIGHT_TARE_REQUEST,
            .arg_count = UART_ARG_UNIVERSAL_WEIGHT_TARE_REQUEST,
            .execute = Cmd_UART_Universal_WeightTareRequest
        },
        {
            .cmd = UART_CMD_UNIVERSAL_INPUT_REQUEST,
            .arg_count = UART_ARG_UNIVERSAL_INPUT_REQUEST,
            .execute = Cmd_UART_Universal_InputRequest
        },
        // {
        //     .cmd = UART_CMD_UNIVERSAL_STEPPER_POSITION_REQUEST,
        //     .arg_count = UART_ARG_UNIVERSAL_STEPPER_POSITION_REQUEST,
        //     .execute = Cmd_UART_Universal_StepperPositionRequest
        // },
        {
            .cmd = UART_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST,
            .arg_count = UART_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_BEGIN_REQUEST,
            .execute = Cmd_UART_Universal_AutomationSequenceBeginRequest
        },
            {
            .cmd = UART_CMD_UNIVERSAL_SET_DISTANCE_MEASUREMENT,
            .arg_count = UART_ARG_UNIVERSAL_SET_DISTANCE_MEASUREMENT,
            .execute = Cmd_UART_Universal_SetDistanceMeasurement

        },


        // --- Science ---
        {
            .cmd = UART_CMD_SCIENCE_GET_SAMPLES_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_SAMPLES_REQUEST,
            .execute = Cmd_UART_Science_GetSamplesRequest,
        },
        {
            .cmd = UART_CMD_SCIENCE_GET_WEIGHT_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_WEIGHT_REQUEST,
            .execute = Cmd_UART_Science_GetWeightRequest,
        },
        {
            .cmd = UART_CMD_SCIENCE_GET_ATMOSPHERE_REQUEST,
            .arg_count = UART_ARG_SCIENCE_GET_ATMOSPHERE_REQUEST,
            .execute = Cmd_UART_Science_GetAtmosphereRequest,
        },

        // --- Mobilab v2 ---
        {
            .cmd = UART_CMD_MOBILAB_SET_PUMP,
            .arg_count = UART_ARG_MOBILAB_SET_PUMP,
            .execute = Cmd_UART_Mobilab_SetPump
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_HEATER,
            .arg_count = UART_ARG_MOBILAB_SET_HEATER,
            .execute = Cmd_UART_Mobilab_SetHeater
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_BACKLIGHT,
            .arg_count = UART_ARG_MOBILAB_SET_BACKLIGHT,
            .execute = Cmd_UART_Mobilab_SetBacklight
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_AUX,
            .arg_count = UART_ARG_MOBILAB_SET_AUX,
            .execute = Cmd_UART_Mobilab_SetAux
        },
        {
            .cmd = UART_CMD_MOBILAB_SET_SERVO,
            .arg_count = UART_ARG_MOBILAB_SET_SERVO,
            .execute = Cmd_UART_Mobilab_SetServo
        },

        // --- Mux ---
        {
            .cmd = UART_CMD_MUX_SET_CAM,
            .arg_count = UART_ARG_MUX_SET_CAM,
            .execute = Cmd_UART_Mux_SetCam,
        },
        {
            .cmd = UART_CMD_MUX_SET_CHANNEL,
            .arg_count = UART_ARG_MUX_SET_CHANNEL,
            .execute = Cmd_UART_Mux_SetChannel,
        },
        {
            .cmd = UART_CMD_MUX_SET_POWER,
            .arg_count = UART_ARG_MUX_SET_POWER,
            .execute = Cmd_UART_Mux_SetPower,
        },

        //ARM CM4
        {
            .cmd = UART_CMD_ARM_CM4,
            .arg_count = UART_ARG_ARM_CM4,
            .execute = Cmd_UART_Arm6DOF_CM4,
        },

        //SILENT MODE
        {
            .cmd = UART_CMD_SILENT_MODE,
            .arg_count = UART_ARG_SILENT_MODE,
            .execute = Cmd_UART_SilentMode

        },

        // --- Power Distribution ---
        {
            .cmd = UART_CMD_VOLTAGE_RESPONSE,
            .arg_count = UART_ARG_VOLTAGE_RESPONSE,
            .execute = Cmd_UART_PowerDistribution_GetVoltage,
        },
        {   
            .cmd = UART_CMD_SENSOR_RESPONSE,
            .arg_count = UART_ARG_SENSOR_RESPONSE,
            .execute = Cmd_UART_PowerDistribution_GetSensor,
        },


        // --- Custom ---
        {
            .cmd = UART_CMD_CUSTOM_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_CustomToRF,
        },
        {
            .cmd = UART_CMD_CUSTOM_TO_UART,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_CustomToUART,
        },

        {
            .cmd = UART_CMD_SUPERVISOR_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_SupervisorToRF,
        },
        {
            .cmd = UART_CMD_SUPERVISOR_TO_UART,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_SupervisorToUART,
        },
        {
            .cmd = UART_CMD_RF_TO_ESP32,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_RF_To_ESP32,
        },
        {
            .cmd = UART_CMD_ESP32_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_ESP32_To_RF,
        },
        {
            .cmd = UART_CMD_CUSTOM_ARM_TO_UART,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_ARM_CustomToUART,
        },
        {
            .cmd = UART_CMD_CUSTOM_ARM_TO_RF,
            .arg_count = UART_ARG_MAX,
            .execute = Cmd_UART_ARM_CustomToRF,
        },

};

//TODO: add message traits / fields such as custom_frame or ack_required changing handler behaviour
#define UART_PACKET_IS_CUSTOM(cmd) ((       \
    (cmd == UART_CMD_CUSTOM_TO_RF)       || \
    (cmd == UART_CMD_CUSTOM_TO_UART)     || \
    (cmd == UART_CMD_SUPERVISOR_TO_RF)   || \
    (cmd == UART_CMD_SUPERVISOR_TO_UART) || \
    (cmd == UART_CMD_ESP32_TO_RF)        || \
    (cmd == UART_CMD_RF_TO_ESP32)        || \
    (cmd == UART_CMD_CUSTOM_ARM_TO_UART)        || \
    (cmd == UART_CMD_CUSTOM_ARM_TO_RF))       ? 1 : 0)


#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_PACKET_DEFS_H
