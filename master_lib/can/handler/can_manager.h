#ifndef KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H
#define KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H

#include "fdcan.h"
#include "can/can_packet.h"
#include "shared/common.h"
#include "spi.h"
#include "gpio.h"

#define CANMANAGER_ACCEPT_ALL_FRAMES 0

#define CAN_MANAGER_TASK_PRIORITY 9
#define CAN_MANAGER_TASK_STACK_SIZE 2048

extern StaticTask_t CANManagerTaskBuffer;
extern StackType_t CANManagerTaskStack[CAN_MANAGER_TASK_STACK_SIZE];

void CANManager_Task(void *argument);


// --- CAN Filters

#define CAN_FILTER_MASK                 0xF0
#define CAN_FILTER_ID_MOTOR             0x10
#define CAN_FILTER_ID_ARM               0x20
#define CAN_FILTER_ID_COMMON            0x30
#define CAN_FILTER_ID_UNIVERSAL2_1      0x50
#define CAN_FILTER_ID_UNIVERSAL2_2      0x60
#define CAN_FILTER_ID_UEUOS             0x70
#define CAN_FILTER_ID_SCIENCE           0x90
#define CAN_FILTER_ID_MUX               0xA0
#define CAN_FILTER_ID_6DOF              0xB0
#define CAN_FILTER_ID_MOBILAB           0xC0
#define CAN_FILTER_ID_DRILL			    0xD0

#define CANLIB_RX_LIST_COUNT            12


#endif //KALMAN_ELECTRONICS_MASTER_V3_CAN_MANAGER_H
