/*
 ============================================================================
 Name        : led.h
 Author      : Hussam Ali
 Description : LED Driver header file
 ============================================================================
 */

#ifndef LED_H_
#define LED_H_


/******************************************* Used Libraries *****************************************/

#include "std_types.h"

/******************************************* Static Configurations *****************************************/

#define LED_PORT		PORTC_ID
#define LED_PIN			PIN3_ID
/* To control whether the LED is connected in
 * Positive logic configuration or
 * Negative logic configuration
 */
#define LED_ON			LOGIC_HIGH
#define LED_OFF			LOGIC_LOW



/******************************************* Functions Prototypes *****************************************/

/*
 * Function to Initialize the LED
 */
void LED_init();
/*
 * Function to turn on the LED
 */
void LED_on();
/*
 * Function to turn off the LED
 */
void LED_off();

#endif /* LED_H_ */
