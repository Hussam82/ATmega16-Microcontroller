/*
 ============================================================================
 Name        : button.h
 Author      : Hussam Ali
 Description : Push Button Driver header file
 ============================================================================
 */

#ifndef BUTTON_H_
#define BUTTON_H_


/******************************************* Used Libraries *****************************************/

#include "std_types.h"


#define BUTTON_PRESSED				LOGIC_HIGH
#define BUTTON_RELEASED				LOGIC_LOW
/* To enable or disable Internal pull up configuration */
#define BUTTON_INTERNAL_PULL_UP		LOGIC_LOW

/******************************************* Functions Prototypes *****************************************/
/*
 * Function to read the status of the button connected to port_id
 * and pin_id whether it is pressed or released
 */
uint8 BUTTON_readStatus(uint8 port_id, uint8 pin_id);



#endif /* BUTTON_H_ */
