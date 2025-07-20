#include "can_manager.h"


StaticTask_t CANManagerTaskBuffer;
StackType_t CANManagerTaskStack[CAN_MANAGER_TASK_STACK_SIZE];
uint32_t can_status = 0;

uint32_t __get_code_from_length(uint8_t bytes_length);
uint8_t __get_length_from_code(uint32_t length_code);

// --- CAN Filters

const uint8_t canlib_rx_list[CANLIB_RX_LIST_COUNT] = {
        CAN_FILTER_ID_COMMON,   //! obowiazkowe dla kazdego modulu!
        CAN_FILTER_ID_MOTOR,
        CAN_FILTER_ID_ARM,
        CAN_FILTER_ID_UNIVERSAL2_1,
        CAN_FILTER_ID_UNIVERSAL2_2,
        CAN_FILTER_ID_SCIENCE,
        CAN_FILTER_ID_MUX,
        CAN_FILTER_ID_6DOF,
        CAN_FILTER_ID_MOBILAB,
        CAN_FILTER_ID_UEUOS,
		CAN_FILTER_ID_DRILL
};

void CanManager_FilterConfig();

void CANManager_Task(void *argument) {

	for(int i = 0; i < FDCAN_DEFS_COUNT; i++) {
		HAL_FDCAN_DeInit(fdcan_defs[i].fdcan_handle);
		fdcan_defs[i].fdcan_handle->Init.StdFiltersNbr = CANLIB_RX_LIST_COUNT;
		HAL_FDCAN_Init(fdcan_defs[i].fdcan_handle);

		//configure filters
		CanManager_FilterConfig(fdcan_defs[i].fdcan_handle);

		//start FDCAN periphery
		HAL_FDCAN_Start(fdcan_defs[i].fdcan_handle);

		// setup notifications
		HAL_FDCAN_ActivateNotification(fdcan_defs[i].fdcan_handle, FDCAN_IT_LIST_RX_FIFO0, 0);
		HAL_FDCAN_ActivateNotification(fdcan_defs[i].fdcan_handle, FDCAN_IT_LIST_TX_FIFO_ERROR, 0);

        /* Disabling arbitration protocol error */
		HAL_FDCAN_ActivateNotification(fdcan_defs[i].fdcan_handle, FDCAN_IT_LIST_PROTOCOL_ERROR & ~FDCAN_FLAG_ARB_PROTOCOL_ERROR, 0);

        HAL_GPIO_WritePin(tcan_defs[i].cs.port, tcan_defs[i].cs.pin, GPIO_PIN_SET);
        TCAN114x_Init(&(tcan_defs[i].tcan), spi_defs[TCAN_SPI_ID].spi_handle, tcan_defs[i].cs.port, tcan_defs[i].cs.pin);
        TCAN114x_getDeviceID(&(tcan_defs[i].tcan));
        TCAN114x_setMode(&(tcan_defs[i].tcan), normal);


	}


    while (1) {
        can_packet_t msg;
        xQueueReceive(can_handler_outgoing_packet_queue, &msg, portMAX_DELAY);

        // Create tx packet info header
        FDCAN_TxHeaderTypeDef can_header;
        can_header.Identifier = msg.cmd;
        can_header.IdType = FDCAN_STANDARD_ID;
        can_header.TxFrameType = FDCAN_DATA_FRAME;
        can_header.DataLength = __get_code_from_length(msg.arg_count);
        can_header.ErrorStateIndicator = FDCAN_ESI_PASSIVE;
        can_header.BitRateSwitch = FDCAN_BRS_OFF;
        can_header.FDFormat = FDCAN_FD_CAN;
        can_header.TxEventFifoControl = FDCAN_NO_TX_EVENTS;
        can_header.MessageMarker = 0;




        // Wait for space in CAN TX FIFO
        while(!HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan1) && !HAL_FDCAN_GetTxFifoFreeLevel(&hfdcan2)) {
        	vTaskDelay(1 / portTICK_PERIOD_MS);
        }

        // Add the packet to be sent from the TX FIFO
        HAL_StatusTypeDef res = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan1, &can_header, msg.args);
        res = HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan2, &can_header, msg.args);
        if (res != HAL_OK) {
            __asm__("nop");
        	//GpioExpander_SetLed(LED_CAN_ERR, on, 50); //TODO: can err led is not working
        }
    }
}

void CanManager_FilterConfig(FDCAN_HandleTypeDef *hfdcan) {
    //configure global filter - behaviour of frames non matching any filters
    HAL_FDCAN_ConfigGlobalFilter(hfdcan, FDCAN_REJECT, FDCAN_REJECT,
                                 FDCAN_REJECT_REMOTE, FDCAN_REJECT_REMOTE);

    FDCAN_FilterTypeDef filter;

#if CANMANAGER_ACCEPT_ALL_FRAMES == 1
    //filtr akceptujący wszystkie otrzymane ramki
	filter.IdType = FDCAN_STANDARD_ID;
	filter.FilterIndex = 0;
	filter.FilterType = FDCAN_FILTER_RANGE;
	filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
	filter.FilterID1 = 0x000;
	filter.FilterID2 = 0x7FF;
	HAL_FDCAN_ConfigFilter(&hfdcan1, &filter);

#else
    //inicjalizacja filtrów akceptujących ramki ze zdefiniowanych modułów
    //TODO: use range/dual filter type
    for (uint8_t filter_number = 0; filter_number < CANLIB_RX_LIST_COUNT; filter_number++) {
        filter.IdType = FDCAN_STANDARD_ID;
        filter.FilterIndex = filter_number;
        filter.FilterType = FDCAN_FILTER_MASK;
        filter.FilterConfig = FDCAN_FILTER_TO_RXFIFO0;
        filter.FilterID1 = canlib_rx_list[filter_number];
        filter.FilterID2 = CAN_FILTER_MASK;
        HAL_FDCAN_ConfigFilter(hfdcan, &filter);
    }
#endif
}

