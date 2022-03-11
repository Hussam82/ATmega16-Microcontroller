/*
 ============================================================================
 Name        : motor.h
 Author      : Hussam Ali
 Description : DC-MOTOR driver source file
 ============================================================================
 */

#ifndef MOTOR_H_
#define MOTOR_H_


/******************************************* Used Libraries *****************************************/
#include "std_types.h"
#include "gpio.h"

/******************************************* Static Configurations *****************************************/
#define MOTOR_IN1_PORT_ID			PORTB_ID
#define MOTOR_IN1_PIN_ID			PIN0_ID
#define MOTOR_IN2_PORT_ID			PORTB_ID
#define MOTOR_IN2_PIN_ID			PIN1_ID


/******************************************* User-defined Types *****************************************/

/*
 * Enum to control the state of the motor
 * To stop the motor = 0
 * To make the motor rotate in clockwise direction = 1
 * To make the motor rotate in anticlockwise direction = 2
 */
typedef enum{
	MOTOR_STOP, MOTOR_CW, MOTOR_ACW
}DcMotor_State;


/******************************************* Functions Prototypes *****************************************/

/*
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver
 * Stop at the DC-Motor at the beginning through the GPIO driver
 */
void DcMotor_Init(void);


/*
 * The function responsible for rotating the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* MOTOR_H_ */
