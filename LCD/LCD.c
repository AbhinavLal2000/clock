/*
 * CFile1.c
 *
 * Created: 11/15/2025 11:28:40 PM
 *  Author: Abhinav
 */ 
#include "LCD.h"

#define LCD_DELAY _delay_ms(2)

uint8_t icon_alarm[LCD_CHAR_MAX_SIZE] = ICON_DATA_ALARM;
uint8_t icon_clock[LCD_CHAR_MAX_SIZE] = ICON_DATA_CLOCK;
uint8_t icon_timer[LCD_CHAR_MAX_SIZE] = ICON_DATA_TIMER;
uint8_t icon_date[LCD_CHAR_MAX_SIZE] = ICON_DATA_DATE;
uint8_t icon_play[LCD_CHAR_MAX_SIZE] = ICON_DATA_PLAY;
uint8_t icon_pause[LCD_CHAR_MAX_SIZE] = ICON_DATA_PAUSE;
uint8_t icon_ok[LCD_CHAR_MAX_SIZE] = ICON_DATA_OK;
uint8_t *icons[MAX_ICONS] = {icon_alarm, icon_clock, icon_timer, icon_date,
							 icon_play, icon_pause, icon_ok};

void lcd_enable(void)
{
	LCD_PORT |= (1 << LCD_EN);
	LCD_DELAY;
	LCD_PORT &= ~(1 << LCD_EN);
	LCD_DELAY;
}

void lcd_send(int type, char data)
{
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0); //send upper 4 bit
	type ? (LCD_PORT |= (1 << LCD_RS)) : (LCD_PORT &= ~(1 << LCD_RS));
	lcd_enable();
	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4); //send lower 4 bit
	lcd_enable();
}

void lcd_init(void)
{
	LCD_DDR |= (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
	LCD_DDR |= (1 << LCD_EN) | (1 << LCD_RS);
	LCD_PORT = 0x00;
	lcd_send(LCD_CMD, 0x33);
	lcd_send(LCD_CMD, 0x32);
	lcd_send(LCD_CMD, 0x28);
	lcd_send(LCD_CMD, 0x0C); 
	lcd_send(LCD_CMD, 0x01); 
}

void lcd_putc(char c)
{
	lcd_send(LCD_DATA, c);
}

void lcd_clear(void)
{
	lcd_send(LCD_CMD, 0x01);
}

void lcd_cursor(uint8_t row, uint8_t col)
{
	uint8_t addr = (row == 0) ? 0x80 : 0xC0;
	addr += col;
	lcd_send(LCD_CMD, (char)addr);
}

void lcd_puts(uint8_t row, uint8_t col, char* data)
{
	lcd_cursor(row, col);
	while (*data)
	{
		lcd_putc(*data);
		data++;
	}
}

void lcd_write_num(uint8_t row, uint8_t col, uint32_t num)
{
	char buff[16];
	memset(buff, 0, 16);
	sprintf(buff, "%ld", num);
	lcd_puts(row, col, buff);
}

void lcd_cursor_on(void)
{
	lcd_send(LCD_CMD, 0x0F); 
}

void lcd_cursor_off(void)
{
	lcd_send(LCD_CMD, 0x0C);
}

void lcd_load_custom_char(uint8_t index, uint8_t *charmap)
{
	if (index > (LCD_CHAR_MAX_SIZE - 1))
		return;

	lcd_send(LCD_CMD, 0x40 | index << 3); // command to store custom char in CG ram at index location, only 8 chars can be stored
	for (uint8_t i = 0; i < LCD_CHAR_MAX_SIZE; i++)
	{
		lcd_putc(charmap[i]);
	}
}

void lcd_draw_char(uint8_t row, uint8_t col, uint8_t index)
{
	lcd_load_custom_char(index, icons[index]);
	lcd_cursor(row, col);
	lcd_putc(index);
}