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

#define LCD_CHAR_MAX_SIZE 8
#define MAX_ICONS 7
#define ICON_INDEX_ALARM 0
#define ICON_INDEX_CLOCK 1
#define ICON_INDEX_TIMER 2
#define ICON_INDEX_DATE  3
#define ICON_INDEX_PLAY  4
#define ICON_INDEX_PAUSE 5
#define ICON_INDEX_OK    6

#define ICON_DATA_ALARM {0x00,0x04,0x0E,0x0E,0x0E,0x1F,0x04,0x00}
#define ICON_DATA_CLOCK {0x00,0x0E,0x15,0x17,0x11,0x0E,0x00,0x00}
#define ICON_DATA_TIMER {0x00,0x0E,0x04,0x0E,0x11,0x1D,0x15,0x0E}
#define ICON_DATA_DATE  {0x00,0x1F,0x1F,0x11,0x15,0x11,0x1F,0x00}
#define ICON_DATA_PLAY  {0x00,0x18,0x1C,0x1E,0x1E,0x1C,0x18,0x00}
#define ICON_DATA_PAUSE {0x00,0x00,0x0E,0x0E,0x0E,0x0E,0x00,0x00}
#define ICON_DATA_OK    {0x00,0x01,0x03,0x16,0x1C,0x08,0x00,0x00}

extern uint8_t icon_alarm[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_clock[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_timer[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_date[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_play[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_pause[LCD_CHAR_MAX_SIZE];
extern uint8_t icon_ok[LCD_CHAR_MAX_SIZE];
extern uint8_t *icons[MAX_ICONS];

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
void lcd_load_custom_char(uint8_t index, uint8_t *charmap);
void lcd_draw_char(uint8_t row, uint8_t col, uint8_t index);

#endif
