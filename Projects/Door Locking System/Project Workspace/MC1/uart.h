/*
 ============================================================================
 Name        : uart.h
 Author      : Hussam Ali
 Description : UART Driver header file
 ============================================================================
 */

#ifndef UART_H_
#define UART_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to hold the number of stop bits */
typedef enum{
	ONE_BIT_STOP, TWO_BIT_STOP
}UART_Stop_Bits;
/* Enum to hold the number of data bits */
typedef enum{
	FIVE_BIT_MODE, SIX_BIT_MODE, SEVEN_BIT_MODE, EIGHT_BIT_MODE, NINE_BIT_MODE = 7
}UART_Num_Bits;
/* Enum to hold Parity type */
typedef enum{
	PARITY_OFF, EVEN_PARITY = 2, ODD_PARITY
}UART_Parity_Bit;

/* Configuration Structure which holds:
 * Number of stop bits
 * Number of Data bits
 * Parity mode
 * Baud rate
 */
typedef struct{
	UART_Stop_Bits stop_bits;
	UART_Num_Bits num_bits;
	UART_Parity_Bit parity_bit;
	uint32 baud_rate;
}UART_Config;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function to Initialize the UART module
 * with the given configurations
 */
void UART_init(const UART_Config* s_ConfigData);
/*
 * Function to send a byte to another device
 */
void UART_sendByte(uint8 data);
/*
 * Function to receive a byte from another device
 */
uint8 UART_receiveByte(void);
/*
 * Function to send a string to another device
 */
void UART_sendString(const char *str);
/*
 * Function to receive a string from another device
 */
void UART_receiveString(char *str);

#endif /* UART_H_ */
