/*
 * mini_project3.c
 *
 * home automation system controller:
 * - controls fan speed via lm35 temperature.
 * - controls led lighting via ldr light intensity.
 * - includes a simple fire alert (int0).
 *
 *  Created on: Sep 29, 2025
 *  Author: Eng.Nawal Hussein
 */

#include "adc.h"
#include "buzzer.h"
#include "common_macros.h"
#include "dc_motor.h"
#include "gpio.h"
#include "lcd.h"
#include "ldr_sensor.h"
#include "led.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "std_types.h"
#include <avr/io.h>
#include <avr/interrupt.h>

uint8 fan_flag=0; // motor state (on/off)
/* system mode: 0=normal, 1=alarm */
uint8 system_mode=0;
/* flag to force lcd to show data when alarm ends */
uint8 force_redraw=0;

/* ----- lighting control ----- */
void lighting_control(void){
	/* use static variables to stop flicker */
	static uint16 last_intensity=0xFFFF;
	uint16 intensity=LDR_getLightIntensity();
	/* redraw if value changed or if alarm ended (force_redraw) */
	if(intensity != last_intensity || force_redraw == 1){
		LCD_displayStringRowColumn(1,8,"LDR=   %");
		LCD_moveCursor(1,12);
		LCD_intgerToString(intensity);
		last_intensity = intensity;

	}
	/* led control logic */
	if(intensity<=15){
		LED_on(LED_RED);
		LED_on(LED_GREEN);
		LED_on(LED_BLUE);


	}
	else if(intensity<=50){
		LED_on(LED_RED);
		LED_on(LED_GREEN);
		LED_off(LED_BLUE);

	}
	else if(intensity<=70){
		LED_on(LED_RED);
		LED_off(LED_GREEN);
		LED_off(LED_BLUE);

	}
	else{
		LED_off(LED_RED);
		LED_off(LED_GREEN);
		LED_off(LED_BLUE);
	}
}

/* ----- fan speed control (temperature) ----- */
void fan_speed_control(void){
	/* use static variables to stop flicker */
	static uint8 last_temp=0xFF;
	static uint8 last_fan_flag=0xFF;

	uint8 temp=LM35_getTemperature();
	/* redraw temp if value changed or if alarm ended */
	if(temp!=last_temp||force_redraw==1){
		LCD_displayStringRowColumn(1,0,"Temp=   ");
		// print temp value
		LCD_moveCursor(1,5);
		LCD_intgerToString(temp);
		last_temp=temp;
	}

	/* set fan flag based on temperature levels */
	if(temp>=25) fan_flag=1;
	else fan_flag=0;
	if(fan_flag){
		/* fan is on, set speed */
		if(temp>=40) DcMotor_Rotate(CW,100);
		else if(temp>=35) DcMotor_Rotate(CW,75);
		else if(temp>=30) DcMotor_Rotate(CW,50);
		else DcMotor_Rotate(CW,25);
	}
	else{
		DcMotor_Rotate(STOP,0);
	}

	/* redraw fan status if state changed or forced */
	if(fan_flag!=last_fan_flag||force_redraw==1){
		LCD_moveCursor(0,1);
		LCD_displayString("                "); // clear display area
		LCD_moveCursor(0,1);
		if(fan_flag)
			LCD_displayString("FAN is ON");
		else
			LCD_displayString("FAN is OFF");
		last_fan_flag=fan_flag;
	}
}

/* ----- int0 init (fire sensor) ----- */
void INT0_Init(void){
	// set pd2 (int0) as input
	DDRD&=~(1<<PD2);
	// trigger on rising edge
	MCUCR|=(1<<ISC00)|(1<<ISC01);
	// enable int0
	GICR|=(1<<INT0);
	// enable global interrupts
	sei();
}

/* ----- isr for fire detection ----- */
ISR(INT0_vect){
	// change to alarm mode
	system_mode=1;
	// start critical outputs
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,1,"Critical Alert!");
	LCD_displayStringRowColumn(1,1,"FIRE DETECTED!");
	Buzzer_on();
	DcMotor_Rotate(STOP,0);
	LED_off(LED_RED);
	LED_off(LED_GREEN);
	LED_off(LED_BLUE);
}

/* ----- main ----- */
int main(void){
	/* setup everything */
	LCD_init();
	DcMotor_Init();
	LEDS_init();
	ADC_init();
	Buzzer_init();
	PWM_Timer0_Init();
	PWM_Timer0_SetDuty(0);
	INT0_Init();
	/* first display setup */
	LCD_clearScreen();
	// show first sensor data
	lighting_control();
	fan_speed_control();
	while(1){
		if(system_mode==0){
			/* normal mode: run control loops */
			lighting_control();
			fan_speed_control();
		}
		else{
			/* alarm mode: check if fire is gone (pd2 is low) */
			if(BIT_IS_CLEAR(PIND,PD2)){
				Buzzer_off();
				// clear the alarm message
				LCD_clearScreen();
				// reset cursor position to C0, R0
				LCD_moveCursor(0,0);
				// set flag to force redraw
				force_redraw=1;
				// back to normal mode
				system_mode=0;
				// redraw the sensor data
				lighting_control();
				fan_speed_control();
				// clear force redraw flag
				force_redraw=0;
			}
		}
	}
}
