/*
 * RTC_Main.h
 *
 * Created: 1/3/2026 12:36:08 PM
 *  Author: Abhinav
 */ 


#ifndef RTC_MAIN_H_
#define RTC_MAIN_H_

#include "../I2C/I2C_Main.h"

struct rtc_time
{
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t isFresh;
};
typedef struct rtc_time rtc_time_t;

struct rtc_date
{
	uint8_t year;
	uint8_t month;
	uint8_t date;
	char* day;
	uint8_t isFresh;
};
typedef struct rtc_date rtc_date_t;

#define RTC_ADDRESS         0x68

#define REG_SECONDS         0x00
#define REG_MINUTES         0x01
#define REG_HOURS           0x02
#define REG_DAY             0x03
#define REG_DATE            0x04
#define REG_MONTH           0x05
#define REG_YEAR            0x06
#define REG_ALARM1_SECONDS  0x07
#define REG_ALARM1_MINUTES  0x08
#define REG_ALARM1_HOURS    0x09
#define REG_ALARM1_DAY      0x0A
#define REG_ALARM2_MINUTES  0x0B
#define REG_ALARM2_HOURS    0x0C
#define REG_ALARM2_DAY      0x0D
#define REG_CONTROL         0x0E
#define REG_STATUS          0x0F
#define REG_AGING_OFFSET    0x10
#define REG_TEMPERATURE_MSB 0x11
#define REG_TEMPERATURE_LSB 0x12

void RTC_check(void);
void RTC_read_time(rtc_time_t *rtc_time);
void RTC_read_date(rtc_date_t *rtc_date);
void RTC_enable_square_wave(void);
void RTC_write_time(uint8_t hour, uint8_t minute, uint8_t second);
void RTC_write_date(uint8_t day, uint8_t date, uint8_t month, uint8_t year);

#endif /* RTC_MAIN_H_ */