/*
 ============================================================================
 Name        : Exercise1.c
 Author      : Mohamed Tarek
 Description : Test the keypad driver with 7-segment
 Date        : 1/23/2014
 ============================================================================
 */

/* You can enhance the exercise by:
 * 1. Implement a 7-segment driver.
 * 2. 7-segment driver will use the gpio driver to access the 7-segment bits.
 * 3. Include the 7-segment driver here instead of accessing the gpio registers.
 * 4. Send the keypad number that you wish to display to the 7-segment driver.
 */

#include "lcd.h"
#include "icu.h"
#include "avr/io.h"


uint8 g_ticks = 0;
uint16 g_timeHigh = 0;
uint16 g_timePeriod = 0;
uint16 g_timePeriodPulseHigh = 0;



void APP_edgeProcessing(void)
{
	g_ticks++;
	if(g_ticks == 1)
	{
		ICU_clearTimerValue();
		/* falling */
		ICU_setEdgeSelection(FALLING);
	}
	else if(g_ticks == 2)
	{
		g_timeHigh = ICU_getInputCaptureValue();
		ICU_setEdgeSelection(RISING);
	}
	else if(g_ticks == 3)
	{
		g_timePeriod = ICU_getInputCaptureValue();
		ICU_setEdgeSelection(FALLING);
	}
	else if(g_ticks == 4)
	{
		g_timePeriodPulseHigh = ICU_getInputCaptureValue();
	}
}



int main(void)
{
	ICU_Config s_configData = {RISING, F_CPU_CLOCK};
	SREG |= (1<<7);

	//uint32 dutyCycle = 0;
	uint32 period = 0;
	//uint32 freq = 0;
	ICU_setCallBack(APP_edgeProcessing);
	LCD_init();
	ICU_init(&s_configData);
	while(1)
	{
		if(g_ticks == 4)
		{
			ICU_deInit();
			g_ticks = 0;
			//LCD_displayString("Duty Cycle = ");
			LCD_displayString("Period = ");
			//LCD_displayString("Freq = ");
			//dutyCycle = ((float)(g_timePeriodPulseHigh - g_timePeriod)/(g_timePeriodPulseHigh - g_timeHigh)) * 100;
			period = g_timePeriodPulseHigh - g_timeHigh;
			//freq = 1000000/(g_timePeriodPulseHigh - g_timeHigh);
			//LCD_intgerToString(dutyCycle);
			LCD_intgerToString(period);
			//LCD_intgerToString(freq);
			//LCD_displayCharacter('%');
			LCD_displayString("us");
			//LCD_displayString("Hz");

		}
	}



}
