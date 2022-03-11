/*
 ============================================================================
 Name        : buzzer.h
 Author      : Hussam Ali
 Description : Buzzer Driver header file
 ============================================================================
 */





/****************************************** Used Libraries & Includes *****************************************/
#include "buzzer.h"
#include "gpio.h"



/******************************************* Functions Definitions *****************************************/
void Buzzer_init(void)
{
	/* Setup the Pin as o/p pin */
	GPIO_setupPinDirection(BUZZER_PORT_ID, BUZZER_PIN_ID, PIN_OUTPUT);
}

void Buzzer_on(void)
{
	/* Write one to buzzer pin */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_HIGH);
}

void Buzzer_off(void)
{
	/* Write zero to the buzzer pin */
	GPIO_writePin(BUZZER_PORT_ID, BUZZER_PIN_ID, LOGIC_LOW);
}
