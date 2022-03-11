/*
 * icu.h
 *
 *  Created on: Oct 7, 2021
 *      Author: pcc
 */

#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

extern volatile uint8 g_ticks;
extern volatile uint16 g_timeHigh;
extern volatile uint16 g_timePeriod;
extern volatile uint16 g_timePeriodPulseHigh;

void ICU_init(void);

void ICU_deInit(void);


#endif /* ICU_H_ */
