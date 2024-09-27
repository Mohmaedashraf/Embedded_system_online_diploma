/*
 * I2C_Slave_EEPROM.h
 *
 *  Created on: Aug 27, 2024
 *      Author: 3m.B
 */

#ifndef INCLUDES_I2C_SLAVE_EEPROM_H_
#define INCLUDES_I2C_SLAVE_EEPROM_H_
#include "STM32_F103C6_I2C_drivers.h"
#define EEPROM_Slave_adress		0x2A

void eeprom_init(void);
unsigned char eeprom_write_Nbytes(unsigned int Memory_Address , unsigned char *bytes , uint8_t data_length) ;
unsigned char eeprom_read_byte(unsigned int address ,  uint8_t *bytes , uint8_t data_length) ;


#endif /* INCLUDES_I2C_SLAVE_EEPROM_H_ */
