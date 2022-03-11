/*
 ============================================================================
 Name        : sevenseg.c
 Author      : Hussam Ali
 Description : Seven Segment Driver source file
 ============================================================================
 */




/******************************************* Used Libraries *****************************************/
#include "sevenseg.h"
#include "gpio.h"



/******************************************* Functions Definitions *****************************************/
void SEVENSEG_init(void)
{
	GPIO_setupPinDirection(SEG_PORT, SEG_PIN1, PIN_OUTPUT);
	GPIO_setupPinDirection(SEG_PORT, SEG_PIN2, PIN_OUTPUT);
	GPIO_setupPinDirection(SEG_PORT, SEG_PIN3, PIN_OUTPUT);
	GPIO_setupPinDirection(SEG_PORT, SEG_PIN4, PIN_OUTPUT);
	GPIO_writePort(SEG_PORT, (0x0F)<<SEG_PIN1);
}

void SEVENSEG_displayDigit(uint8 num)
{
	GPIO_writePort(SEG_PORT, ((num & 0x0F)<<SEG_PIN1));
}
