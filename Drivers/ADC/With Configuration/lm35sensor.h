/*
 ============================================================================
 Name        : adc.c
 Author      : Hussam Ali
 Description : LM35 Sensor Driver header file
 Date        : 08-Oct-21
 ============================================================================
 */

#ifndef LM35SENSOR_H_
#define LM35SENSOR_H_



/******************************************* Used Libraries *****************************************/

#include "std_types.h"


/******************************************* Static Configurations *****************************************/

#define SENSOR_CHANNEL_ID				2
#define SENSOR_MAX_TEMPERATURE			150
#define SENSOR_MAX_VOLT_VALUE			1.5




/******************************************* Functions Prototypes *****************************************/

/* Function to calculate the temperature value after taking the digital value
 * from the ADC
 */
uint8 LM35_getTemperature(void);

#endif /* LM35SENSOR_H_ */
