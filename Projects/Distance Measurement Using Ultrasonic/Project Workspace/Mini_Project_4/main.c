/*
 ============================================================================
 Name        : main.c
 Author      : Hussam Ali
 Description : Display the reading of ultrasonic sensor on LCD
 ============================================================================
 */




/******************************************* Used Libraries and Includes *****************************************/
#include "lcd.h"
#include "ultrasonic.h"
#include "util/delay.h"
#include <avr/io.h>


/******************************************* Main Function *****************************************/
int main(void)
{
	/* A variable to hold the distance */
	uint16 distance = 0;
	/* Enable the Global Interrupts I-bit */
	SREG |= (1<<7);
	/* Initialize the LCD */
	LCD_init();
	/* Initialize the Ultrasonic sensor */
	Ultrasonic_init();
	LCD_displayString("Distance = ");
	while(1)
	{
		distance = Ultrasonic_readDistance();
		/* Always write the distance over the old distance so that
		 * it will not increment the cursor and display in wrong
		 * places
		 */
		LCD_moveCursor(0, 11);
		/* This if else condition to remove the extra digit that is displayed
		 * when the number decreases from 3 digits to 2 digits
		 */
		if(distance >= 100)
		{
			LCD_integerToString(distance);

		}
		else
		{
			LCD_integerToString(distance);
			LCD_displayCharacter(' ');
		}
		LCD_displayString("cm");
		LCD_displayCharacter(' ');
	}
}
