/*
 ============================================================================
 Name        : Exercise1.c
 Author      : Mohamed Tarek
 Description : Test the keypad driver with 7-segment
 Date        : 1/23/2014
 ============================================================================
 */

/* You can enhance the exercise by:
 * 1. Implement a 7-segment driver.
 * 2. 7-segment driver will use the gpio driver to access the 7-segment bits.
 * 3. Include the 7-segment driver here instead of accessing the gpio registers.
 * 4. Send the keypad number that you wish to display to the 7-segment driver.
 */

#include "lcd.h"
#include "adc.h"
#include "lm35sensor.h"
#include "avr/io.h"








int main(void)
{
	uint16 temp_read_value = 0;
	ADC_ConfigType s_configData = {REF_AREF, F_CPU__8};
	LCD_init();
	ADC_init(&s_configData);
	LCD_displayString("Temp =    C");
	while(1)
	{
		LCD_moveCursor(0, 7);
		temp_read_value = LM35_getTemperature();
		if(temp_read_value >= 100)
		{
			LCD_integerToString(temp_read_value);
		}
		else
		{
			LCD_integerToString(temp_read_value);
			LCD_displayCharacter(' ');
		}
	}



}
