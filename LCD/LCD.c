/*
 * CFile1.c
 *
 * Created: 11/15/2025 11:28:40 PM
 *  Author: Abhinav
 */ 
#include "LCD.h"

#define LCD_DELAY _delay_ms(2)

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