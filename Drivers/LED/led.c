/*
 ============================================================================
 Name        : led.h
 Author      : Hussam Ali
 Description : LED Driver source file
 ============================================================================
 */

/******************************************* Used Libraries *****************************************/


#include "led.h"
#include "gpio.h"



/******************************************* Functions Definitions *****************************************/



void LED_init()
{
	/* The pin connected to the LED must be o/p */
	GPIO_setupPinDirection(LED_PORT, LED_PIN, PIN_OUTPUT);
	/* Turn off the LED initially */
	GPIO_writePin(LED_PORT, LED_PIN, LED_OFF);
}

void LED_on()
{

	/* Write 1 to the pin connected to the LED */
	GPIO_writePin(LED_PORT, LED_PIN, LED_ON);
}


void LED_off()
{
	/* Write 0 to the pin connected to the LED */
	GPIO_writePin(LED_PORT, LED_PIN, LED_OFF);
}


