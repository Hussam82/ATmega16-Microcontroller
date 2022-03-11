/*
 ============================================================================
 Name        : eeprom.c
 Author      : Hussam Ali
 Description : EEPROM Driver Source file
 ============================================================================
 */



/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "external_eeprom.h"
#include "twi.h"





/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/* Function to write a byte into the external EEPROM memory */
uint8 EEPROM_writeByte(uint16 addr, uint8 data)
{
	/* Send the start bit to begin the transaction */
	TWI_start();
	/* Check if the start is transmitted or not */
	if(TWI_getStatus() != TWI_START)
		return ERROR;
	/* Send the device address which is composed of
	 * 1010 then the MSB 3 bits of the addr then
	 * R/W = 0(write)
	 */
	TWI_write((uint8)(((addr & 0x0700)>>7) | 0xA0));
	/* Ensure that the master transmitted the address and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
    /* Send the first 8 bits of addr */
	TWI_write((uint8)addr);
	/* Ensure that the master transmitted the address and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
    /* Send the actual data */
	TWI_write(data);
	/* Ensure that the master transmitted the data and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
    /* Send the stop bit to terminate the transaction */
    TWI_stop();
    return SUCCESS;
}

/* Function to read a byte from the external EEPROM memory */
uint8 EEPROM_readByte(uint16 addr, uint8* data)
{
	/* Send the start bit to begin the transaction */
	TWI_start();
	/* Check if the start is transmitted or not */
	if(TWI_getStatus() != TWI_START)
		return ERROR;
	/* Send the device address which is composed of
	 * 1010 then the MSB 3 bits of the addr then
	 * R/W = 0(write)
	 */
	TWI_write((uint8)(((addr & 0x0700)>>7) | 0xA0));
	/* Ensure that the master transmitted the address and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;
    /* Send the first 8 bits of addr */
	TWI_write((uint8)addr);
	/* Ensure that the master transmitted the address and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;
    /* Send the repeated start */
	TWI_start();
	/* Check if the start is transmitted or not */
	if(TWI_getStatus() != TWI_REP_START)
		return ERROR;
	/* Send the device address which is composed of
	 * 1010 then the MSB 3 bits of the addr then
	 * R/W = 1(write)
	 */
	TWI_write((uint8)(((addr & 0x0700)>>7) | 0xA1));
	/* Ensure that the master transmitted the address and the slave
	 * received it successfully and replied with ACK
	 */
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;
    /* Read the data and send NACK to stop sending  */
    *data = TWI_readWithNack();
    /* Ensure that the master received the data from the
     * slave and replied with NACK successfully
     */
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;
    /* Send the stop bit */
    TWI_stop();
    return SUCCESS;
}
