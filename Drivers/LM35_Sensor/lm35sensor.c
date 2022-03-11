/*
 * lm35sensor.c
 *
 *  Created on: Oct 6, 2021
 *      Author: pcc
 */


#include "lm35sensor.h"
#include "adc.h"
#include "util/delay.h"


#ifdef ADC_INTERRUPT_TECHNIQUE
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;
	ADC_readChannel(SENSOR_CHANNEL_ID);
	_delay_ms(5);
	temp_value = (uint8)(((uint32)g_adcValue * SENSOR_MAX_TEMPERATURE * ADC_REF_VOLT_VALUE)/(SENSOR_MAX_VOLT_VALUE * ADC_MAXIMUM_VALUE));
	return temp_value;

}
#endif
uint8 LM35_getTemperature(void)
{
	uint8 temp_value = 0;

	uint16 adc_value = 0;

	/* Read ADC channel where the temperature sensor is connected */
	adc_value = ADC_readChannel(SENSOR_CHANNEL_ID);

	/* Calculate the temperature from the ADC value*/
	temp_value = (uint8)(((uint32)adc_value*SENSOR_MAX_TEMPERATURE*ADC_REF_VOLT_VALUE)/(ADC_MAXIMUM_VALUE*SENSOR_MAX_VOLT_VALUE));

	return temp_value;
}

