/*
 * RTC_Main.c
 *
 * Created: 1/3/2026 12:35:54 PM
 *  Author: Abhinav
 */ 
#include "RTC_Main.h"

// void RTC_check(void)
// {
// 	unsigned char data = 0;
// 	data = I2C_read(RTC_ADDRESS, REG_STATUS);
// }

static char *dayname[7] = {
	"Sun",
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat"
};

void RTC_read_time(rtc_time_t *rtc_time)
{
	uint8_t data = 0;
    I2C_start();
    I2C_addr(RTC_ADDRESS << 1);
    I2C_send(0x00);
    I2C_rep_start();
    I2C_addr((RTC_ADDRESS << 1) | 1);
	I2C_read(&data);
	rtc_time->second = BCD_DEC(data);
	I2C_read(&data);
	rtc_time->minute = BCD_DEC(data);
	I2C_read(&data);
	rtc_time->hour = BCD_DEC(data);
}

void RTC_read_date(rtc_date_t *rtc_date)
{
	uint8_t data = 0;
    I2C_start();
    I2C_addr(RTC_ADDRESS << 1);
    I2C_send(0x03);
    I2C_rep_start();
    I2C_addr((RTC_ADDRESS << 1) | 1);
	I2C_read(&data);
	rtc_date->day = dayname[BCD_DEC(data)-1];
	I2C_read(&data);
	rtc_date->date = BCD_DEC(data);
	I2C_read(&data);
	rtc_date->month = BCD_DEC(data);
	I2C_read(&data);
	rtc_date->year = BCD_DEC(data);
}

// enables 1 Hz square wave output
void RTC_enable_square_wave(void)
{
	I2C_start();
	I2C_addr(RTC_ADDRESS << 1);
    I2C_send(0x0E);
	I2C_send(0x00);
}

void RTC_write_time(uint8_t hour, uint8_t minute, uint8_t second)
{
	I2C_start();
	I2C_addr(RTC_ADDRESS << 1);
	I2C_send(0x00);
	I2C_send(DEC_BCD(second));
	I2C_send(DEC_BCD(minute));
	I2C_send(DEC_BCD(hour));
}

void RTC_write_date(uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
	I2C_start();
	I2C_addr(RTC_ADDRESS << 1);
	I2C_send(0x03);
	I2C_send(DEC_BCD(day));
	I2C_send(DEC_BCD(date));
	I2C_send(DEC_BCD(month));
	I2C_send(DEC_BCD(year));
}
