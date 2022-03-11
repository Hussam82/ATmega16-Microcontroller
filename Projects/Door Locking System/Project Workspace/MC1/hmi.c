 /*
 ============================================================================
 Name        : hmi.c
 Author      : Hussam Ali
 Description : HMI (Human Machine Interface) ECU source file
 ============================================================================
 */


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

/* Keypad Driver */
#include "keypad.h"
/* LCD Driver */
#include "lcd.h"
/* UART Driver */
#include "uart.h"
/* Timer Driver */
#include "timer.h"
/* Delay Library */
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

/* To determine how many times the Pin is wrong */
static uint8 count = 0;
/* Timer configuration Structure */
Timer_Config s_TimerConfigData = {TIMER1_ID, 0, 8000, COMPARE_MODE, TIMER1_1024};
/* To store the ticks for the Motor timing */
static uint8 g_ticks = 0;
/* Flag to determine whether the processor
 * should continue in the while(1) or not
 */
static uint8 term_flag = 0;


/*******************************************************************************
 *                                Function Definitions                         *
 *******************************************************************************/

/* The call back function which displays the state of the Motor as follows
 * Display "Opening..." for 15 seconds
 * Display "STOPPED" for 3 seconds
 * Display "Closing..." for 15 seconds
 */
void APP_openDoor(void)
{
	g_ticks++;
	if(g_ticks == 1)
	{
		LCD_clearScreen();
		LCD_displayString("Opening...");
	}
	else if(g_ticks == 15)
	{
		LCD_clearScreen();
		LCD_displayString("STOPPED");
	}
	else if(g_ticks == 18)
	{
		LCD_clearScreen();
		LCD_displayString("Closing...");
	}
	else if(g_ticks == 33)
	{
		/* Reset the ticks when done */
		g_ticks = 0;
		/* Clear the flag when done */
		term_flag = 0;
		LCD_clearScreen();
		/* De-initialize the timer when done */
		Timer_deInit(TIMER1_ID);
	}
}

/* Function to create a new Pin and verifying it once to
 * send it MC2 to be stored in the EEPROM
 */
void APP_getThePin(void)
{
	/* Array to hold the Pin */
	uint8 pin[5];
	/* Array to store a copy from the received pin to verify it */
	uint8 re_pin[5];
	uint8 i;
	/* Flag to indicate whether the pin entered is right or wrong */
	uint8 flag;
	do{
		LCD_displayString("Enter new PIN:");
		/* Get the 5 numbers pin from the user */
		for(i = 0; i < 5; i++)
		{
			pin[i] = KEYPAD_getPressedKey();
			_delay_ms(500);
			LCD_moveCursor(1, i);
			LCD_displayCharacter('*');
		}
		/* Wait until the user presses Enter */
		while(KEYPAD_getPressedKey() != 13) {}
		_delay_ms(500);
		LCD_clearScreen();
		LCD_displayString("Re-enter the PIN:");
		/* Re-take the pin from the user to verify it */
		for(i = 0; i < 5; i++)
		{
			re_pin[i] = KEYPAD_getPressedKey();
			_delay_ms(500);
			LCD_moveCursor(1, i);
			LCD_displayCharacter('*');
		}
		while(KEYPAD_getPressedKey() != 13) {}
		_delay_ms(500);
		LCD_clearScreen();
		/* Compare the entered pin in the two times */
		for(i = 0; i < 5; i++)
		{
			if(pin[i] != re_pin[i])
			{
				/* Break the loop when u find a mismatch in the pin */
				flag = 1;
				break;
			}
			else
			{
				flag = 0;
			}
		}
		if(flag == 1)
		{
			LCD_displayString("PIN not matched");
			LCD_moveCursor(1, 0);
			LCD_displayString("Try again !");
			_delay_ms(1000);
		}
		/* If the flag = 0, this means that the user entered the pin correctly
		 * and that means that we have to sent the pin to MC2 to store it in
		 * the EEPROM
		 */
		else if(flag == 0)
		{
			while(UART_receiveByte() != CONTROL_READY) {}
			for(i = 0; i < 5; i++)
			{
				UART_sendByte(pin[i]);
			}
			LCD_displayString("Success");
		}

		LCD_clearScreen();
	/* Stay in the do while loop until the pin is entered correctly */
	}while(flag == 1);

}

/* Callback function to display ERROR message for 1 minute
 * when the user attempts to write the pin wrong for 3 times
 */
