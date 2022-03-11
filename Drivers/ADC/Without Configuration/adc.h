/*
 * adc.h
 *
 *  Created on: Oct 6, 2021
 *      Author: pcc
 */

#ifndef ADC_H_
#define ADC_H_

#include "std_types.h"

#define ADC_POLLING_TECHNIQUE
#define ADC_MAXIMUM_VALUE			1023
#define ADC_REF_VOLT_VALUE			5


#ifdef ADC_INTERRUPT_TECHNIQUE
extern volatile uint16 g_adcValue;
void ADC_readChannel(uint8 ch_num);
#else
void ADC_init(void);
uint16 ADC_readChannel(uint8 ch_num);
#endif


#endif /* ADC_H_ */
