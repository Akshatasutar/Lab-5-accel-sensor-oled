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


void initUART();
void uart_putc(unsigned char c);    //Sends a single character via UART
void uart_puts (char *s);    //Sends a complete string via UART
void uart_int(int i);    //Sends an Integer via UART
void uart_puti16B (uint16_t value);    //Sends an Integer in Binaryformat via UART

#endif /* _UART_H_ */
