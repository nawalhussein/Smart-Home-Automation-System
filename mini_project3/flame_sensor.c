/*
 * flame_sensor.c
 *
 *  Created on: Sep 30, 2025
 *      Author: Eng.Nawal Hussein
 */
#include <avr/io.h>
#include "flame_sensor.h"
#include "common_macros.h"
void FlameSensor_init(void) {
/*Initializes the flame sensor pin direction.*/
	DDR(FLAME_SENSOR_PORT)&=~(1<<FLAME_SENSOR_PIN);
}
uint8 FlameSensor_getValue(void){
/*Reads the value from the flame sensor and returns it.*/
	return BIT_IS_SET(DDR(FLAME_SENSOR_PORT),FLAME_SENSOR_PIN);
}
