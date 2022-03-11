/*
 ============================================================================
 Name        : adc.h
 Author      : Hussam Ali
 Description : ADC driver header file
 Date        : 08-Oct-21
 ============================================================================
 */

#ifndef ADC_H_
#define ADC_H_

/******************************************* Used Libraries *****************************************/
#include "std_types.h"

/******************************************* Static Configurations *****************************************/
#define ADC_MAXIMUM_VALUE			1023
#define ADC_REF_VOLT_VALUE			5

/******************************************* User-defined Types *****************************************/

/*
 * Enum to hold the values for the Prescaler
 */
typedef enum{
	F_CPU__2 = 1, F_CPU__4, F_CPU__8, F_CPU__16, F_CPU__32, F_CPU__64, F_CPU__128
}ADC_Prescaler;


/* Enum to hold the values of the reference voltage
 * REF_AREF = 00
 * REF_AVCC = 01
 * REF_INT = 11 (the internal reference voltage which is 2.56v)
 */
typedef enum{
	REF_AREF, REF_AVCC, REF_INT = 3
}ADC_ReferenceVoltage;

/*
 * Structure to hold the configurations we need as
 * The reference voltage
 * The prescaler
 */
typedef struct{
	ADC_ReferenceVoltage ref_volt;
	ADC_Prescaler prescaler;
}ADC_ConfigType;


/******************************************* Functions Prototypes *****************************************/

/*
 * Function to initialize the ADC by taking a pointer to the structure which contains
 * all the needed information to initialize it
 */
void ADC_init(const ADC_ConfigType *Config_Ptr);

/*
 * Function to read the sensor value at the given channel
 * and returns the digital value after converting the sensor
 * value to a digital value
 */
uint16 ADC_readChannel(uint8 ch_num);



#endif /* ADC_H_ */
