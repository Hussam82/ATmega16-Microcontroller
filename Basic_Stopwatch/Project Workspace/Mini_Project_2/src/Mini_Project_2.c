/* Stop_Watch_MIni_Project_2 
  Name: Hussam Ali 
  Diploma Number: 60 */



#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

/*Array contains the display value of each of the 6 7-segments*/
unsigned char segs_arr[6] = {0};
/*Flags which control the 6 7-segments to control which 7-seg is counting and which is not*/
unsigned char flags[5] = {0};


void Timer1_CTC_Init(void)
{
	TCCR1A = (1<<FOC1A) | (1<<COM1A0); //non-PWM mode - Toggle on compare match
	TCCR1B = (1<<WGM12) | (1<<CS11) | (1<<CS10); // CTC mode - Prescaler 64
	TIMSK |= (1<<OCIE1A); //Enable interrupt of timer1 in compare mode
	TCNT1 = 0;
	OCR1A = 15625; // each count is 64 microsec. so to get 1 sec we need 15625 counts
}

ISR(TIMER1_COMPA_vect)
{
	/* Write code to increment the stop watch every second (every compare match) */
	/* Increment Unit seconds */
	if(segs_arr[0] == 9)
	{
		flags[0] = 1;
		segs_arr[0] = 0;
	}
	else
	{
		segs_arr[0]++;
		flags[0] = 0;
		flags[1] = 0;
		flags[2] = 0;
		flags[3] = 0;
		flags[4] = 0;
	}
	/* Increment Tenth seconds */
	if((segs_arr[1] == 5) && (flags[0] == 1))
	{
		flags[1] = 1;
		segs_arr[1] = 0;
	}
	else if(flags[0] == 1)
	{
		segs_arr[1]++;
	}
	/* Increment Unit minutes */
	if((segs_arr[2] == 9) && (flags[1] == 1))
	{
		flags[2] = 1;
		segs_arr[2] = 0;
	}
	else if(flags[1] == 1)
	{
		segs_arr[2]++;
	}
	/* Increment Tenth minutes */
	if((segs_arr[3] == 5) && (flags[2] == 1))
	{
		flags[3] = 1;
		segs_arr[3] = 0;
	}
	else if(flags[2] == 1)
	{
		segs_arr[3]++;
	}
	/* Increment Unit hours */
	if((segs_arr[4] == 9) && (flags[3] == 1))
	{
		flags[4] = 1;
		segs_arr[4] = 0;

	}
	else if(flags[3] == 1)
	{
		segs_arr[4]++;

	}
	/* Increment Tenth hours */
	if((segs_arr[5] == 9) && (flags[4] == 1))
	{
		segs_arr[5] = 0;

	}
	else if(flags[4] == 1)
	{
		segs_arr[5]++;
	}
}

/* Configuring push button 1 on external interrupt 0 */
void INT0_Init(void)
{
	MCUCR |= (1<<ISC01); //INT0 falling edge
	GICR |= (1<<INT0); //Enable external INT0
	DDRD &= ~(1<<PD2); //set pin 2 of port D to be i/p
	PORTD |= (1<<PD2); //Enable internal pull up of pin 2 of port D
}

ISR(INT0_vect)
{
	/* Write code to reset the stop watch */
	for(unsigned char i = 0; i < 6; i++)
	{
		segs_arr[i] = 0;
	}
	TCNT1 = 0;
}

/* Configuring push button 2 on external interrupt 1 */
void INT1_Init(void)
{
	MCUCR |= (1<<ISC11) | (1<<ISC10); //INT1 Rising edge
	GICR |= (1<<INT1); //Enable external INT1
	DDRD &= ~(1<<PD3); //set pin 3 of port D to be i/p
}

ISR(INT1_vect)
{
	/* Write code to reset the pause the stop watch */
	TCCR1B &= 0xF8; // cut the clock
}

/* Configuring push button 3 on external interrupt 2 */
void INT2_Init(void)
{
	MCUCSR &= ~(1<<ISC2); //INT2 falling edge
	GICR |= (1<<INT2); //Enable external INT2
	DDRB &= ~(1<<PB2); //set pin 2 of port B to be i/p
	PORTB |= (1<<PB2); //Enable internal pull up of pin 2 of Port B
}

ISR(INT2_vect)
{
	/* Write code to reset the resume the stop watch */
	TCCR1B |= 0x03; // set the clock back on

}


int main(void)
{
	SREG |= (1<<7); // Enable I-Bit
	/* Configure the 7 segment */
	DDRC |= 0x0F; // first 4 pins of Port C as o/p
	PORTC &= 0xF0; //first 4 pins of Port C = 0
	DDRA |= 0x3F; //first 6 pins of Port A as o/p
	PORTA &= 0xC0; //first 6 pins of Port A = 0
	Timer1_CTC_Init();
	INT0_Init();
	INT1_Init();
	INT2_Init();
	while(1)
	{
		/* Keep the 6 7-segments always on displaying the number on each 7segment */
		for(unsigned char i = 0; i < 6; i++)
		{
			PORTA &= 0xC0; //disable the 6 7-segments
			PORTA |= (1<<i); //enable only the 7-seg at which the number will be displayed
			PORTC &= 0xF0; //set each 7-seg to 0
			PORTC = (PORTC & 0xF0) | (segs_arr[i] & 0x0F); //insert the number which will increment with the timer
			_delay_ms(3);
		}
	}
}
