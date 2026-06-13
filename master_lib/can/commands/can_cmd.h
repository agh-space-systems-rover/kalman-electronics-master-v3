#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H

#include "can/can_packet.h"
#include "shared/common.h"

/*
 *  RX Frames
 */

// --- Motor ---
void Cmd_Bus_Motor_GetWheels1(uint8_t *data);
void Cmd_Bus_Motor_GetWheels2(uint8_t *data);
void Cmd_Bus_Motor_GetStatus(uint8_t* data);
void Cmd_Bus_Motor_GetTemperature(uint8_t* data);

// --- Arm 6DoF ---
void Cmd_Bus_Arm6DOF_GetPos1(uint8_t *data);
void Cmd_Bus_Arm6DOF_GetPos2(uint8_t *data);
void Cmd_Bus_Arm6DOF_GetGripper(uint8_t *data, uint8_t count);
void Cmd_Bus_Arm6DOF_GetSmartKutongData(uint8_t *data);

// --- Universal ---
void Cmd_Bus_Universal_SetResponse(uint8_t* data);
void Cmd_Bus_Universal_WeightResponse(uint8_t *data);
void Cmd_Bus_Universal_InputResponse(uint8_t *data);
void Cmd_Bus_Universal_StepperPositionResponse(uint8_t *data);
void Cmd_Bus_Universal_AutomationSequenceStateResponse(uint8_t* data);
void Cmd_Bus_Universal_DistanceResponse(uint8_t* data);

// --- Science ---
void Cmd_Bus_Science_GetTemperature1(uint8_t* data);
void Cmd_Bus_Science_GetTemperature2(uint8_t* data);
void Cmd_Bus_Science_GetHumidity(uint8_t* data);
void Cmd_Bus_Science_GetAtmosphere(uint8_t* data);
void Cmd_Bus_Science_GetWeight(uint8_t* data);
void Cmd_Bus_Science_GetStatus(uint8_t* data);

// --- Mobilab v2 ---
void Cmd_Bus_Mobilab_GetTemperature(uint8_t* data);

// --- Fallback handlers ---
void Cmd_Bus_UnknownHandler(can_packet_t* msg);
void Cmd_Bus_EmptyHandler(uint8_t* msg);

// --- Drill ---
void Cmd_Bus_Drill_GetWeight(uint8_t* data);
void Cmd_Bus_Drill_Telemetry(uint8_t* data);

// -- Power Distribution ---
void Cmd_Bus_PowerDistribution_VoltageResponse(uint8_t* data);
void Cmd_Bus_PowerDistribution_SensorResponse(uint8_t* data);
/*
 *  TX Frames
 */

// --- Motor ---
void Cmd_Bus_Motor_SetWheels();
void Cmd_Bus_Motor_Calibrate(uint8_t channel);

// --- Arm 6DoF
void Cmd_Bus_Arm6DOF_SetPosVel();
void Cmd_Bus_Arm6DOF_SetTorque();
void Cmd_Bus_Arm6DOF_SetPos();
void Cmd_Bus_Arm6DOF_SetVelocity();
void Cmd_Bus_Arm6DOF_SetGripper();
void Cmd_Bus_Arm6DOF_SetParams();
void Cmd_Bus_Arm6DOF_PositioningStart(uint8_t ID);
void Cmd_Bus_Arm6DOF_PositioningAbort();
void Cmd_Bus_Arm6DOF_KeyboardClick();
void Cmd_Bus_Arm6DOF_SetActualPos(uint8_t ID, uint8_t MSB, uint8_t LSB);
void Cmd_Bus_Arm6DOF_SoftReset();
void Cmd_Bus_Arm6DOF_SmartKutongToggle();
void Cmd_Bus_Arm6DOF_Autoclick_SetPos(uint8_t pos);

// --- Drill ---
void Cmd_Bus_Drill_A_Bridge_Set(uint8_t direction, uint8_t speed);
void Cmd_Bus_Drill_B_Bridge_Set(uint8_t direction, uint8_t speed);
void Cmd_Bus_Drill_C_Bridge_Set(uint8_t direction, uint8_t speed);
void Cmd_Bus_Drill_Autonomy(uint8_t* data);
void Cmd_Bus_Drill_SetGear(uint8_t* data);

// --- UEUOS v2 ---
void Cmd_Bus_Ueuos_SetState(const uint8_t* data);
void Cmd_Bus_Ueuos_SetColor(const uint8_t* data);
void Cmd_Bus_Ueuos_SetEffect(const uint8_t* data);

// --- Universal ---
void Cmd_Bus_Universal_SetDigitalOutput(uint8_t* data);
void Cmd_Bus_Universal_SetPWMOutput(uint8_t* data);
void Cmd_Bus_Universal_SetLEDDriver(uint8_t* data);
void Cmd_Bus_Universal_SetHBridge(uint8_t* data);
void Cmd_Bus_Universal_SetStepperPosition(uint8_t* data);
void Cmd_Bus_Universal_StepperHomingRequest(uint8_t* data);
void Cmd_Bus_Universal_WeightRequest(uint8_t* data);
void Cmd_Bus_Universal_InputRequest(uint8_t* data);
void Cmd_Bus_Universal_StepperPositionRequest(uint8_t* data);
void Cmd_Bus_Universal_AutomationSequenceBeginRequest(uint8_t* data);
void Cmd_Bus_Universal_AutomationSequenceStateRequest(uint8_t* data);
void Cmd_Bus_Universal_WeightTareRequest(uint8_t* data);
void Cmd_Bus_Universal_SetDistanceMeasurement(const uint8_t* data);
// --- Science ---

// --- Mobilab v2 ---
void Cmd_Bus_Mobilab_SetPump(const uint8_t* data);
void Cmd_Bus_Mobilab_SetHeater(const uint8_t* data);
void Cmd_Bus_Mobilab_SetBacklight(const uint8_t* data);
void Cmd_Bus_Mobilab_SetAux(const uint8_t* data);
void Cmd_Bus_Mobilab_SetServo(const uint8_t* data);
// --- Mux --
void Cmd_Bus_Mux_SetChannel(uint8_t vtx, uint8_t channel);
void Cmd_Bus_Mux_SetCam(uint8_t vtx, uint8_t cam);
void Cmd_Bus_Mux_SetPower(uint8_t vtx, uint8_t power);

#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_CMD_H
