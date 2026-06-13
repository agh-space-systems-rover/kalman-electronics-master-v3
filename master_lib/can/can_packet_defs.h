#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H

#include "can_packet.h"
#include "can/commands/can_cmd.h"

#define CAN_PACKET_DEFS_LEN (sizeof(can_packet_defs)/sizeof(can_packet_def_t))

// CAN RX packet callback registration
const can_packet_def_t can_packet_defs[] = {
		// --- Motor ---
		{
				.cmd = CAN_CMD_MOTOR_GET_WHEELS1,
				.arg_count = CAN_ARG_MOTOR_GET_WHEELS1,
				.execute = Cmd_Bus_Motor_GetWheels1,
		},
		{
				.cmd = CAN_CMD_MOTOR_GET_WHEELS2,
				.arg_count = CAN_ARG_MOTOR_GET_WHEELS2,
				.execute = Cmd_Bus_Motor_GetWheels2,
		},
		{
				.cmd = CAN_CMD_MOTOR_GET_STATUS,
				.arg_count = CAN_ARG_MOTOR_GET_STATUS,
				.execute = Cmd_Bus_Motor_GetStatus,
		},
		{
				.cmd = CAN_CMD_MOTOR_GET_TEMPERATURE,
				.arg_count = CAN_ARG_MOTOR_GET_TEMPERATURE,
				.execute = Cmd_Bus_Motor_GetTemperature,
		},

		// --- Arm 6DoF ---
		{
				.cmd = CAN_CMD_ARM_6DOF_GET_POS1,
				.arg_count = CAN_ARG_ARM_6DOF_GET_POS1,
				.execute = Cmd_Bus_Arm6DOF_GetPos1,
		},
		{
				.cmd = CAN_CMD_ARM_6DOF_GET_POS2,
				.arg_count = CAN_ARG_ARM_6DOF_GET_POS2,
				.execute = Cmd_Bus_Arm6DOF_GetPos2,
		},
		{
				.cmd = CAN_CMD_ARM_6DOF_SET_GRIPPER,
				.arg_count = CAN_ARG_ARM_6DOF_SET_GRIPPER,
				.execute = Cmd_Bus_Arm6DOF_SetGripper,
		},
		{
				.cmd = CAN_CMD_ARM_6DOF_SMART_KUTONG_DATA,
				.arg_count = CAN_ARG_ARM_6DOF_SMART_KUTONG_DATA,
				.execute = Cmd_Bus_Arm6DOF_GetSmartKutongData,
		},

		// --- Universal ---
		{
				.cmd = CAN_CMD_UNIVERSAL_SET_RESPONSE,
				.arg_count = CAN_ARG_UNIVERSAL_SET_RESPONSE,
				.execute = Cmd_Bus_Universal_SetResponse
		},
		{
				.cmd = CAN_CMD_UNIVERSAL_WEIGHT_RESPONSE,
				.arg_count = CAN_ARG_UNIVERSAL_WEIGHT_RESPONSE,
				.execute = Cmd_Bus_Universal_WeightResponse
		},
		{
				.cmd = CAN_CMD_UNIVERSAL_INPUT_RESPONSE,
				.arg_count = CAN_ARG_UNIVERSAL_INPUT_RESPONSE,
				.execute = Cmd_Bus_Universal_InputResponse
		},
		// {
		// 		.cmd = CAN_CMD_UNIVERSAL_STEPPER_POSITION_RESPONSE,
		// 		.arg_count = CAN_ARG_UNIVERSAL_STEPPER_POSITION_RESPONSE,
		// 		.execute = Cmd_Bus_Universal_StepperPositionResponse
		// },
		{
				.cmd = CAN_CMD_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_RESPONSE,
				.arg_count = CAN_ARG_UNIVERSAL_AUTOMATION_SEQUENCE_STATE_RESPONSE,
				.execute = Cmd_Bus_Universal_SetResponse
		},	
		// Distance response: response ID 0x5A / 4 bytes (protocol spec)
		{
				.cmd = CAN_CMD_UNIVERSAL_DISTANCE_RESPONSE,
				.arg_count = CAN_ARG_UNIVERSAL_DISTANCE_RESPONSE,
				.execute = Cmd_Bus_Universal_DistanceResponse
		},
		
		// --- Power Distribution ---
		{
				.cmd = CAN_CMD_VOLTAGE_RESPONSE,
				.arg_count = CAN_ARG_VOLTAGE_RESPONSE,
				.execute = Cmd_Bus_PowerDistribution_VoltageResponse,
		},
		{
				.cmd = CAN_CMD_SENSOR_RESPONSE,
				.arg_count = CAN_ARG_SENSOR_RESPONSE,
				.execute = Cmd_Bus_PowerDistribution_SensorResponse,
		},

		// --- Science ---
		{
				.cmd = CAN_CMD_SCIENCE_GET_TEMPERATURE1,
				.arg_count = CAN_ARG_SCIENCE_GET_TEMPERATURE1,
				.execute = Cmd_Bus_Science_GetTemperature1,
		},
		{
				.cmd = CAN_CMD_SCIENCE_GET_TEMPERATURE2,
				.arg_count = CAN_ARG_SCIENCE_GET_TEMPERATURE2,
				.execute = Cmd_Bus_Science_GetTemperature2,
		},
		{
				.cmd = CAN_CMD_SCIENCE_GET_HUMIDITY,
				.arg_count = CAN_ARG_SCIENCE_GET_HUMIDITY,
				.execute = Cmd_Bus_Science_GetHumidity,
		},
		{
				.cmd = CAN_CMD_SCIENCE_GET_ATMOSPHERE,
				.arg_count = CAN_ARG_SCIENCE_GET_ATMOSPHERE,
				.execute = Cmd_Bus_Science_GetAtmosphere,
		},
		{
				.cmd = CAN_CMD_SCIENCE_GET_WEIGHT,
				.arg_count = CAN_ARG_SCIENCE_GET_WEIGHT,
				.execute = Cmd_Bus_Science_GetWeight,
		},
		{
				.cmd = CAN_CMD_SCIENCE_GET_STATUS,
				.arg_count = CAN_ARG_SCIENCE_GET_STATUS,
				.execute = Cmd_Bus_Science_GetStatus,
		},

		// --- Mobilab v2 ---
		{
				.cmd = CAN_CMD_MOBILAB_GET_TEMPERATURE,
				.arg_count = CAN_ARG_MOBILAB_GET_TEMPERATURE,
				.execute = Cmd_Bus_Mobilab_GetTemperature,
		},

		// --- Drill ---
		{
				.cmd = CAN_CMD_DRILL_SEND_WEIGHT,
				.arg_count = CAN_ARG_DRILL_SEND_WEIGHT,
				.execute = Cmd_Bus_Drill_GetWeight
		},
		{
				.cmd = CAN_CMD_DRILL_TELEMETRY,
				.arg_count = CAN_ARG_DRILL_TELEMETRY,
				.execute = Cmd_Bus_Drill_Telemetry
		},


		// --- Fallback handlers ---
		//TODO: uh, how
#warning "Frame 0xBE is discarded, because for some reason we receive it"
		{
				.cmd = 190,
				.arg_count = 2,
				.execute = Cmd_Bus_EmptyHandler,
		},
};

#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_PACKET_DEFS_H
