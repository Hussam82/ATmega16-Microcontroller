/*
 ============================================================================
 Name        : pwm.c
 Author      : Hussam Ali
 Description : PWM driver source file
 ============================================================================
 */


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "pwm.h"
#include "common_macros.h"
#include "avr/io.h"
#include "gpio.h"


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Function to generate a PWM signal on OC0/PB3 pin
 * with a given duty cycle by using
 * Timer0 in Fast PWM mode
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	/* Timer 0 configurations:
	 * Fast PWM mode
	 * Non-inverting (OC0 is connected)
	 * Prescaler 8 (gives a PWM signal of frequency 500Hz on OC0 pin knowing that the MC runs at frequency 1MHz)
	 */
	TCCR0 |= (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01);
	/* Start counting from 0 */
	TCNT0 = 0;
	/* Put in OCR0 Register the duty cycle required */
	OCR0 = ((float)duty_cycle/100) * 255;
	/* Set the OC0/PB3 pin in Microcontroller to be o/p */
	GPIO_setupPinDirection(PORTB_ID, PIN3_ID, PIN_OUTPUT);
}

