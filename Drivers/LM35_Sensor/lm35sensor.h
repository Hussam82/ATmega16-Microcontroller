/*
 * lm35sensor.h
 *
 *  Created on: Oct 6, 2021
 *      Author: pcc
 */

#ifndef LM35SENSOR_H_
#define LM35SENSOR_H_

#include "std_types.h"

#define SENSOR_CHANNEL_ID				2
#define SENSOR_MAX_TEMPERATURE			150
#define SENSOR_MAX_VOLT_VALUE			1.5

uint8 LM35_getTemperature(void);

#endif /* LM35SENSOR_H_ */
