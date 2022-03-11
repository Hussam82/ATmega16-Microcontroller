/*
 ============================================================================
 Name        : timer.c
 Author      : Hussam Ali
 Description : Timer0 Driver Source file
 ============================================================================
 */


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "timer.h"
#include "avr/io.h"
#include "avr/interrupt.h"


/*******************************************************************************
 *                         Global Variables                                    *
 *******************************************************************************/

/* Pointer to function to hold the callback function address
 * of each Timer
 */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function to initialize the Timer with the given configurations
 * in a Configuration Structure
 */
void Timer_init(const Timer_Config* s_ConfigData)
{
	if(s_ConfigData->timer_id == TIMER0_ID)
	{
		/* Set FOC0 when working in non-PWM mode
		 * Clear WGM00 as it is always zero in Normal and CTC modes
		 * Clear COM01:00 assuming that OC0 is always disconnected
		 */
		TCCR0 = (1<<FOC0);
		/* Insert the Prescaler in the first 3 bits of TCCR0 register */
		TCCR0 = (TCCR0 & 0xF8) | (s_ConfigData->timer_prescaler);
		/* Insert the timer mode in WGM01 bit in TCCR0 register */
		TCCR0 = (TCCR0 & 0xF7) | ((s_ConfigData->timer_mode)<<3);
		/* Insert the given initial value in TCNT0 register */
		TCNT0 = s_ConfigData->initial_value;
		/* Insert the given compare value in OCR0 register */
		OCR0 = s_ConfigData->compare_value;
		/* Enable interrupt of the given mode
		 * NORMAL_MODE
		 * COMPARE_MODE
		 */
		if(s_ConfigData->timer_mode == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE0);
		}
		else if(s_ConfigData->timer_mode == COMPARE_MODE)
		{
			TIMSK |= (1<<OCIE0);
		}
	}
	else if(s_ConfigData->timer_id == TIMER1_ID)
	{
		/* Set FOC1A when working in non-PWM mode
		 * Clear WGM11:10 as they are always zero in Normal and CTC modes
		 * Clear COM1A1:1A0:1B1:1B0 assuming that OC1A and OC1B are always disconnected
		 */
		TCCR1A = (1<<FOC1A);
		/* Clear TCCR1B to disable ICU interrupts */
		TCCR1B = 0;
		/* Insert the timer mode in WGM12 bit in TCCR1B register */
		TCCR1B = (TCCR1B & 0xF7) | ((s_ConfigData->timer_mode)<<3);
		/* Insert the Prescaler in the first 3 bits of TCCR1B register */
		TCCR1B = (TCCR1B & 0xF8) | (s_ConfigData->timer_prescaler);
		/* Insert the given initial value in TCNT1 register */
		TCNT1 = s_ConfigData->initial_value;
		/* Insert the given compare value in OCR1A register */
		OCR1A = s_ConfigData->compare_value;
		/* Enable interrupt of the given mode
		 * NORMAL_MODE
		 * COMPARE_MODE
		 */
		if(s_ConfigData->timer_mode == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE1);
		}
		else if(s_ConfigData->timer_mode == COMPARE_MODE)
		{
			TIMSK |= (1<<OCIE1A);
		}
	}
	else if(s_ConfigData->timer_id == TIMER2_ID)
	{
		/* Set FOC2 when working in non-PWM mode
		 * Clear WGM20 as it is always zero in Normal and CTC modes
		 * Clear COM21:20 assuming that OC2 is always disconnected
		 */
		TCCR2 = (1<<FOC2);
		/* Insert the prescaler in the first 3 bits of TCCR2 register */
		TCCR2 = (TCCR2 & 0xF8) | (s_ConfigData->timer_prescaler);
		/* Insert the timer mode in WGM21 bit in TCCR2 register */
		TCCR2 = (TCCR2 & 0xF7) | ((s_ConfigData->timer_mode)<<3);
		/* Insert the given initial value in TCNT2 register */
		TCNT2 = s_ConfigData->initial_value;
		/* Insert the given compare value in OCR2 register */
		OCR2 = s_ConfigData->compare_value;
		/* Enable interrupt of the given mode
		 * NORMAL_MODE
		 * COMPARE_MODE
		 */
		if(s_ConfigData->timer_mode == NORMAL_MODE)
		{
			TIMSK |= (1<<TOIE2);
		}
		else if(s_ConfigData->timer_mode == COMPARE_MODE)
		{
			TIMSK |= (1<<OCIE2);
		}
	}
}

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer0, the callback function is executed
 */
void Timer_setCallBack0(void (*a_ptr)(void))
{
	g_callBackPtr0 = a_ptr;
}

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer1, the callback function is executed
 */
void Timer_setCallBack1(void (*a_ptr)(void))
{
	g_callBackPtr1 = a_ptr;
}

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer2, the callback function is executed
 */
void Timer_setCallBack2(void (*a_ptr)(void))
{
	g_callBackPtr2 = a_ptr;
}

/* Function to de-initialize the required timer */
void Timer_deInit(uint8 timer_id)
{
	if(timer_id == TIMER0_ID)
	{
		TCCR0 = 0;
		TCNT0 = 0;
	}
	else if(timer_id == TIMER1_ID)
	{
		TCCR1A = 0;
		TCCR1B = 0;
		TCNT1 = 0;
	}
	else if(timer_id == TIMER2_ID)
	{
		TCCR2 = 0;
		TCNT2 = 0;
	}
}

/*******************************************************************************
 *                      Interrupt Service Routines (ISRs)                      *
 *******************************************************************************/

/* ISR of Timer0 in overflow mode, which is executed every time
 * an overflow occurs
 */
ISR(TIMER0_OVF_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr0)();
	}
}

/* ISR of Timer0 in compare mode, which is executed every time
 * compare match occurs
 */
ISR(TIMER0_COMP_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr0)();
	}
}

/* ISR of Timer1 in overflow mode, which is executed every time
 * an overflow occurs
 */
ISR(TIMER1_OVF_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr1)();
	}
}

/* ISR of Timer1 in compare mode, which is executed every time
 * compare match occurs
 */
ISR(TIMER1_COMPA_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr1)();
	}
}

/* ISR of Timer2 in overflow mode, which is executed every time
 * an overflow occurs
 */
ISR(TIMER2_OVF_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr2)();
	}
}

/* ISR of Timer2 in compare mode, which is executed every time
 * compare match occurs
 */
ISR(TIMER2_COMP_vect)
{
	/* Don't call the callback function unless the pointer has a value other than null */
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* call the callback function */
		(*g_callBackPtr2)();
	}
}
