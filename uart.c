#ifndef _UART_H_
#define _UART_H_

#include <avr/io.h>  
#include <stdlib.h>			// for integer -> char converting  

#ifndef F_CPU
/* prevent compiler error by supplying a default */
# warning "F_CPU not defined. Define F_CPU with 16 Mhz."
#define F_CPU 16000000UL    // Quarz with 16 Mhz  */
#endif

#define UART_BAUDRATE 9600 
#define UART_BAUD_SELECT ((F_CPU / (UART_BAUDRATE * 16L))-1) 

/******************************************************************//**
 * Sends a single character via UART (eg. to a Hyperterminal).
 *********************************************************************/
void initUART()
{
	UBRR0H = (UART_BAUD_SELECT>>8); 
  	UBRR0L = UART_BAUD_SELECT; 

	UCSR0B |= (1<<TXEN0)|(1<<RXEN0); 	//Transmit/Receive enable
	
 	UCSR0C |= (1<<UCSZ01)|(1<<UCSZ00); 
 	UCSR0C &= ~(1<<UMSEL00) & ~(1<<UPM00) & ~(1<<USBS0);
}

/******************************************************************//**
 * Sends a single character via UART (eg. to a Hyperterminal).
 *********************************************************************/
void uart_putc(unsigned char c)
{
    while (!(UCSR0A & (1<<UDRE0)))  // wait until sending is possible
    {
    }                             
    UDR0 = c;                       // sending signs
}
 
/******************************************************************//**
 * Sends a complete string via UART (eg. to a Hyperterminal).
 *********************************************************************/
void uart_puts (char *s)
{
    while (*s)
    {                               // sending char until "/0"
        uart_putc(*s);
        s++;
    }
}

/*************************************************************
*Name: uart_int
*Purpose:  Converts integer to string to send to serial monitor*
*Input:  Integer to be converted*
*Output (return value): none
*************************************************************/
void uart_int(int i) {
	char* int_to_string = "";
	itoa(i, int_to_string, 10);
	uart_puts(int_to_string);
}

/******************************************************************//**
 * Sends an Integer in Binaryformat via UART (eg. to a Hyperterminal).
 *********************************************************************/
void uart_puti16B (uint16_t value)
{
	char _buffer[17];
	itoa( value, _buffer, 2 );	//conversion from integer to char
	uart_puts(_buffer);
}

#endif /* _UART_H_ */
