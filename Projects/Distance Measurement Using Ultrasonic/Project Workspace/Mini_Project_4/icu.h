/*
 ============================================================================
 Name        : icu.h
 Author      : Hussam Ali
 Description : ICU Driver header file
 ============================================================================
 */

#ifndef ICU_H_
#define ICU_H_

/******************************************* Used Libraries and Includes *****************************************/
#include "std_types.h"

/******************************************* User-Defined types **************************************************/
/* Enum to hold the values of the edge whether it is
 * Rising or Falling
 */
typedef enum{
	FALLING, RISING
}ICU_EdgeType;

/* Enum to hold the values of the used frequency */
typedef enum{
	NO_CLOCK, F_CPU_CLOCK, F_CPU_8, F_CPU_64, F_CPU_256, F_CPU_1024
}ICU_Clock;

/* Structure to hold the required edge type and clock which are given
 * during initialization of the ICU
 */
typedef struct{
	ICU_EdgeType edge;
	ICU_Clock clock;
}ICU_Config;


/********************************************** Functions Prototypes *******************************************/
/* Function to initialize the ICU with the given structure which
 * contains the required settings like the edge type and the clock
 */
void ICU_init(const ICU_Config *a_configPtr);

/* Function to clear the Timer value to start from 0 */
void ICU_clearTimerValue(void);

/* Function to select the Edge type that the ICU detects upon which
 * the interrupt happens
 */
void ICU_setEdgeSelection(const ICU_EdgeType edge);

/* Function to return the value of the register ICR1 which contains
 * the value of timer
 */
uint16 ICU_getInputCaptureValue(void);

/* Function to assign the address of the Callback function which is to be called
 * every time an interrupt occurs by the ICU to a global pointer to function variable
 */
void ICU_setCallBack(void(*a_ptr)(void));

/* Function to De-initialize the ICU driver */
void ICU_deInit(void);


#endif /* ICU_H_ */
