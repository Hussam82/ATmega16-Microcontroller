/*
 * adc.c
 *
 *  Created on: Oct 6, 2021
 *      Author: pcc
 */


#include "adc.h"
#include "common_macros.h"
#include "avr/io.h"
#include <avr/interrupt.h>

#ifdef ADC_INTERRUPT_TECHNIQUE
volatile uint16 g_adcValue = 0;
#endif

#ifdef ADC_INTERRUPT_TECHNIQUE
ISR(ADC_vect)
{
	g_adcValue = ADC;
}
#endif


#ifdef ADC_INTERRUPT_TECHNIQUE
void ADC_init(void)
{
	/* Vref = AREF, channel ADC0 */
	ADMUX = 0;
	/* Enable ADC, enable interrupts , prescaler 8*/
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0) | (1<<ADIE);
}

void ADC_readChannel(uint8 ch_num)
{
	/* insert channel number which is a 3 bit number in the first 5 bits of ADMUX REGISTER*/
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x07);
	/* start conversion */
	SET_BIT(ADCSRA, ADSC);
}
#else
void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0);
}
uint16 ADC_readChannel(uint8 ch_num)
{
	/* insert channel number which is a 3 bit number in the first 5 bits of ADMUX REGISTER*/
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x07);
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}
#endif



