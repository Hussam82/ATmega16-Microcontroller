/*
 ============================================================================
 Name        : ultrasonic.c
 Author      : Hussam Ali
 Description : Ultrasonic Sensor Driver header file
 ============================================================================
 */




/******************************************* Used Libraries and Includes *****************************************/
#include "ultrasonic.h"
#include "icu.h"
#include "gpio.h"
#include "util/delay.h"

/*********************************************** Global Variables ********************************************/
/* Used to hold the count of the edges */
static uint8 g_edgeCount = 0;
/* Used to store the value of the Timer1 value which indicates
 * the time of the pulse
 */
static uint16 g_timeHigh = 0;
/* Used to store the distance value which is calculated from
 * the pulse time
 */
static uint16 dist = 0;


/******************************************* Functions Definitions *****************************************/

void Ultrasonic_edgeProcessing(void)
{
	/* Increment the edge count every time an interrupt occurs */
	g_edgeCount++;
	if(g_edgeCount == 1)
	{
		/* Clear timer value to start from the first detected Rising Edge */
		ICU_clearTimerValue();
		/* Set the detection type to FALLING edge so that it gives interrupt
		 * on the next Falling edge
		 */
		ICU_setEdgeSelection(FALLING);
	}
	else if(g_edgeCount == 2)
	{
		/* Store the timer value in the global variable to be used later */
		g_timeHigh = ICU_getInputCaptureValue();
		/* Set the detection type to Rising edge so that it gives interrupt
		 * on the next Rising edge
		 */
		ICU_setEdgeSelection(RISING);
	}
}

void Ultrasonic_init(void)
{
	/* Configuration structure contains the required settings:
	 * Edge type: Rising edge
	 * Frequency: F_osc/8 (prescaler 8)
	 */
	ICU_Config s_configData = {RISING, F_CPU_8};
	/* Initialize the ICU with the given Configurations */
	ICU_init(&s_configData);
	/* Set the call back function to be called every interrupt */
	ICU_setCallBack(Ultrasonic_edgeProcessing);
	/* Setup the direction for the trigger pin as o/p */
	GPIO_setupPinDirection(TRIGGER_PORT, TRIGGER_PIN, PIN_OUTPUT);
}

void Ultrasonic_Trigger(void)
{
	/* Generate a 10 us pulse to make the ultrasonic generate
	 * 8 pulses of 40kHz
	 */
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIGGER_PORT, TRIGGER_PIN, LOGIC_LOW);
}

uint16 Ultrasonic_readDistance(void)
{
	/* Sent the 10 us trigger pulse	 */
	Ultrasonic_Trigger();
	/* After 2 edges, we consider that the pulse has ended
	 * so we need to reset the count and make the calculations
	 * needed to return the distance in centimeters
	 */
	if(g_edgeCount == 2)
	{
		/* Every time the edge count is 2 reset the edge count to zero
		 * to start over again
		 */
		g_edgeCount = 0;
		/* The calculations required to get the distance in cm
		 * considering that speed of sound is 340 m/sec and each
		 * count by the timer takes 1 us
		 *
		 */
		dist = (uint16)(g_timeHigh / 58) + 1;
	}
	return dist;
}
