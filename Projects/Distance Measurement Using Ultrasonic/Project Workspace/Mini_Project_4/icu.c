/*
 ============================================================================
 Name        : icu.c
 Author      : Hussam Ali
 Description : ICU Driver Source file
 ============================================================================
 */




/******************************************* Used Libraries and Includes *****************************************/
#include "icu.h"
#include "avr/io.h"
#include <avr/interrupt.h>


/*********************************************** Global Variables ********************************************/
/* Pointer to function to hold the callback function address */
static volatile void (*g_callBackPtr)(void) = NULL_PTR;


/*********************************************** Interrupt Service Routines ********************************************/
ISR(TIMER1_CAPT_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr)();
	}

}

/******************************************* Functions Definitions *****************************************/
void ICU_init(const ICU_Config *a_configPtr)
{
	/* Set ICP1/PD6 pin as i/p */
	DDRD &= ~(1<<PD6);
	/* Non-pwm mode
	 * OC1A and OC1B disconnected
	 * Overflow mode
	 */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/* Insert the required clock in the first three bits of the
	 * TCCR1B register
	 */
	TCCR1B = (TCCR1B & 0xF8) | (a_configPtr->clock);
	/* Insert the required edge type in the 6th bit of the
	 * TCCR1B register
	 */
	TCCR1B = (TCCR1B & 0xBF) | ((a_configPtr->edge)<<6);
	/* Start counting from 0 */
	TCNT1 = 0;
	ICR1 = 0;
	/* Enable ICU Interrupt */
	TIMSK |= (1<<TICIE1);
}

void ICU_deInit(void)
{
	/* Turn off the timer and hence the ICU driver */
	TCCR1A = 0;
	TCCR1B = 0;
	/* Reset the timer value */
	TCNT1 = 0;
	ICR1 = 0;
	/* Disable ICU Interrupt */
	TIMSK &= ~(1<<TICIE1);
}

void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

void ICU_setEdgeSelection(const ICU_EdgeType a_edgeType)
{
	/* Insert the required edge type */
	TCCR1B = (TCCR1B & 0xBF) | ((a_edgeType)<<6);
}

uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}

void ICU_setCallBack(void (*a_ptr)(void))
{
	g_callBackPtr = a_ptr;
}
