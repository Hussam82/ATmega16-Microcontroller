/*
 ============================================================================
 Name        : keypad.h
 Author      : Hussam Ali
 Description : Keypad Driver Header file
 ============================================================================
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/
#include "std_types.h"




/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define KEYPAD_NUM_COLS 		4
#define KEYPAD_NUM_ROWS			4
#define KEYPAD_PORT_ID			PORTC_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID
#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID
#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED		LOGIC_HIGH

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to return the actual value of the pressed key after
 * being processed by the adjust function
 */
uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
