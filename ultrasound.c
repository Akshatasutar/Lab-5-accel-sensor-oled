/*
Ultrasound sensor functions
Akshata
29-09-2020
*/

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#define trigger_pin PORTB0
#define echo_pin PINB1

volatile uint8_t ovf_count_microsec;

ISR(TIMER0_OVF_vect){
	ovf_count_microsec++;
}

/*************************************************************
*Name: init_timer0
*Purpose:  Initialize Timer 0
*Input:  none
*Output (return value): none
*************************************************************/
void init_timer0() {
	ovf_count_microsec = 0;			// initialize overflow count

	TCCR0B |= (1 << CS00);			//no pre-scaling
	TCCR0A |= (1 << WGM01);			// CTC mode
	TIMSK0 |= (1 << TOIE0);    // enable Timer 0 overflow interrupt
	TIFR0 = 1 << TOV0;
	TCNT0 = 0;				//Initialize timer counter to start from 0
	sei();
}

/*************************************************************
*Name: us_trigger
*Purpose: Send trigger pulse to ultrasound sensor for 10 microseconds *
*Input:  *
*Output (return value):
*************************************************************/
void us_trigger() {
	PORTB |= (1 << trigger_pin);    //supply 10 microsecond burst to trigger
	_delay_us(10);
	PORTB &= ~(1<<trigger_pin);    //Stop trigger - set trigger pin to 0
	
	uart_puts("Burst supplied\n");
}

/*************************************************************
*Name: us_get_distance_cm
*Purpose: Send trigger pulse to ultrasound sensor for 10 microseconds *
*Input:  *
*Output (return value):distance in cm
*************************************************************/
int us_get_distance_cm() {
	uint16_t echo_time = 0;
	int dist;
	
	while (!(PINB & (1 << echo_pin))){}   //Echo is low - do nothing
	ovf_count_microsec = 0;
	while ((PINB & (1 << echo_pin))){   //When echo is high
		//starts counting time
	}

	echo_time = ovf_count_microsec;    //stores counted time in variable
	uart_puts("echo time recorded \n");
	uart_int(echo_time);
	uart_puts("\n");
	
	//ovf_count_microsec = 0;
	
	dist = echo_time * 0.017; //distance(cm) = [time * velocity(340m/s)]/2
	_delay_us(200);
	
	return dist;
}