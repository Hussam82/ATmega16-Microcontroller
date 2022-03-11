/*
 ============================================================================
 Name        : lm35sensor.c
 Author      : Hussam Ali
 Description : LM35 Sensor Driver source file
 ============================================================================
 */

/******************************************* Used Libraries *****************************************/
#include "lm35sensor.h"
#include "adc.h"
#include "util/delay.h"



/******************************************* Functions Definitions *****************************************/

/* Function to calculate the temperature value after taking the digital value
 * from the ADC
 */
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

