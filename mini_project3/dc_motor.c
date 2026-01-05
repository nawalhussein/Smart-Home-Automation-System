/*
 * dc_motor.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Eng.Nawal Hussein
 */

#include "dc_motor.h"
#include "pwm.h"
#include <avr/io.h>

void DcMotor_Init(void) {
    DDR(IN1_PORT)|=(1<<IN1_PIN);
    DDR(IN2_PORT)|=(1<<IN2_PIN);
    PORT(IN1_PORT)&=~(1<<IN1_PIN);
    PORT(IN2_PORT)&=~(1<<IN2_PIN);
}

void DcMotor_Rotate(DcMotor_State state, uint8 speed) {
    switch(state){
    case CW:
        PORT(IN1_PORT)|=(1<<IN1_PIN);
        PORT(IN2_PORT)&=~(1<<IN2_PIN);
        PWM_Timer0_SetDuty(speed);
        break;

    case CCW:
        PORT(IN1_PORT)&=~(1<<IN1_PIN);
        PORT(IN2_PORT)|=(1<<IN2_PIN);
        PWM_Timer0_SetDuty(speed);
        break;

    case STOP:
        PORT(IN1_PORT)&=~(1<<IN1_PIN);
        PORT(IN2_PORT)&=~(1<<IN2_PIN);
        PWM_Timer0_SetDuty(0);
        break;
    }
}

