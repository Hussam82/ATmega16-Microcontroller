/*
 ============================================================================
 Name        : timer.h
 Author      : Hussam Ali
 Description : Timer0 Driver header file
 ============================================================================
 */

#ifndef TIMER_H_
#define TIMER_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"


/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* enum to hold the Timer Mode */
typedef enum{
	TIMER0_ID, TIMER1_ID, TIMER2_ID
}Timer_ID;

/* enum to hold the Timer Mode */
typedef enum{
	NORMAL_MODE, COMPARE_MODE
}Timer_Mode;

/* enum to hold the prescaler Values */
typedef enum{
	NO_CLOCK, TIMER0_1 = 1, TIMER0_8 = 2, TIMER0_64 = 3, TIMER0_256 = 4, TIMER0_1024 = 5,\
	TIMER1_1 = 1, TIMER1_8 = 2,  TIMER1_64 = 3, TIMER1_256 = 4, TIMER1_1024 = 5,\
	TIMER2_1 = 1, TIMER2_8 = 2, TIMER2_32 = 3, TIMER_2_64 = 4, TIMER_2_128 = 5, TIMER_2_256 = 6, TIMER_2_1024 = 7
}Timer_Prescaler;

/* Configuration Structure to configure the timer:
 * Timer ID
 * Initial Value
 * Compare Value
 * Timer Mode
 * Prescaler
 */
typedef struct{
	Timer_ID timer_id;
	uint32 initial_value;
	uint32 compare_value;
	Timer_Mode timer_mode;
	Timer_Prescaler timer_prescaler;
}Timer_Config;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function to initialize the Timer with the given configurations
 * in a Configuration Structure
 */
void Timer_init(const Timer_Config* s_ConfigData);

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer0, the callback function is executed
 */
void Timer_setCallBack0(void (*a_ptr)(void));

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer1, the callback function is executed
 */
void Timer_setCallBack1(void (*a_ptr)(void));

/* Assign the address of the given callback function to the global variable
 * so that every time an interrupt occurs by Timer2, the callback function is executed
 */
void Timer_setCallBack2(void (*a_ptr)(void));

/* Function to de-initialize the required timer */
void Timer_deInit(Timer_ID timer_id);

#endif /* TIMER_H_ */
