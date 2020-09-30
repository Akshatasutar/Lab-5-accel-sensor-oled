/*
 * oledDisplay.c
 *
 * Created: 9/30/2020
 * Author : Akshata
 */ 

#define F_CPU 16000000UL
#include "lcd.h"
#include "i2cmaster.h"
#include "font.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>

int y,x;

/************************************************************************
*Name: Print_pos
*Purpose: Prints to the oled at pos x,y
*INput: The row and the column it shall be whiten on
*Output: void
*Anropar:lcd_clrscr(),lcd_gotoxy(),i2c_start(), i2c_byte(),i2c_stop()
************************************************************************/
void Print_pos(char* string, short length, int x, int y){	
	//lcd_clrscr();
	for (uint8_t c = 0; c < length; c++) {
		unsigned char letter = string[c];
		lcd_gotoxy(x+c, y);  //line x column y
		i2c_start(0x3c << 1);  //address of I2C oled
		i2c_byte(0x40);  //
		for (uint8_t i = 0; i < 7; i++)
		{
			i2c_byte(pgm_read_byte(&(FONT[letter - 32][i])));  // ASCII code - 32. Because font follows offset of 32 from ASCII
		}
	}
	
	i2c_stop();
}


/************************************************************
*Name: print_int_value
*Purpose: Covert read ADC value to string and print it on oled display
*Input: ADC value, row number - 0 for x and 1 for y
*Output: none
************************************************************/
void print_int_value(int int_value, uint8_t row){
	char* to_string = "";
	itoa (int_value, to_string, 10);
	Print_pos(to_string, 5, 3, row);
}
	



