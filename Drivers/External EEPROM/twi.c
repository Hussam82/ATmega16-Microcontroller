/*
 ============================================================================
 Name        : i2c.h
 Author      : Hussam Ali
 Description : I2C Driver Source file
 ============================================================================
 */


/******************************************* Used Libraries & Includes *****************************************/

#include "twi.h"
#include "common_macros.h"
#include <avr/io.h>



/******************************************* Functions Definitions *****************************************/
void TWI_init(const TWI_Config* s_ConfigData)
{
	/* TWINT = 0 TWI flag
	 * TWIEA = 0 Disable acknowledge bit
	 * TWSTA = 0 Disable start bit
	 * TWSTO = 0 Disable stop bit
	 * TWWC = 0 Write collision flag is disabled
	 * TWEN = 1 Enable the TWI module
	 * TWIE = 0 Disable interrupt enable of TWI
	 */
	TWCR = (1<<TWEN);
	/*
	 * TWPS1:0 = 0 (Prescaler bits)
	 * TWS7:3 = 0 (Status bits)
	 */
	TWSR = 0x00;
	/*
	 * This is the equation to determine the required TWBR
	 * register value to obtain the required Bitrate as given
	 * in the structure but we are assuming that Prescaler is
	 * one and F_CPU = 8MHz
	 */
	TWBR = (uint8)(8000000 / (2 * s_ConfigData->BIT_RATE)) - 8;
	/* The 7-BIT address of the device to be able to communicate with
	 *  the last bit TWGCE = 0 to disable the General Call Recognition
	 */
	TWAR = ((s_ConfigData->ADDRESS)<<1) | 0xFE;
}

void TWI_start(void)
{
	/* Clear the TWINT flag before the entering of every function
	 * Send the start bit by writing 1 to TWSTA
	 * Enable the TWI every time we enter a function
	 */
	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
	/* Wait until the start bit is transmitted (TWINT = 1)*/
	while(BIT_IS_CLEAR(TWCR, TWINT)) {}
}

void TWI_stop(void)
{
	/* Clear the TWINT flag before the entering of every function
	 * Send the stop bit by writing 1 to TWSTO
	 * Enable the TWI every time we enter a function
	 */
	TWCR = (1<<TWINT) | (1<<TWSTO) | (1<<TWEN);
	/* No need to use polling for TWINT flag as the stop bit
	 * means that the master has ended the entire transaction
	 */
}

void TWI_write(uint8 data)
{
	/* Put the data to be written in the TWDR register */
	TWDR = data;
	/* Clear the TWINT flag and enable the TWI module
	 * every time we enter a function
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Wait until the data is transmitted (TWINT = 1) */
	while(BIT_IS_CLEAR(TWCR, TWINT)) {}
}

uint8 TWI_readWithAck(void)
{
	/* Clear the TWINT flag and enable the TWI module
	 * every time we enter a function
	 * TWEA = 1 to read the data with ACK
	 */
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	/* Wait until the data is received (TWINT = 1) */
	while(BIT_IS_CLEAR(TWCR, TWINT)) {}
	return TWDR;
}

uint8 TWI_readWithNack(void)
{
	/* Clear the TWINT flag and enable the TWI module
	 * every time we enter a function
	 * TWEA = 0 to read the data with NACK
	 */
	TWCR = (1<<TWINT) | (1<<TWEN);
	/* Wait until the data is received (TWINT = 1) */
	while(BIT_IS_CLEAR(TWCR, TWINT)) {}
	return TWDR;
}

uint8 TWI_getStatus(void)
{
	uint8 status;
	/* We need the last 5 bits only TWS7:3
	 * so masked the register with 0b11111000
	 */
	status = (TWSR & 0xF8);
	return status;
}



