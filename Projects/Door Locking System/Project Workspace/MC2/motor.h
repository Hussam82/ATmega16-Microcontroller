/*
 ============================================================================
 Name        : motor.h
 Author      : Hussam Ali
 Description : DC-MOTOR driver source file
 ============================================================================
 */

#ifndef MOTOR_H_
#define MOTOR_H_


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "std_types.h"
#include "gpio.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/

#define MOTOR_IN1_PORT_ID			PORTD_ID
#define MOTOR_IN1_PIN_ID			PIN2_ID
#define MOTOR_IN2_PORT_ID			PORTD_ID
#define MOTOR_IN2_PIN_ID			PIN3_ID


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_init(void);

/* Function to rotate the motor in Clockwise direction */
void DcMotor_rotateCW(void);

/* Function to rotate the motor in Anti-Clockwise direction */
void DcMotor_rotateACW(void);

/* Function to stop the motor */
void DcMotor_stop(void);

#endif /* MOTOR_H_ */
