/******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: motor.c
 *
 * Description: source file for the ATmega12 motor driver
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/

#include "pwm.h"
#include "gpio.h"
#include "common_macros.h"
#include "motor.h"
#include "adc.h"
#include <avr/io.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void DcMotor_Init(void)	/* Initialization for DC motor */
{

	/* configure pin PC0 and PC1 as output pins */
	GPIO_setupPinDirection(PORTB_ID, PIN0_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(PORTB_ID, PIN1_ID, PIN_OUTPUT);

	/* Motor is stop at the beginning */
	GPIO_writePort(PORTB_ID, 0XFA);
	DcMotor_Rotate(STOP, 0);
}

void DcMotor_Rotate(DcMotor_State state,uint8 speed)	/* starts rotation at specific speed */
{
	uint8 dutyCycle;
	if(speed == 100){
		dutyCycle=255;
	}else{
		dutyCycle=(speed*256)/100;
	}
	/* check if the first push button at PA0 is pressed/not */
	if(state==CW)
	{
		// Rotate the motor --> clock wise
		PWM_Timer0_Start(dutyCycle);
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_HIGH);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
	}

	/* check if the third push button at PA2 is pressed/not */
	else if(state==STOP)
	{
		// Stop the motor
		PWM_Timer0_Start(0);
		GPIO_writePin(PORTB_ID, PIN0_ID, LOGIC_LOW);
		GPIO_writePin(PORTB_ID, PIN1_ID, LOGIC_LOW);
	}

}