void APP_errorMsg(void)
{
	g_ticks++;
	if(g_ticks == 1)
	{
		LCD_clearScreen();
		LCD_displayString("ERROR");
	}
	else if(g_ticks == 60)
	{
		/* Reset the ticks when done */
		g_ticks = 0;
		/* Clear the flag when done */
		term_flag = 0;
		LCD_clearScreen();
		/* De-initialize the timer when done */
		Timer_deInit(TIMER1_ID);
	}
}

/* Function to verify the pin taken from the user
 * It takes the pin array and address of the flag
 * as arguments
 */
void APP_verifyPin(uint8* pin, uint8* flag)
{
	uint8 i;
	do{
		count++;
		/* if the user entered the pin 3 times wrong
		 * display error message for 1 minute
		 */
		if(count == 4)
		{
			/* Take the flag to prevent the processor from going through
			 * the while(1) until the error message disappears
			 */
			term_flag = 1;
			Timer_init(&s_TimerConfigData);
			Timer_setCallBack1(APP_errorMsg);
			break;
		}
		LCD_clearScreen();
		LCD_displayString("Enter the PIN:");
		/* Get the pin from the user */
		for(i = 0; i < 5; i++)
		{
			pin[i] = KEYPAD_getPressedKey();
			_delay_ms(500);
			LCD_moveCursor(1, i);
			LCD_displayCharacter('*');
		}
		/* Wait until user presses Enter key */
		while(KEYPAD_getPressedKey() != 13) {}
		_delay_ms(500);
		/* Send the Pin to MC2 */
		for(i = 0; i < 5; i++)
		{
			UART_sendByte(pin[i]);
		}
		/* Receive the flag from MC2 which indicates whether the
		 * sent pin is correct or no
		 */
		*flag = UART_receiveByte();
	/* Stay in the do while until the user enters the pin correctly */
	}while(*flag == 1);
}


/*******************************************************************************
 *                                Main Function                                *
 *******************************************************************************/
int main(void)
{
	/* To store the Pin values */
	uint8 pin[5];
	/* To indicate which operation to be performed */
	uint8 option;
	/* Flag to indicate whether the pin is entered correctly
	 * or not
	 */
	uint8 flag = 0;
	/* Enable the I-bit to enable Interrupts */
	SREG |= (1<<7);
	/* UART configuration Structure
	 * ONE STOP BIT
	 * EIGHT BIT MODE
	 * NO PARITY
	 * BAUD RATE 9600
	 */
	UART_Config s_UARTConfigData = {ONE_BIT_STOP, EIGHT_BIT_MODE, PARITY_OFF, 9600};
	/* Initialize the UART driver with the given structure */
	UART_init(&s_UARTConfigData);
	/* Initialize the LCD driver */
	LCD_init();
	/* Request from the user to enter the Pin and check for it only once
	 * to be stored in the EEPROM
	 */
	APP_getThePin();
	while(1)
	{
		/* The interface displayed to the user */
		LCD_displayString("+: Open Door");
		LCD_moveCursor(1, 0);
		LCD_displayString("-: Change PIN");
		/* The pin from the user */
		option = KEYPAD_getPressedKey();
		/* Delay 500ms which is enough to take the pressed key from the user */
		_delay_ms(500);
		LCD_clearScreen();
		/* Send the option chosen by the user to MC2 */
		UART_sendByte(option);
		/* '+' indicates that user wants to Rotate the door */
		if(option == '+')
		{
			/* Attempt to take the pin from the user and verify it */
			APP_verifyPin(pin, &flag);
			/* if flag = 0, this means that the entered pin is correct */
			if(flag == 0)
			{
				count = 0;
				term_flag = 1;
				Timer_init(&s_TimerConfigData);
				Timer_setCallBack1(APP_openDoor);
			}
		}
		/* '-' indicates that the user wants to change the pin */
		else if(option == '-')
		{
			/* Attempt to take the pin from the user and verify it */
			APP_verifyPin(pin, &flag);
			/* flag = 0 means that the user entered the pin correctly */
			if(flag == 0)
			{
				count = 0;
				LCD_clearScreen();
				APP_getThePin();
				LCD_displayString("PIN Changed");
				LCD_moveCursor(1, 0);
				LCD_displayString("Successfully !");
				_delay_ms(1000);
				LCD_clearScreen();
			}
		}
		LCD_clearScreen();
		/* Do nothing when the door is opening or closing and when the Buzzer goes off */
		while(term_flag == 1) {}
	}
}
