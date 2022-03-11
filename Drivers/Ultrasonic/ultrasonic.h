/*
 ============================================================================
 Name        : ultrasonic.h
 Author      : Hussam Ali
 Description : Ultrasonic Sensor Driver header file
 ============================================================================
 */

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_



/******************************************* Used Libraries and Includes *****************************************/
#include "std_types.h"

/******************************************* Static Configurations *****************************************/
/* The port to which the trigger pin is connected */
#define TRIGGER_PORT		PORTB_ID
/* The pin to which the trigger pin is connected */
#define TRIGGER_PIN			PIN5_ID


/******************************************* Functions Prototypes *****************************************/
/*
 * Function to initialize the ultrasonic module
 * which initializes the ICU module with the required
 * configurations
 */
void Ultrasonic_init(void);

/*
 * Function to generate 10 us pulse to make the ultrasonic module
 * generate 8 pulses of 40kHz frequency
 */
void Ultrasonic_Trigger(void);


/*
 * Function to measure the distance by using the high time
 * of the echo signal and making some calculations and returns
 * the distance in centimeters
 */
uint16 Ultrasonic_readDistance(void);

/*
 * This is the CallBack function which is to be called
 * every time an interrupt triggered by the ICU
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
