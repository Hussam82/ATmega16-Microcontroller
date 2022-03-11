/*
 ============================================================================
 Name        : i2c.h
 Author      : Hussam Ali
 Description : I2C Driver header file
 ============================================================================
 */
#ifndef TWI_H_
#define TWI_H_

/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                               Types Declaration                             *
 *******************************************************************************/

/* Enum to carry the Bit rate values at which the I2C sends the data */
typedef enum{
	BR_100 = 100000, BR_400 = 400000
}TWI_BR;
/* Configuration Structure which holds:
 * Device address
 * Bit rate
 */
typedef struct{
	uint8 ADDRESS;
	TWI_BR BIT_RATE;
}TWI_Config;

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define TWI_START			0x08	/* Start transmitted */
#define TWI_REP_START		0x10	/* Repeated start transmitted */
#define TWI_MT_SLA_W_ACK	0x18	/* Master transmitted the byte (address + R/W = 0) and the slave replied with ACK */
#define TWI_MT_SLA_R_ACK	0x40	/* Master transmitted the byte (address + R/W = 1) and the slave replied with ACK */
#define TWI_MT_DATA_ACK		0x28	/* Master transmitted the byte (data) and the slave replied with ACK */
#define TWI_MR_DATA_ACK		0x50	/* Master received the byte (data) from the slave and replied with ACK */
#define TWI_MR_DATA_NACK	0x58	/* Master received the byte (data) from the slave and replied with NACK */


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * Function to initialize the I2C(TWI) module with the given configurations
 */
void TWI_init(const TWI_Config* s_ConfigData);
/* Function to send the start bit to start the
 * transmission
 */
void TWI_start(void);
/* Function to send the stop bit to stop the
 * transmission
 */
void TWI_stop(void);
/* Function to write data to the I2C bus */
void TWI_write(uint8 data);
/* Function to read the data replying with ACK to
 * continue sending more bytes
 */
uint8 TWI_readWithAck(void);
/* Function to read the data replying with NACK to
 * stop sending more bytes
 */
uint8 TWI_readWithNack(void);
/* Function to read the 5 bits in the TWSR which determines
 * the status of the Frame
 */
uint8 TWI_getStatus(void);


#endif /* TWI_H_ */
