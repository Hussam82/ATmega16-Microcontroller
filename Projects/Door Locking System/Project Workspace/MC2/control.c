 /*
 ============================================================================
 Name        : control.c
 Author      : Hussam Ali
 Description : Control ECU source file
 ============================================================================
 */



/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

/* I2C Driver */
#include "twi.h"
/* UART Driver */
#include "uart.h"
/* External EEPROM Driver */
#include "external_eeprom.h"
/* Timer Driver */
#include "timer.h"
/* Motor Driver */
#include "motor.h"
/* Buzzer Driver */
#include "buzzer.h"
/* Delay library */
#include "util/delay.h"
/* AVR library to be able to access the registers */
#include "avr/io.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define HMI_READY 0x30
#define CONTROL_READY 0x31


/*******************************************************************************
 *                             Global Variables                                *
 *******************************************************************************/
/* To store the ticks for the Motor timing */
static uint8 g_ticks = 0;
/* To store the ticks for the Buzzer timing */
static uint8 g_ticks1 = 0;
/* Flag to determine whether the processor
 * should continue in the while(1) or not
 */
static uint8 term_flag = 0;
/* To determine how many times the Pin is wrong */
static uint8 count = 0;
/* Timer configuration Structure */
Timer_Config s_TimerConfigData = {TIMER1_ID, 0, 8000, COMPARE_MODE, TIMER1_1024};



/*******************************************************************************
 *                                Function Definitions                         *
 *******************************************************************************/

/* The call back function which controls the Rotation of the Motor as follows
 * Considering that each tick is one second:
 * Rotate the motor for 15 seconds in Clockwise direction
 * Stop the motor for 3 seconds
 * Rotate the motor for 15 seconds in Anti-clockwise direction
 */
void APP_rotateMotor(void)
{
	g_ticks++;
	if(g_ticks == 1)
	{
		DcMotor_rotateCW();
	}
	else if(g_ticks == 15)
	{
		DcMotor_stop();
	}
	else if(g_ticks == 18)
	{
		DcMotor_rotateACW();
	}
	else if(g_ticks == 33)
	{
		/* Reset the ticks when done */
		g_ticks = 0;
		/* Clear the flag when done */
		term_flag = 0;
		DcMotor_stop();
		/* De-initialize the timer when done */
		Timer_deInit(TIMER1_ID);
	}
}

/* Function to control the Buzzer timing as follows
 * The buzzer is turned on for one minute then it
 * is turned off to indicate that the pin has been
 * entered 3 times wrong
 */
void APP_buzzerTrigger(void)
{
	g_ticks1++;
	if(g_ticks1 == 1)
	{
		Buzzer_on();
	}
	else if(g_ticks1 == 60)
	{
		/* Reset the ticks when done */
		g_ticks1 = 0;
		/* Clear the flag when done */
		term_flag = 0;
		Buzzer_off();
		/* De-initialize the timer when done */
		Timer_deInit(TIMER1_ID);
	}
}

/* Function to store the pin the external EEPROM after
 * taking it from MC1
 */
void APP_storePin(void)
{
	uint8 i;
	/* Array to hold the Pin */
	uint8 pin[5];
	/* Receive the 5-digit PIN */
	UART_sendByte(CONTROL_READY);
	for(i = 0; i < 5; i++)
	{
		pin[i] = UART_receiveByte();
	}

	/* Store the PIN in the EEPROM */
	for(i = 0; i < 5; i++)
	{
		EEPROM_writeByte(i, pin[i]);
		_delay_ms(10);
	}
}

/* Function to verify that the pin is correct to proceed
 * If the user attempted to enter the wrong pin 3 times in
 * a row, it will trigger the buzzer
 */
void APP_verifyPin(uint8* flag)
{
	/* Array to hold the pin from the EEPROM */
	uint8 stored_pin[5];
	/* Array to hold the pin received from MC1 to check
	 * its validity with the stored pin
	 */
	uint8 check_pin[5];
	uint8 i;
	/* Stores the pin in an empty array */
	for(i = 0; i < 5; i++)
	{
		EEPROM_readByte(i, &stored_pin[i]);
		_delay_ms(10);
	}
	/* Receive the pin from MC1 if it is true proceed to
	 * rotating the motor if not, it will attempt to get
	 * the pin for 2 more times. If the pin is still wrong
	 * Buzzer goes off
	 */
	do{
		count++;
		if(count == 4)
		{
			/* Take the flag when executing the buzzer app */
			term_flag = 1;
			Timer_init(&s_TimerConfigData);
			Timer_setCallBack1(APP_buzzerTrigger);
			break;
		}
		for(i = 0; i < 5; i++)
		{
			check_pin[i] = UART_receiveByte();
		}
		/* Check for the received pin from MC1 with the one stored
		 * in the EEPROM
		 */
		for(i = 0; i < 5; i++)
		{
			if(check_pin[i] != stored_pin[i])
			{
				/* Indicate the pin is wrong */
				*flag = 1;
				break;
			}
			else
			{
				*flag = 0;
			}
		}
		/* Send the value of the flag to tell MC1 that the PIN is correct
		 * or not to take action depending on that
		 */
		UART_sendByte(*flag);
	/* Stay in the do while loop for 3 times only */
	}while(*flag == 1);
}


/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/
int main(void)
{
	/* Enable the I-bit to enable Interrupts */
	SREG |= (1<<7);
	/* To indicate which operation to be performed */
	uint8 option;
	/* Flag to indicate whether the pin is entered correctly
	 * or not
	 */
	uint8 flag;
	/* UART configuration Structure
	 * ONE STOP BIT
	 * EIGHT BIT MODE
	 * NO PARITY
	 * BAUD RATE 9600
	 */
	UART_Config s_UARTConfigData = {ONE_BIT_STOP, EIGHT_BIT_MODE, PARITY_OFF, 9600};
	/* I2C configuration Structure
	 * MC2 address = 0x50
	 * Bit rate 400k kbits/sec
	 */
	TWI_Config s_TWIConfigData = {0x50, BR_400};
	/* Initialize the UART driver with the given structure */
	UART_init(&s_UARTConfigData);
	/* Initialize the I2C driver with the given structure */
	TWI_init(&s_TWIConfigData);
	/* Initialize the Motor driver */
	DcMotor_init();
	/* Initialize the Buzzer driver */
	Buzzer_init();
	/* Store the pin in EEPROM after receiving it from MC1 */
	APP_storePin();
	while(1)
	{
		/* Get the required option from MC1 */
		option = UART_receiveByte();
		/* '+' indicates that user wants to Rotate the door */
		if(option == '+')
		{
			/* Attempt to take the pin from the user and verify it */
			APP_verifyPin(&flag);
			/* if flag = 0, this means that the entered pin is correct */
			if(flag == 0)
			{
				count = 0;
				/* Take the flag to rotate the door without interruption */
				term_flag = 1;
				Timer_init(&s_TimerConfigData);
				Timer_setCallBack1(APP_rotateMotor);
			}
		}
		/* '-' indicates that the user wants to change the pin */
		else if(option == '-')
		{
			/* Attempt to take the pin from the user and verify it */
			APP_verifyPin(&flag);
			/* flag = 0 means that the user entered the pin correctly */
			if(flag == 0)
			{
				count = 0;
				/* Store the pin after it has been entered correctly */
				APP_storePin();
			}
		}
		/* Do nothing when the door is opening or closing and when the Buzzer goes off */
		while(term_flag == 1) {}
	}
}
