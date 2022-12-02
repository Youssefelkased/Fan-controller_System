/******************************************************************************
 *
 * Module: APP
 *
 * File Name: main.c
 *
 * Description: Source file for the main function
 *
 * Author: Youssef Mamdouh
 *
 *******************************************************************************/
#include "adc.h"
#include "lcd.h"
#include "lm35_sensor.h"
#include "pwm.h"
#include "std_types.h"
#include "motor.h"

int main()
{
	uint8 temp;
	/* initialization functions calling	*/
	ADC_ConfigType ADC_currentConfig={HIGH,DF_8};	/* ADC structure for configuration */
	LCD_init();
	ADC_init(&ADC_currentConfig);
	DcMotor_Init();

	/* LCD initial display */
	LCD_moveCursor(0, 2);
	LCD_displayString("Fan is ");
	LCD_moveCursor(1, 2);
	LCD_displayString("Temp =    C");



	while(1)
	{
		temp = LM35_getTemperature();

			/*	display temperature and turn on fan on certain temperatures	*/
		if (temp < 30) {
			LCD_moveCursor(0, 9);
			LCD_displayString("OFF");
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DcMotor_Rotate(STOP, 0);
			LCD_displayCharacter(' ');
		} else if (temp < 60 && temp>30) {
			LCD_moveCursor(0, 9);
			LCD_displayString("ON ");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW, 25);
			LCD_displayCharacter(' ');
		} else if (temp < 90 && temp>60) {
			LCD_moveCursor(0, 9);
			LCD_displayString("ON ");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW, 50);
			LCD_displayCharacter(' ');
		} else if (temp < 120 && temp>90) {
			LCD_moveCursor(0, 9);
			LCD_displayString("ON ");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW, 75);
			if (temp < 100) {
				LCD_displayCharacter(' ');
			}
		} else {
			LCD_moveCursor(0, 9);
			LCD_displayString("ON ");
			LCD_displayCharacter(' ');
			LCD_moveCursor(1, 9);
			LCD_intgerToString(temp);
			DcMotor_Rotate(CW, 100);
		}
	}
	return 1;
}
