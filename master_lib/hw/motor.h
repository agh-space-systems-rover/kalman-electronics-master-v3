#ifndef KALMAN_ELECTRONICS_MASTER_V3_MOTOR_H
#define KALMAN_ELECTRONICS_MASTER_V3_MOTOR_H

#include "stdint.h"


typedef struct {
    uint8_t umc_temp;
    uint8_t carrier_temp;
    uint8_t gate_driver_temp;
} motor_temperature_t; 

/**
 * struktura reprezentujaca modul Motor Controller v2 / UMC
 */
typedef struct {
    //dane wysylane cyklicznie do modulu
    int8_t required_speed[4];   //!< zadane predkosci kolejnych kol, wartosci: -100..+100, procenty pelnej predkosci (dodatnie - jazda do przodu)
    int8_t required_angle[4];   //!< zadane wychylenia kolejnych modulow skretu, wartosci: -90..+90, stopnie wzgledem polozenia domyslnego (dodatnie - skret w prawo)

    //dane odbierane cyklicznie od modulu
    int16_t current_speed[4];   //!< aktualne predkosci obrotu kol, wartosci: predkosc katowa w 0.1 stopnia na sekunde (dodatnie - jazda do przodu)
    int8_t  current_angle[4];   //!< aktualne wychylenia modulow skretu, wartosci: -90..+90, stopnie wzgledem polozenia domyslnego (dodatnie - skret w prawo)
    uint8_t supply_voltage;     //!< aktualna wartosc napiecia zasilania czesci mocy (w 0.1V)
    uint8_t limit_status;       //!< stany krancowek silnikow skretu
    uint8_t motor_status;       //!< status wszystkich silnikow
    uint8_t status;             //!< status kontrolera

    struct {
        motor_temperature_t propulsion_temperature[4];
        motor_temperature_t turn_temperature[4];
    } motor_temperature;
} motor_controller_t;


#endif //KALMAN_ELECTRONICS_MASTER_V3_MOTOR_H
