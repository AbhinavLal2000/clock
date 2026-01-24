/*
 * I2C_Main.c
 *
 * Created: 1/3/2026 5:59:26 PM
 *  Author: Abhinav
 */ 

#include "I2C_Main.h"

void I2C_baud(unsigned char speed)
{
	TWSR = 0x00;
	switch (speed)
	{
		case SM:
		TWBR = BAUD;
		break;
		
		case FM:
		break;
	}
	TWCR = (1<<TWEN);
}

// unsigned char I2C_read(unsigned char slave, unsigned char reg)
// {
// 	unsigned char data = 0xFF;
// 	
// 	// START condition
// 	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
// 	while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag set. This indicates that the START condition has been transmitted
// // 	if ((TWSR & TW_STATUS_MASK) != TW_START) // Check value of TWI status register. Mask prescaler bits
// // 	{
// // 		return data-1;
// // 	}
// 	
// 	// Slave write mode
// 	TWDR = (slave << 1) | TW_WRITE;
// 	TWCR = (1<<TWINT)|(1<<TWEN); // Start transmission
// 	while (!(TWCR & (1 << TWINT)));  // Wait for TWINT flag set. This indicates that the START condition has been transmitted
// // 	if ((TWSR & TW_STATUS_MASK) != TW_MT_SLA_ACK) // Check value of TWI status register. Mask prescaler bits
// // 	{
// // 		return data-2;
// // 	}
// 	
// 	// Set read address
// 	TWDR = reg; // RTC DS3231 status register
// 	TWCR = (1<<TWINT)|(1<<TWEN); // Start transmission
// 	while (!(TWCR & (1 << TWINT)));
// // 	if ((TWSR & TW_STATUS_MASK) != TW_MT_DATA_ACK)
// // 	{
// // 		return data-3;
// // 	}
// 	
// 	// Repeated START condition
// 	TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
// 	while (!(TWCR & (1<<TWINT)));  // Wait for TWINT flag set. This indicates that the START condition has been transmitted
// // 	if ((TWSR & TW_STATUS_MASK) != TW_REP_START) // Check value of TWI status register. Mask prescaler bits
// // 	{
// // 		return data-4;
// // 	}
// 	
// 	// Slave read mode
// 	TWDR = (slave << 1) | TW_READ;
// 	TWCR = (1<<TWINT)|(1<<TWEN); // Start transmission
// 	while (!(TWCR & (1 << TWINT)));  // Wait for TWINT flag set. This indicates that the START condition has been transmitted
// // 	if ((TWSR & TW_STATUS_MASK) != TW_MR_SLA_ACK) // Check value of TWI status register. Mask prescaler bits
// // 	{
// // 		return data-5;
// // 	}
// 	
// 	// Read register
// 	TWCR = (1<<TWINT)|(1<<TWEN); // Start Read, ACK enabled
// 	while (!(TWCR & (1 << TWINT)));
// 	data = TWDR;
// // 	if ((TWSR & TW_STATUS_MASK) != TW_MR_DATA_ACK)
// // 	{
// // 		return data-6;
// // 	}
// 	
// 	// STOP condition
// 	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
// 	while (!(TWCR & (1 << TWINT)));
// 	_delay_ms(1);
// 	
// 	return data;
// }

void I2C_init(void)
{
	TWSR = 0x00;
	TWBR = 32;
	TWCR = (1 << TWEN);
}

uint8_t I2C_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return ( TWSR & TW_STATUS_MASK ) != TW_START;
}

uint8_t I2C_rep_start(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTA) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return ( TWSR & TW_STATUS_MASK ) != TW_REP_START;
}

void I2C_stop(void)
{
	TWCR = (1 << TWINT) | (1 << TWSTO) | (1 << TWEN);
	//while (TWCR & (1 << TWSTO));
}

uint8_t I2C_addr(uint8_t addr)
{
	TWDR = addr;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return ( TWSR & TW_STATUS_MASK ) != ( ( addr & 1 ) ? TW_MR_SLA_ACK : TW_MT_SLA_ACK );
}

uint8_t I2C_send(uint8_t data)
{
	TWDR = data;
	TWCR = (1 << TWINT) | (1 << TWEN);
	while (!(TWCR & (1 << TWINT)));
	return ( TWSR & TW_STATUS_MASK ) != TW_MT_DATA_ACK;
}

uint8_t I2C_read(uint8_t* data)	
{
	TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));
	*data = TWDR;
	return ( TWSR & TW_STATUS_MASK ) != TW_MR_DATA_ACK;
}

uint8_t BCD_DEC(uint8_t val)
{
	return ((val >> 4) * 10) + (val & 0x0F);
}

uint8_t DEC_BCD(uint8_t val)
{
    return ((val / 10) << 4) | (val % 10);
}

