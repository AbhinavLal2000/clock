/*
 * HelloWorld.c
 *
 * Created: 11/15/2025 11:21:20 AM
 * Author : Abhinav
 */ 
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include "LCD/LCD.h"
#include "RTC/RTC_Main.h"
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>


#define BUTTON_Reg       DDRC
#define BUTTON_OK        (PINC & 0x02)
#define BUTTON_UP        (PINC & 0x01)
#define BUTTON_BACK      (PINC & 0x04)

#define MAX_OPTION       4
#define OPTION_ALARM     0
#define OPTION_STOPWATCH 1
#define OPTION_TIMER     2
#define OPTION_TIME      3

volatile rtc_time_t rtc_current_time;
volatile rtc_date_t rtc_current_date;

uint32_t count;
uint8_t option_index;
volatile uint64_t system_seconds;
volatile uint8_t tick;

char *option[MAX_OPTION] = {
	"Alarm",
	"Stopwatch",
	"Timer",
	"Time"
};

void PCINT_PD0_init(void)
{
    // PD0 as input
    DDRD &= ~(1 << DDD0);

    // Enable pull-up (optional)
    PORTD |= (1 << PORTD0);

    // Enable Pin Change Interrupt for PORTD
    PCICR |= (1 << PCIE2);

    // Enable PCINT16 (PD0)
    PCMSK2 |= (1 << PCINT16);

    // Enable global interrupts
    sei();
}

ISR(PCINT2_vect)
{
	// update current date and time buffer
	RTC_read_time((rtc_time_t*)&rtc_current_time);
	RTC_read_date((rtc_date_t*)&rtc_current_date);
	tick++;
	if (tick == 2)
	{
		tick = 0;
		system_seconds++;
		if (system_seconds == INT_FAST64_MAX)
		{
			system_seconds = 0;
		}
	}
}

void process_alarm(void)
{
	uint8_t data[3] = {0}; // HH,MM,SS
	uint8_t index = 0;

	while (BUTTON_BACK != 1)
	{
		if (BUTTON_UP == 1)
		{
			data[index]++;
		}
		if (BUTTON_OK == 1)
		{
			index++;
		}
	}

	// save alarm values
}

void display_current_date_time(void)
{
	char buffer[16];
	while (1)
	{
		if (BUTTON_BACK)
		{
			_delay_ms(200);
			return;
		}
		memset(buffer, 0, 16);
		sprintf(buffer, "%02d:%02d:%02d", rtc_current_time.hour, rtc_current_time.minute, rtc_current_time.second);
		lcd_puts(0, 4, buffer);
		memset(buffer, 0, 16);
		sprintf(buffer, "%s %02d %02d %02d", rtc_current_date.day, rtc_current_date.date, rtc_current_date.month, rtc_current_date.year);
		lcd_puts(1, 2, buffer);
	}
}

void process_stopwatch(void)
{
	uint8_t start = 0;
	uint8_t counter[3] = {0,0,0};
	char buffer[16];

	while (1)
	{
		if (BUTTON_BACK)
		{
			_delay_ms(200);
			return;
		}
		if (BUTTON_OK)
		{
			_delay_ms(200);
			start ^= 1;
			if (start == 1)
			{
				system_seconds = 0;
				tick = 0;
				counter[0] = 0;
				counter[1] = 0;
				counter[2] = 0;
			}
		}
		if (start == 1)
		{
			counter[2] = system_seconds;
			if (counter[2] == 60)
			{
				tick = 0;
				system_seconds = 0;
				counter[2] = 0;
				counter[1]++;
				if (counter[1] == 60)
				{
					counter[1] = 0;
					counter[0]++;
				}
			}
		}
		memset(buffer, 0, 16);
		sprintf(buffer, "%02d:%02d:%02d", counter[0], counter[1], counter[2]);
		lcd_puts(0, 4, buffer);
	}
}

void process_timer(void)
{
	char buffer[16];
	uint8_t counter[3] = {0,0,0};
	uint8_t index = 2;
	uint8_t run = 1;

	memset(buffer, 0, 16);
	sprintf(buffer, "%02d:%02d:%02d", counter[0], counter[1], counter[2]);
	lcd_puts(0, 4, buffer);

	lcd_cursor_on();
	while (run)
	{
		if (BUTTON_BACK)
		{
			_delay_ms(200);
			run = 0;
		}
		if (BUTTON_OK)
		{
			_delay_ms(200);
			counter[index]++;
			memset(buffer, 0, 16);
			sprintf(buffer, "%02d:%02d:%02d", counter[0], counter[1], counter[2]);
			lcd_puts(0, 4, buffer);
		}
		if (BUTTON_UP)
		{
			_delay_ms(200);
			index++;
			if (index > 2)
			{
				index = 0;
			}
			lcd_cursor(0, 4+(index*3));
		}
	}
	lcd_cursor_off();
}

void init_buttons(void)
{
	BUTTON_Reg = 0x00;
}

int main(void)
{
	PCINT_PD0_init();
	I2C_init();
    lcd_init();
	init_buttons();
	
#if 0
	cli();
	DDRB = 0x00;
	PORTB = 0x00;
	RTC_write_time(10, 40, 0);
	PORTB = 0x01;
	while (1){}
#endif
	
	RTC_enable_square_wave();
	display_current_date_time();
	lcd_clear();
	lcd_puts(0, 0, option[option_index]);
	
	while (1) 
    {
		if (BUTTON_OK)
		{
			_delay_ms(200);
			lcd_clear();
			switch (option_index)
			{
				case OPTION_ALARM:
				//process_alarm();
				break;

				case OPTION_STOPWATCH:
				process_stopwatch();
				break;

				case OPTION_TIMER:
				process_timer();
				break;

				case OPTION_TIME:
				display_current_date_time();
				break;
			}
			lcd_clear();
			lcd_puts(0, 0, option[option_index]);
		}
		
		if (BUTTON_UP)
		{
			_delay_ms(200);
			option_index++;
			if (option_index == MAX_OPTION)
			{
				option_index = 0;
			}
			lcd_clear();
			lcd_puts(0, 0, option[option_index]);
		}
    }
}
