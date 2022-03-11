/*
 * icu.c
 *
 *  Created on: Oct 7, 2021
 *      Author: pcc
 */

#include "icu.h"
#include "avr/io.h"
#include <avr/interrupt.h>

volatile uint8 g_ticks = 0;
volatile uint16 g_timeHigh = 0;
volatile uint16 g_timePeriod = 0;
volatile uint16 g_timePeriodPulseHigh = 0;

/* measure duty cycle of pwm signal */
ISR(TIMER1_CAPT_vect)
{
	g_ticks++;
	if(g_ticks == 1)
	{
		TCNT1 = 0;
		/* falling */
		TCCR1B &= ~(1<<ICES1);
	}
	else if(g_ticks == 2)
	{
		g_timeHigh = ICR1;
		TCCR1B |= (1<<ICES1);
	}
	else if(g_ticks == 3)
	{
		g_timePeriod = ICR1;
		TCCR1B &= ~(1<<ICES1);
	}
	else if(g_ticks == 4)
	{
		g_timePeriodPulseHigh = ICR1;
	}

}





void ICU_init(void)
{
	/* non-pwm */
	TCCR1A = (1<<FOC1A) | (1<<FOC1B);
	/* Rising edge, No prescaler */
	TCCR1B = (1<<ICES1) | (1<<CS10);
	/* start counting from 0 */
	TCNT1 = 0;
	ICR1 = 0;
	/* Enable icu interrupt */
	TIMSK |= (1<<TICIE1);
}


void ICU_deInit(void)
{
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;
	TIMSK &= ~(1<<TICIE1);
}
