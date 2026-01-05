/*
 * flame_sensor.h
 *
 *  Created on: Sep 30, 2025
 *      Author: Eng.Nawal Hussein
 */

#ifndef FLAME_SENSOR_H_
#define FLAME_SENSOR_H_

#include "std_types.h"
#define FLAME_SENSOR_PORT D
#define FLAME_SENSOR_PIN 2
#define _DDR(port) DDR##port
#define DDR(port)  _DDR(port)
#define _PORT(port) PORT##port
#define PORT(port)  _PORT(port)

void FlameSensor_init(void);
uint8 FlameSensor_getValue(void);

#endif /* FLAME_SENSOR_H_ */
