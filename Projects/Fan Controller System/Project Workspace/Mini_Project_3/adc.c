/*
 ============================================================================
 Name        : adc.c
 Author      : Hussam Ali
 Description : ADC driver source file
 ============================================================================
 */


/******************************************* Used Libraries *****************************************/
#include "adc.h"
#include "common_macros.h"
#include "avr/io.h"
#include <avr/interrupt.h>





/******************************************* Functions Definitions *****************************************/

/*
 * Function to initialize the ADC by taking a pointer to the structure which contains
 * all the needed information to initialize it
 */
void ADC_init(const ADC_ConfigType *Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0;
	/* Insert the reference voltage in the bits no.6 and no.7 of ADCSRA register */
	ADMUX |= (Config_Ptr->ref_volt)<<6;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<ADEN);
	/* Insert the prescaler in the first three bits of ADCSRA register */
	ADCSRA |= (Config_Ptr->prescaler);
}

/*
 * Function to read the sensor value at the given channel
 * and returns the digital value after converting the sensor
 * value to a digital value
 */
uint16 ADC_readChannel(uint8 ch_num)
{
	/* insert channel number which is a 3 bit number in the first 5 bits of ADMUX REGISTER*/
	ADMUX = (ADMUX & 0xE0) | (ch_num & 0x07);
	/* Start conversion write '1' to ADSC */
	SET_BIT(ADCSRA,ADSC);
	/* Wait for conversion to complete, ADIF becomes '1' */
	while(BIT_IS_CLEAR(ADCSRA,ADIF));
	/* Clear ADIF by write '1' to it :) */
	SET_BIT(ADCSRA,ADIF);
	/* Read the digital value from the data register and return it */
	return ADC;
}




