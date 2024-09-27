/*
 * I2C_Slave_EEPROM.c
 *
 *  Created on: Aug 27, 2024
 *      Author: 3m.B
 */
#include "I2C_Slave_EEPROM.h"

void eeprom_init(void)
{
	I2C_Config I2C1CFG;
	I2C1CFG.I2C_general_call=I2C_generalcall_enable;
	I2C1CFG.I2C_ACK=I2C_Ack;

	I2C1CFG.I2C_clk_Speed=I2C_SM_Speed_100K;
	I2C1CFG.I2C_Mode=I2C_mode;
	I2C1CFG.P_Slave_Event_CallBack=NULL;

	I2C1CFG.I2C_Strech_Mode=I2C_StretcMode_Enable;
	MCAL_I2C_gpio_Set_Pins(I2C1);
	MCAL_I2C_Init(I2C1, &I2C1CFG);
}
unsigned char eeprom_write_Nbytes(unsigned int Memory_Address , unsigned char *bytes , uint8_t data_length)
{
	uint8_t i = 0;
	uint8_t buffer[256];
	buffer[0]=(uint8_t)(Memory_Address>>8);
	buffer[1]=(uint8_t)Memory_Address;
	for(i=2 ; i<(data_length+2);i++)
		buffer[i]=bytes[i-2];
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_adress, buffer, (data_length+2), Stop, start);
	return 0;

}
unsigned char eeprom_read_byte(unsigned int address ,  uint8_t *bytes , uint8_t data_length)
{
	uint8_t buffer[2];
	buffer[0]=(uint8_t)(address>>8);
	buffer[1]=(uint8_t)address;
	MCAL_I2C_Master_TX(I2C1, EEPROM_Slave_adress, buffer, 2, without_stop, start);
	MCAL_I2C_Master_RX(I2C1, EEPROM_Slave_adress, bytes, data_length, Stop, repeated_start);
	return 0;
}


