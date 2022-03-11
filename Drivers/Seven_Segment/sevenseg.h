/*
 ============================================================================
 Name        : sevenseg.h
 Author      : Hussam Ali
 Description : Seven Segment Driver header file
 ============================================================================
 */

#ifndef SEVENSEG_H_
#define SEVENSEG_H_


/******************************************* Used Libraries *****************************************/
#include "std_types.h"




/******************************************* Static Configurations *****************************************/
#define SEG_PORT			PORTD_ID
#define SEG_PIN1			PIN0_ID
#define SEG_PIN2			PIN1_ID
#define SEG_PIN3			PIN2_ID
#define SEG_PIN4			PIN3_ID



/******************************************* Functions Prototypes *****************************************/
/*
 * Function initialize the seven segment
 */
void SEVENSEG_init(void);

/*
 * Function to display the given digit on the seven segment display
 */
void SEVENSEG_displayDigit(uint8 num);

#endif /* SEVENSEG_H_ */
