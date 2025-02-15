#ifndef KALMAN_ELECTRONICS_MASTER_V3_COMMON_H
#define KALMAN_ELECTRONICS_MASTER_V3_COMMON_H

#include "FreeRTOS.h"
#include "task.h"

#include "queues.h"
#include "tcan114x-driver//TCAN114x.h"
#include "gpio_expander.h"
#include "config.h"


#define TIMER_COMM_TIMEOUT_BYPASS 0
#if TIMER_COMM_TIMEOUT_BYPASS != 0
    #warning "Arm & Motor timeouts disabled on master, if you don't know what are you doing change TIMER_COMM_TIMEOUT_BYPASS to 0!"
#endif

// GPIO Expander
extern TaskHandle_t GpioExpanderTaskHandle;
// UART
extern TaskHandle_t UARTParserTaskHandle;
extern TaskHandle_t UARTHandlerTaskHandle;
extern TaskHandle_t UARTEncoderTaskHandle;
// CAN
extern TaskHandle_t CANManagerTaskHandle;
extern TaskHandle_t CANHandlerTaskHandle;

extern TaskHandle_t StatusInfoTaskHandle;




typedef enum {
    RF_ON = 1,
    RF_OFF = 0
} rf_status_t;

typedef enum {
	ESTOP_ENGAGED = 1, //odcięte
	ESTOP_DISENGAGED = 0

} remote_estop_status_t;

extern rf_status_t RF_status;
extern remote_estop_status_t remoteEstopStatus;



#endif //KALMAN_ELECTRONICS_MASTER_V3_COMMON_H
