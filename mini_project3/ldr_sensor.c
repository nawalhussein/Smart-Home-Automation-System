/*
 * ldr_sensor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Nawal Hussein
 */
#include "ldr_sensor.h"
#include "adc.h"
static uint16 intensity,adc_raw;

uint16 LDR_getLightIntensity(void){
	adc_raw = ADC_readChannel(LDR_SENSOR_CHANNEL_ID);
	/*Light intensity of the 3 LEDs is inversely proportional to (Vin/Vref)
	 * as Vin is max when the sensor is in darkness
	 */
	intensity=(uint16)(LDR_SENSOR_MAX_LIGHT_INTENSITY*(1.0f-((float)adc_raw/1024.0f)));
	return 100-intensity;
}
