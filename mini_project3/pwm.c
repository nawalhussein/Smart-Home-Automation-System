/*
 * pwm.c
 *
 *  Created on: Sep 29, 2025
 *      Author: Nawal Hussein
 */
#include <avr/io.h>
#include "pwm.h"

/* Initialize PWM on Timer0 */
void PWM_Timer0_Init(void){
    /* Set Fast PWM mode, non-inverting, prescaler = F_CPU/1024 */
    TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<CS02) | (1<<CS00) | (1<<COM01);
    /* Start from 0 */
    TCNT0 = 0;
    OCR0  = 0;
    /* Set OC0 (PB3) as output */
    DDRB |= (1<<PB3);
}

/* Update duty cycle*/
void PWM_Timer0_SetDuty(uint8 duty_cycle){
    if(duty_cycle > 100) duty_cycle = 100;
    OCR0 = ((uint16)duty_cycle*255)/100;
}

