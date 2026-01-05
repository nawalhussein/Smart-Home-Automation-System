/*
 * dc_motor.h
 *
 *  Created on: Sep 29, 2025
 *      Author: Eng.Nawal Hussein
 */

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_
#include "std_types.h"
#define IN1_PORT B
#define IN1_PIN 0
#define IN2_PORT B
#define IN2_PIN 1
#define EN_PORT B
#define EN_PIN 3
#define _DDR(port) DDR##port
#define DDR(port)  _DDR(port)
#define _PORT(port) PORT##port
#define PORT(port)  _PORT(port)

typedef enum{
	CW,CCW,STOP
}DcMotor_State;

void DcMotor_Init(void);
void DcMotor_Rotate(DcMotor_State state, uint8 speed);

#endif /* DC_MOTOR_H_ */