void HAL_FDCAN_RxFifo0Callback(FDCAN_HandleTypeDef *hfdcan, uint32_t RxFifo0ITs) {
    FDCAN_RxHeaderTypeDef header;
    can_packet_t msg;
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    HAL_FDCAN_GetRxMessage(hfdcan, FDCAN_RX_FIFO0, &header, msg.args);
    //TODO: error state indicator support

    msg.cmd = header.Identifier;
	msg.arg_count = __get_length_from_code(header.DataLength);

    //TODO: timeouts
    xQueueSendFromISR(can_handler_incoming_packet_queue, &msg, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}


void HAL_FDCAN_TxFifoEmptyCallback(FDCAN_HandleTypeDef *hfdcan) {

}

void HAL_FDCAN_ErrorCallback(FDCAN_HandleTypeDef *hfdcan) {
    can_status = HAL_FDCAN_GetError(hfdcan);

    GpioExpander_SetLed(LED_CAN_ERR, on, 100);

    switch (can_status) {
        case HAL_FDCAN_ERROR_NONE:
            break;

        case HAL_FDCAN_ERROR_TIMEOUT:
            break;

        case HAL_FDCAN_ERROR_NOT_INITIALIZED:
            break;

        case HAL_FDCAN_ERROR_NOT_READY:
            break;

        case HAL_FDCAN_ERROR_NOT_STARTED:
            break;

        case HAL_FDCAN_ERROR_NOT_SUPPORTED:
            break;

        case HAL_FDCAN_ERROR_PARAM:
            break;

        case HAL_FDCAN_ERROR_PENDING:
            break;

        case HAL_FDCAN_ERROR_RAM_ACCESS:
            break;

        case HAL_FDCAN_ERROR_FIFO_EMPTY:
            break;

        case HAL_FDCAN_ERROR_FIFO_FULL:
            break;

        case HAL_FDCAN_ERROR_LOG_OVERFLOW:
            break;

        case HAL_FDCAN_ERROR_RAM_WDG:
            break;

        case HAL_FDCAN_ERROR_PROTOCOL_ARBT:
            break;

        case HAL_FDCAN_ERROR_PROTOCOL_DATA:
            break;

        case HAL_FDCAN_ERROR_RESERVED_AREA:
            break;
    }

}
void HAL_FDCAN_ErrorStatusCallback(FDCAN_HandleTypeDef *hfdcan, uint32_t ErrorStatusITs) {
    GpioExpander_SetLed(LED_CAN_ERR, on, 100);
}

//implementation of function converting HAL code to actual length
uint8_t __get_length_from_code(uint32_t length_code){
    switch (length_code) {
        case FDCAN_DLC_BYTES_0: return 0;
        case FDCAN_DLC_BYTES_1: return 1;
        case FDCAN_DLC_BYTES_2: return 2;
        case FDCAN_DLC_BYTES_3: return 3;
        case FDCAN_DLC_BYTES_4: return 4;
        case FDCAN_DLC_BYTES_5: return 5;
        case FDCAN_DLC_BYTES_6: return 6;
        case FDCAN_DLC_BYTES_7: return 7;
        case FDCAN_DLC_BYTES_8: return 8;
        case FDCAN_DLC_BYTES_12: return 12;
        case FDCAN_DLC_BYTES_16: return 16;
        case FDCAN_DLC_BYTES_20: return 20;
        case FDCAN_DLC_BYTES_24: return 24;
        case FDCAN_DLC_BYTES_32: return 32;
        case FDCAN_DLC_BYTES_48: return 48;
        case FDCAN_DLC_BYTES_64: return 64;
        default:
            return 0x0;
    }
}

//implementation of function converting actual length to HAL code
uint32_t __get_code_from_length(uint8_t bytes_length){
    switch (bytes_length) {
        case 0: return FDCAN_DLC_BYTES_0;
        case 1: return FDCAN_DLC_BYTES_1;
        case 2: return FDCAN_DLC_BYTES_2;
        case 3: return FDCAN_DLC_BYTES_3;
        case 4: return FDCAN_DLC_BYTES_4;
        case 5: return FDCAN_DLC_BYTES_5;
        case 6: return FDCAN_DLC_BYTES_6;
        case 7: return FDCAN_DLC_BYTES_7;
        case 8: return FDCAN_DLC_BYTES_8;
        default:
            if (bytes_length <= 12) return FDCAN_DLC_BYTES_12;
        if (bytes_length <= 16) return FDCAN_DLC_BYTES_16;
        if (bytes_length <= 20) return FDCAN_DLC_BYTES_20;
        if (bytes_length <= 24) return FDCAN_DLC_BYTES_24;
        if (bytes_length <= 32) return FDCAN_DLC_BYTES_32;
        if (bytes_length <= 48) return FDCAN_DLC_BYTES_48;
        if (bytes_length <= 64) return FDCAN_DLC_BYTES_64;
        return 0x0;
    }
}
