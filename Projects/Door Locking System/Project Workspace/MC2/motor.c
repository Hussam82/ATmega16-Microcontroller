/*
 ============================================================================
 Name        : motor.c
 Author      : Hussam Ali
 Description : DC-MOTOR driver source file
 ============================================================================
 */


/*******************************************************************************
 *                                Includes                                  *
 *******************************************************************************/

#include "motor.h"
#include "gpio.h"
#include "common_macros.h"
#include "avr/io.h"



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_init(void)
{
	/* Setup pins PB0 and PB1 as o.p pins */
	GPIO_setupPinDirection(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, PIN_OUTPUT);
	/* Initially the motor is not rotating */
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/* Function to rotate the motor in Clockwise direction */
void DcMotor_rotateCW(void)
{
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_HIGH);
}

/* Function to rotate the motor in Anti-Clockwise direction */
void DcMotor_rotateACW(void)
{
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}

/* Function to stop the motor */
void DcMotor_stop(void)
{
	GPIO_writePin(MOTOR_IN1_PORT_ID, MOTOR_IN1_PIN_ID, LOGIC_LOW);
	GPIO_writePin(MOTOR_IN2_PORT_ID, MOTOR_IN2_PIN_ID, LOGIC_LOW);
}



