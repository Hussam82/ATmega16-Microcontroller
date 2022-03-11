/*
 ============================================================================
 Name        : eeprom.h
 Author      : Hussam Ali
 Description : EEPROM Driver Header file
 ============================================================================
 */

#ifndef EXTERNAL_EEPROM_H_
#define EXTERNAL_EEPROM_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define ERROR		0
#define SUCCESS		1


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Function to write a byte into the external EEPROM memory */
uint8 EEPROM_writeByte(uint16 addr, uint8 data);
/* Function to read a byte from the external EEPROM memory */
uint8 EEPROM_readByte(uint16 addr, uint8* data);


#endif /* EEPROM_H_ */
