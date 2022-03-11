/*
 ============================================================================
 Name        : uart.c
 Author      : Hussam Ali
 Description : UART Driver source file
 ============================================================================
 */

/******************************************* Used Libraries *****************************************/

#include "avr/io.h"
#include "uart.h"
#include "common_macros.h"



/******************************************* Functions Definitions *****************************************/

/* Function to initialize the UART */
void UART_init(const UART_Config* s_ConfigData)
{
	uint16 ubrr_value = 0;
	/* Double-speed mode */
	UCSRA = (1<<U2X);
	/* Enable Tx and Rx
	 * Disable interrupts
	 */
	UCSRB = (1<<TXEN) | (1<<RXEN);
	/* In case of 9-bit mode the set the UCSZ2 bit in the UCSRB register */
	UCSRB = (UCSRB & 0xFB) | (s_ConfigData->num_bits);
	/* Set the URSEL bit when writing in UCSRC register */
	UCSRC = (1<<URSEL);
	/* Insert the number of data bits required
	 * 5-Bit mode
	 * 6-Bit mode
	 * 7-Bit mode
	 * 8-Bit mode
	 * 9-Bit mode
	 */
	UCSRC = (UCSRC & 0xF9) | ((s_ConfigData->num_bits)<<1);
	/* Insert the number of parity bits required
	 * Parity disabled
	 * Even Parity
	 * Odd parity
	 */
	UCSRC = (UCSRC & 0xCF) | ((s_ConfigData->parity_bit)<<4);
	/* Insert the number of stop bits required
	 * 1 stop bit
	 * 2 stop bits
	 */
	UCSRC = (UCSRC & 0xF7) | ((s_ConfigData->stop_bits)<<3);
	/* Calculate UBBR value according to the given baud_rate */
	ubrr_value = (uint16)((F_CPU / (s_ConfigData->baud_rate * 8UL)) - 1);
	/* Insert first 8-bits in the UBRRL register and the rest in the UBRRH register */
	UBRRL = ubrr_value;
	UBRRH = ubrr_value>>8;
}

void UART_sendByte(uint8 data)
{
	/* Wait until the UDR is empty and ready to send a byte */
	while(BIT_IS_CLEAR(UCSRA, UDRE)) {}
	UDR = data;
}

uint8 UART_receiveByte(void)
{
	/* Wait until receiving is complete */
	while(BIT_IS_CLEAR(UCSRA, RXC)) {}
	return UDR;
}

void UART_sendString(const char *str)
{
	uint8 i = 0;
	while(str[i] != '\0')
	{
		UART_sendByte(str[i]);
		i++;
	}
}

void UART_receiveString(char *str)
{
	uint8 i = 0;
	/* Receive the first byte only to be able to check for the special Character
	 * which determines the end of the string which is '@'
	 */
	str[i] = UART_receiveByte();
	/* Receive until '@' is pressed */
	while(str[i] != '@')
	{
		i++;
		str[i] = UART_receiveByte();
	}
	/* Terminate the string with null terminator to indiciate the end of the string */
	str[i] = '\0';
}
