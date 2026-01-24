/*
 * I2C_Main.h
 *
 * Created: 1/3/2026 5:59:46 PM
 *  Author: Abhinav
 */ 


#ifndef I2C_MAIN_H_
#define I2C_MAIN_H_

#define F_CPU 8000000
#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <util/twi.h>
#include <stddef.h>
#include <stdint.h>

#define BAUD 32 // for 100 KHz I2C clock
#define SM 0 // Standard Mode - 100 KHz
#define FM 1 // Fast Mode - 400 KHz

void I2C_baud(unsigned char speed);

void I2C_init(void);
uint8_t I2C_start(void);
uint8_t I2C_rep_start(void);
void I2C_stop(void);
uint8_t I2C_addr(uint8_t addr);
uint8_t I2C_send(uint8_t data);
uint8_t I2C_read(uint8_t* data);
uint8_t BCD_DEC(uint8_t val);
uint8_t DEC_BCD(uint8_t val);

#endif /* I2C_MAIN_H_ */