/*
 * ldr_sensor.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Nawal Hussein
 */

#ifndef LDR_SENSOR_H_
#define LDR_SENSOR_H_
#include "std_types.h"
/*configurations*/
#define LDR_SENSOR_CHANNEL_ID 0
#define LDR_SENSOR_MAX_VOLT_VALUE 2.56
#define LDR_SENSOR_MAX_LIGHT_INTENSITY 100
/*functions*/
uint16 LDR_getLightIntensity(void);
#endif /* LDR_SENSOR_H_ */
