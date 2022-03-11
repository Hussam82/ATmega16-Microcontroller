/*
 ============================================================================
 Name        : pwm.h
 Author      : Hussam Ali
 Description : PWM driver header file
 ============================================================================
 */

#ifndef PWM_H_
#define PWM_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to generate a PWM signal with a given duty cycle by using
 * Timer0 in PWM mode
 */
void PWM_Timer0_Start(uint8 duty_cycle);

#endif /* PWM_H_ */
