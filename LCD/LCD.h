/*
 * IncFile1.h
 *
 * Created: 11/15/2025 11:29:00 PM
 *  Author: Abhinav
 */ 

#ifndef _LCD_H_
#define _LCD_H_

/*
RS PD2
EN PD3
D4 PD4
D5 PD5
D6 PD6
D7 PD7
*/

#define F_CPU 8000000
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7
#define LCD_EN 3
#define LCD_RS 2

#define LCD_DDR DDRD
#define LCD_PORT PORTD

#define LCD_CMD 0
#define LCD_DATA 1

void lcd_enable(void);
void lcd_send(int type, char data);
void lcd_putc(char c);
void lcd_init(void);
void lcd_clear(void);
void lcd_cursor(uint8_t row, uint8_t col);
void lcd_puts(uint8_t row, uint8_t col, char* data);
void lcd_write_num(uint8_t row, uint8_t col, uint32_t num);
void lcd_cursor_on(void);
void lcd_cursor_off(void);

#endif
