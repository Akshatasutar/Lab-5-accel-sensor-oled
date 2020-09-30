/*
 * Lab-5-us_sensor_accelerometer.c
 *
 * Created: 9/25/2020 10:38:29 AM
 * Author : Akshata
 */ 

#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "mpu6050.h"
#include "i2cmaster.h"
#define trigger_pin PORTB0
#define echo_pin PINB1

volatile uint8_t ovf_count_microsec;
volatile uint16_t dist;
volatile int x;
volatile int y;
volatile int z;

/*************************************************************
*Name: Main
*Purpose:  *
*Input:  *
*Output (return value): 
*************************************************************/
int main(void)
{
	initUART();
	lcd_init(0xAF);    // init lcd and turn on
	mpu6050_init();
	
	Print_pos("X:", 2, 0, 0);
	Print_pos("Y:", 2, 0, 1);
	Print_pos("Z:", 2, 0, 2);
	Print_pos("D:", 2, 0, 3);
		
	OCR0A = 20;    //ovf happens after 1 microsecond
	DDRB |= 1 << trigger_pin;

	init_timer0();    //Initialize timer - timer starts

    while (1) 
    {
		//ULTRASOUND (Uses functions from ultrasound.c):
		us_trigger();
		dist = us_get_distance_cm();
		//UDR0 = 'A';
		uart_int(dist);
		uart_puts("cm\n");   
		
		//ACCELEROMETER (Uses functions from mpu6050.c):
		mpu6050_getRawAccData(&x, &y, &z);
		
		//OLED DISPLAY (Uses functions from oledDisplay.c):
		print_int_value(x, 0);
		print_int_value(y, 1);
		print_int_value(z, 2);
		print_int_value(dist, 3);
    }
	
	return 0;
}

