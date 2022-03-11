A basic stopwatch implemented by using:
1. ATmega16 microcontroller with frequency 1Mhz
2. Timer1 in CTC mode to count the stopwatch time.
3. Six common-anode seven segments
4. 3 push buttons to control the stopwatch:
	-External Interrupt EXTI0 (Falling edge) ==> Reset the stopwatch
	-External Interrupt EXTI1 (Rising edge) ==>  Pause the stopwatch
	-External Interrupt EXTI2 (falling edge) ==> Resume the stopwatch
	
	
	
	