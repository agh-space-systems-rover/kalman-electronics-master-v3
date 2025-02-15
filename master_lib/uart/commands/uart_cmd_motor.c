#include <string.h>
#include "uart_cmd.h"
#include "can/commands/can_cmd.h"

remote_estop_status_t remoteEstopStatus = ESTOP_DISENGAGED;

/**
 * Ustawianie zadanej prędkości obrotu oraz wychylenia modułów skrętu.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Motor_SetWheels(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_cyclic) {
            debug_printf("[%s] Motor SetWheels: %d %d %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
        //}

        // Update HW struct
		if(remoteEstopStatus == ESTOP_DISENGAGED) {
			for(uint8_t i = 0; i < 4; i++) {
				bus_motor.required_speed[i] = data[i];
				bus_motor.required_angle[i] = data[i + 4];
			}
		} else {
			for(uint8_t i = 0; i < 4; i++) {
				bus_motor.required_speed[i] = 0;
				bus_motor.required_angle[i] = 0;
			}
		}

        // Update motor master
        Cmd_Bus_Motor_SetWheels();

        // Reset periodical motor master timeout
        Timer_ResetTimeout(TIMER_CAN_TRAFFIC_SET_MOTOR);
        Timer_ResetTimeout(TIMER_MOTOR_TIMEOUT);

        Cmd_UART_BlinkLed(link_type);
    }
}

/**
 * Zdalne grzybowanie napędów
 */
void CMD_UART_Motor_RemoteEstop(uint8_t* data, uart_packet_link_t link_type) {
	remoteEstopStatus = data[0];

	uart_packet_t msg = {
			.cmd = UART_CMD_MOTOR_GET_REMOTE_ESTOP,
			.arg_count = UART_ARG_MOTOR_GET_REMOTE_ESTOP,
			.origin = logic.link_type | LINK_RF_UART,
	};

	msg.args[0] = remoteEstopStatus;

	Queues_SendUARTFrame(&msg);
}



/**
 * Zlecenie kalibracji rozregulowanego modułu skrętu.
 * @param data      wskaźnik na bufor odebranych danych
 * @param link_type łącze komunikacyjne, na którym odebrano ramkę
 */
void Cmd_UART_Motor_Calibrate(uint8_t *data, uart_packet_link_t link_type) {
    if ((link_type == LINK_RF_UART) ||  (link_type == logic.link_type)) {
        //if (logic_flash.debug_info & debug_comm_control) {
            debug_printf("[%s] Motor Calibrate: %d %d %d %d %d %d\r\n",
                    (link_type == LINK_RF_UART ? "RF" : "WiFi/Auto"),
                    data[0], data[1], data[2], data[3], data[4], data[5]);
        //}

        //tylko po regulaminowym czasie bezczynnosci
        if (Logic_GetUptime() >= LOGIC_COMM_START_TIME) {
            static uint8_t buf[] = "do it";
            if (memcmp(data, buf, 5) == 0) {
                Cmd_Bus_Motor_Calibrate(data[5]);
            }
        }

        Cmd_UART_BlinkLed(link_type);
    }
}



/**
 * Zwracanie aktualnej prędkości obrotu oraz wychylenia modułów skrętu.
 */
void Cmd_UART_Motor_GetWheels(void) {
    uart_packet_t msg = {
        .cmd = UART_CMD_MOTOR_GET_WHEELS,
        .arg_count = UART_ARG_MOTOR_GET_WHEELS,
        .origin = logic.link_type | LINK_RF_UART, // When using autonomy mode, send a frame onto rf channel as well
    };

    for (uint8_t i=0; i<4; i++) {
        uint16_t speed = (uint16_t)(bus_motor.current_speed[i]);
        msg.args[2*i]   = (uint8_t)(speed >> 8);
        msg.args[2*i+1] = (uint8_t)(speed & 0xFF);
        msg.args[8+i]   = (uint8_t)(bus_motor.current_angle[i]);

        bus_motor.current_speed[i] = 0;
    }

    Queues_SendUARTFrame(&msg);
}

/**
 * Zwracanie ostatniego odczytu z temperatury silnikow
 */
void Cmd_UART_Motor_GetTemperature(void) {
    uart_packet_t msg = {
        .cmd = UART_CMD_MOTOR_GET_TEMPERATURE,
        .arg_count = UART_ARG_MOTOR_GET_TEMPERATURE,
        .origin = logic.link_type | LINK_RF_UART, // When using autonomy mode, send a frame onto rf channel as well
    };

    for(uint8_t i = 0; i < 4; i++)
        msg.args[i] = bus_motor.motor_temperature.propulsion_temperature[i];
    for(uint8_t i = 0; i < 4; i++)
        msg.args[4 + i] = bus_motor.motor_temperature.turn_temperature[i];

    Queues_SendUARTFrame(&msg);
}

