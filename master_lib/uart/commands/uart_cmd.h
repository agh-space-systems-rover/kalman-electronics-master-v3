#ifndef KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H
#define KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H

#include "uart/uart_packet.h"
#include "shared/common.h"
#include "shared/logic.h"
#include "hw/hw.h"
#include "timers/timer.h"


/** RX frames */

// --- Master ---
void Cmd_UART_Master_SetLink(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_SilentMode(uint8_t* data, uart_packet_link_t link_type);

// -- Power Distribution ---
void Cmd_UART_PowerDistribution_GetVoltage(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_PowerDistribution_GetSensor(uint8_t* data, uart_packet_link_t link_type);

// --- Motor ---
void Cmd_UART_Motor_SetWheels(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Motor_Calibrate(uint8_t* data, uart_packet_link_t link_type);
void CMD_UART_Motor_RemoteEstop(uint8_t* data, uart_packet_link_t link_type);

// --- Arm 6DoF ---
void Cmd_UART_Arm6DOF_SetPos(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetPosVel(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetTorque(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetVelocity(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetGripper(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_Autoclick_SetPos(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_PositioningStart(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_PositioningAbort(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SetActualPos(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_KeyboardClick(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_SoftReset(uint8_t *data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_GetProbeRequest(uint8_t* data, uart_packet_link_t link_type);

// --- Drill ---
void Cmd_UART_Drill_A_Bridge_Set(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Drill_B_Bridge_Set(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Drill_C_Bridge_Set(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Drill_GetWeightRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Drill_Autonomy(uint8_t* data, uart_packet_link_t link_type);

// --- UEUOS v2 ---
void Cmd_UART_Ueuos_SetState(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Ueuos_SetColor(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Ueuos_SetEffect(uint8_t *data, uart_packet_link_t link_type);

// --- Universal ---

void Cmd_UART_Universal_SetDigitalOutput(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_SetPWMOutput(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_SetLEDDriver(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_SetHBridge(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_SetStepperPosition(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_StepperHomingRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_WeightRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_WeightTareRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_InputRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_StepperPositionRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_AutomationSequenceBeginRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Universal_SetDistanceMeasurement(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_GetProbeEsp(uint8_t* data, uart_packet_link_t link_type);

// --- Science ---
void Cmd_UART_Science_GetSamplesRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Science_GetWeightRequest(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Science_GetAtmosphereRequest(uint8_t* data, uart_packet_link_t link_type);

// --- Mobilab v2 ---
void Cmd_UART_Mobilab_SetPump(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mobilab_SetHeater(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mobilab_SetBacklight(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mobilab_SetAux(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mobilab_SetServo(uint8_t* data, uart_packet_link_t link_type);

// --- Mux ---
void Cmd_UART_Mux_SetCam(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mux_SetChannel(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Mux_SetPower(uint8_t* data, uart_packet_link_t link_type);

// --- Custom ---
void Cmd_UART_CustomToRF(uint8_t* data, uint8_t len);
void Cmd_UART_CustomToUART(uint8_t* data, uint8_t len);
void Cmd_UART_SupervisorToRF(uint8_t* data, uint8_t len);
void Cmd_UART_SupervisorToUART(uint8_t* data, uint8_t len);
void Cmd_UART_ESP32_To_RF(uint8_t* data, uint8_t len);
void Cmd_UART_RF_To_ESP32(uint8_t* data, uint8_t len);
void Cmd_UART_ARM_CustomToUART(uint8_t* data, uint8_t len);
void Cmd_UART_ARM_CustomToRF(uint8_t* data, uint8_t len);

// --- Unknown ---
void Cmd_UART_UnknownHandler(uart_packet_t* msg);

/** TX frames */

// --- Master ---
void Cmd_UART_Master_SetLinkResponse(uart_packet_link_t new_link);

// --- Motor ---
void Cmd_UART_Motor_GetWheels(void);
void Cmd_UART_Motor_GetTemperature(void);

// --- Arm 6DoF ---
void Cmd_UART_Arm6DOF_GetGripper();
void Cmd_UART_Arm6DOF_GetPos(uint8_t* data, uart_packet_link_t link_type);
void Cmd_UART_Arm6DOF_CM4(uint8_t* data, uart_packet_link_t link_type);

// --- Universal ---
void Cmd_UART_Universal_SetResponse(uint8_t* data);
void Cmd_UART_Universal_WeightResponse(uint8_t* data);
void Cmd_UART_Universal_InputResponse(uint8_t* data);
void Cmd_UART_Universal_StepperPositionResponse(uint8_t* data);
void Cmd_UART_Universal_AutomationSequenceStateResponse(uint8_t* data);
void Cmd_UART_Universal_DistanceResponse(uint8_t* data);
// --- Science ---
void Cmd_UART_Science_GetAtmosphere(uint8_t id);
void Cmd_UART_Science_GetWeight(uint8_t id, uint8_t loadcell_index);
void Cmd_UART_Science_GetSamples(uint8_t id, uint8_t sample_index);

// --- Mobilab ---
void Cmd_UART_Mobilab_GetTemperature(uint8_t id);

// --- Drill ---
void Cmd_UART_Drill_GetWeight(int32_t weight);
void Cmd_UART_Drill_Telemetry(uint8_t* data);


// --- Power Distribution ---
void Cmd_UART_PowerDistribution_VoltageResponse(uint8_t* data);
void Cmd_UART_PowerDistribution_SensorResponse(uint8_t* data);
/** Helpers */

void Cmd_UART_BlinkLed(uart_packet_link_t link_type);

#endif //KALMAN_ELECTRONICS_MASTER_V3_UART_CMD_H
