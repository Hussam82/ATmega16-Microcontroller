/*
 ============================================================================
 Name        : keypad.c
 Author      : Hussam Ali
 Description : Keypad Driver Source file
 ============================================================================
 */





/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "keypad.h"
#include "common_macros.h"
#include "gpio.h"


/*******************************************************************************
 *                      Static Function Prototypes                             *
 *******************************************************************************/

/* This function is static as it makes no sense for any other file
 * to use as it is used only in the getPressedKey function
 */
#if (KEYPAD_NUM_COLS == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number);
#elif (KEYPAD_NUM_COLS == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number);
#endif



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function to return the actual value of the pressed key after
 * being processed by the adjust function
 */
uint8 KEYPAD_getPressedKey(void)
{
	uint8 row, col;
	uint8 key_port_value = 0; /* Variable to hold the value of register to be written into */
	while(1)
	{
	for(col = 0; col < KEYPAD_NUM_COLS; col++)
	{
		/*
		 * Each time setup the direction for all keypad port as input pins,
		 * except this column will be output pin
		 */
		GPIO_setupPortDirection(KEYPAD_PORT_ID, PORT_INPUT);
		GPIO_setupPinDirection(KEYPAD_PORT_ID, KEYPAD_FIRST_COL_PIN_ID + col, PIN_OUTPUT);
#if(KEYPAD_BUTTON_PRESSED == LOGIC_LOW)
		key_port_value = ~(1<<(KEYPAD_FIRST_COL_PIN_ID + col));
#else
		key_port_value = (1<<(KEYPAD_FIRST_COL_PIN_ID + col));
#endif
		GPIO_writePort(KEYPAD_PORT_ID, key_port_value);
		for(row = 0; row < KEYPAD_NUM_ROWS; row++)
		{
			/* Check if the switch is pressed in this row */
			if(GPIO_readPin(KEYPAD_PORT_ID, KEYPAD_FIRST_ROW_PIN_ID + row) == KEYPAD_BUTTON_PRESSED)
			{
#if (KEYPAD_NUM_COLS == 3)
				return KEYPAD_4x3_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
#elif (KEYPAD_NUM_COLS == 4)
				return KEYPAD_4x4_adjustKeyNumber((row * KEYPAD_NUM_COLS) + col + 1);
#endif
			}
		}
	}
	}
}

/*
 * Function to take the value of the button number and make some
 * adjustments to return the actual value of the pressed key
 */
#if(KEYPAD_NUM_COLS == 3)
uint8 KEYPAD_4x3_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 10:
		keypad_button = '*';
		break;
	case 11:
		keypad_button = 0;
		break;
	case 12:
		keypad_button = '#';
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}
#else
uint8 KEYPAD_4x4_adjustKeyNumber(uint8 button_number)
{
	uint8 keypad_button = 0;
	switch(button_number)
	{
	case 1:
		keypad_button = 7;
		break;
	case 2:
		keypad_button = 8;
		break;
	case 3:
		keypad_button = 9;
		break;
	case 4:
		keypad_button = '%';
		break;
	case 5:
		keypad_button = 4;
		break;
	case 6:
		keypad_button = 5;
		break;
	case 7:
		keypad_button = 6;
		break;
	case 8:
		keypad_button = '*';
		break;
	case 9:
		keypad_button = 1;
		break;
	case 10:
		keypad_button = 2;
		break;
	case 11:
		keypad_button = 3;
		break;
	case 12:
		keypad_button = '-';
		break;
	case 13:
		keypad_button = 13;
		break;
	case 14:
		keypad_button = 0;
		break;
	case 15:
		keypad_button = '=';
		break;
	case 16:
		keypad_button = '+';
		break;
	default:
		keypad_button = button_number;
		break;
	}
	return keypad_button;
}
#endif











