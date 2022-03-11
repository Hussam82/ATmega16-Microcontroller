/*
 ============================================================================
 Name        : main.c
 Author      : Hussam Ali
 Description : FAN Controller System
 ============================================================================
 */



/******************************************* Used Libraries and Modules *****************************************/
#include "motor.h"
#include "lm35sensor.h"
#include "lcd.h"
#include "adc.h"


/******************************************* Main Function *****************************************/
int main(void)
{
	/* A variable to hold the temperature value */
	uint8 temp_read_value = 0;
	/* ADC Configuration
	 * using internal reference voltage 2.56V
	 * prescaler 8
	 */
	ADC_ConfigType s_configData = {REF_INT, F_CPU__8};
	/* Initialize ADC with the given Configuration */
	ADC_init(&s_configData);
	/* Initialize LCD */
	LCD_init();
	/* Initialize DC-MOTOR */
	DcMotor_Init();
	/* Start typing from the first row third column */
	LCD_displayStringRowColumn(0, 3, "FAN IS");
	/* Start typing from the second row third column */
	LCD_displayStringRowColumn(1, 3, "Temp =     C");
	while(1)
	{
		/* Read the sensor value and save the temperature */
		temp_read_value = LM35_getTemperature();
		/* Control the FAN according the temperature
		 * The fan rotates in a clock-wise direction
		 * according to the temperature value
		 */
		if(temp_read_value < 30)
		{
			LCD_displayStringRowColumn(0, 10, "OFF");
			DcMotor_Rotate(MOTOR_STOP, 0);
			/* To write in the second ROW */
			LCD_moveCursor(1, 10);
			LCD_integerToString(temp_read_value);
			LCD_displayCharacter(' ');
		}
		else if((temp_read_value >= 30) && (temp_read_value < 60))
		{
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(MOTOR_CW, 25);
			LCD_moveCursor(1, 10);
			LCD_integerToString(temp_read_value);
			LCD_displayCharacter(' ');
		}
		else if((temp_read_value >= 60) && (temp_read_value < 90))
		{
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(MOTOR_CW, 50);
			LCD_moveCursor(1, 10);
			LCD_integerToString(temp_read_value);
			LCD_displayCharacter(' ');
		}
		else if((temp_read_value >= 90) && (temp_read_value < 120))
		{
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(MOTOR_CW, 75);
			LCD_moveCursor(1, 10);
			LCD_integerToString(temp_read_value);
			LCD_displayCharacter(' ');
		}
		else if(temp_read_value >= 120)
		{
			LCD_displayStringRowColumn(0, 10, "ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(MOTOR_CW, 100);
			LCD_moveCursor(1, 10);
			LCD_integerToString(temp_read_value);
		}
		else
		{
			LCD_displayStringRowColumn(0, 10, "OFF");
		}
	}
}
