/*
 * keypad.h
 *
 *  Created on: Oct 4, 2021
 *      Author: pcc
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"

#define KEYPAD_NUM_COLS 		3
#define KEYPAD_NUM_ROWS			4
#define KEYPAD_PORT_ID			PORTB_ID
#define KEYPAD_FIRST_COL_PIN_ID		PIN4_ID
#define KEYPAD_FIRST_ROW_PIN_ID		PIN0_ID
#define KEYPAD_BUTTON_PRESSED		LOGIC_LOW
#define KEYPAD_BUTTON_RELEASED		LOGIC_HIGH


uint8 KEYPAD_getPressedKey(void);

#endif /* KEYPAD_H_ */
