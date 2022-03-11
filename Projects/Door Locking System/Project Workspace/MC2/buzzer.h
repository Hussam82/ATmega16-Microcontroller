/*
 ============================================================================
 Name        : buzzer.h
 Author      : Hussam Ali
 Description : Buzzer Driver header file
 ============================================================================
 */


#ifndef BUZZER_H_
#define BUZZER_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/
#include "std_types.h"



/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define BUZZER_PORT_ID			PORTD_ID
#define BUZZER_PIN_ID			PIN4_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Function to initialize the Buzzer */
void Buzzer_init(void);
/* Function to turn on the Buzzer */
void Buzzer_on(void);
/* Function to turn off the Buzzer */
void Buzzer_off(void);

#endif /* BUZZER_H_ */
