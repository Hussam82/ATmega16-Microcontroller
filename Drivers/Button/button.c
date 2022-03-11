/*
 ============================================================================
 Name        : button.c
 Author      : Hussam Ali
 Description : Push Button Driver source file
 ============================================================================
 */


/******************************************* Used Libraries *****************************************/

#include "button.h"
#include "gpio.h"



/******************************************* Functions Definitions *****************************************/

uint8 BUTTON_readStatus(uint8 port_id, uint8 pin_id)
{
	/* Variable to hold the state of the button */
	uint8 button_state;
	/* The pin connected to the button must be i/p */
	GPIO_setupPinDirection(port_id, pin_id, PIN_INPUT);
	/* To enable the internal pull up configuration
	 * write 1 to the pin while it is in i/p mode
	 */
#if(BUTTON_INTERNAL_PULL_UP)
	GPIO_writePin(port_id, pin_id, LOGIC_HIGH);
#endif
	/* Check whether the button is pressed or not */
	if(GPIO_readPin(port_id, pin_id))
	{
		button_state = BUTTON_PRESSED;
	}
	else
	{
		button_state = BUTTON_RELEASED;
	}
	return button_state;
}
