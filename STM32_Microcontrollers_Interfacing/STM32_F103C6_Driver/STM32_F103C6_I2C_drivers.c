/*
 * STM32_F103C6_I2C_drivers.c
 *
 *  Created on: Aug 22, 2024
 *      Author: 3m.B
 */

#include "STM32_F103C6_I2C_drivers.h"
#include "STM32_F103C6_EXTIO_drivers.h"
#include "STM32_F103C6_RCC_drivers.h"
#include "STM32_F103C6_RCC_drivers.h"
I2C_Config	I2C_config[2] ;

#define I2C1_Index		0
#define I2C2_Index		1


void MCAL_I2C_Init(I2C_Typedef *I2CX , I2C_Config *I2C_conf)
{
    uint16_t  tempreg =0 ;
    uint16_t freq ;
    uint32_t pclk = 8000000 ;
    uint16_t resalt = 0;
    if (I2CX==I2C1)
    {
        RCC_I2C1_CLK_EN();
        I2C_config[I2C1_Index]= *I2C_conf;
    }else if (I2CX == I2C2)
    {
        RCC_I2C2_CLK_EN();
        I2C_config[I2C2_Index]= *I2C_conf;
    }
    if(I2C_conf->I2C_Mode==I2C_mode)
    {
        tempreg = I2CX->CR2 ;
        tempreg &=~(I2C_CR2_FREQ);
        pclk=MCAL_RCC_GetPCLK1Freq();
        freq= (uint16_t)(pclk / 1000000) ;
        tempreg |= freq ;
        I2CX->CR2=tempreg ;
        I2CX->CR1 &=~(I2C_CR1_PE);
        tempreg = 0;
        if(I2C_conf->I2C_clk_Speed == I2C_SM_Speed_50K || I2C_conf->I2C_clk_Speed == I2C_SM_Speed_100K)
        {
            // Calculate the CCR value
            resalt = (uint16_t)((pclk) / (I2C_conf->I2C_clk_Speed * 2));
            tempreg |= resalt;  // Assign the CCR value
            I2CX->CCR = tempreg;  // Set the CCR register
            I2CX->TRISE = freq + 1;  // Set the TRISE register
        }else
        {
            // Not supported yet
        }

        tempreg = I2CX->CR1;
        tempreg |=((I2C_conf->I2C_ACK)|(I2C_conf->I2C_Strech_Mode)|(I2C_conf->I2C_general_call)|(I2C_conf->I2C_Mode));
        I2CX->CR1=tempreg;
        tempreg = 0;
        if(I2C_conf->I2C_Slave_Address_Mode.Enable_DUAL_Address==1)
        {
            tempreg = I2C_OAR2_ENDUAL;
            tempreg |= (I2C_conf->I2C_Slave_Address_Mode.Secondary_Slave_Address <<I2C_OAR2_ADD2_Pos);
            I2CX->OAR2 = tempreg ;
        }
        tempreg = 0;
        tempreg |= (I2C_conf->I2C_Slave_Address_Mode.Primary_Slave_Address <<1);
        tempreg |= (I2C_conf->I2C_Slave_Address_Mode.I2C_Addressing_Slave_Mode);
        I2CX->OAR1 = tempreg;

    }else
    {
        // Not supported yet
    }

    if(I2C_conf->P_Slave_Event_CallBack != NULL)
    {
        I2CX->CR2 |=(I2C_CR2_ITERREN);
        I2CX->CR2 |=(I2C_CR2_ITEVTEN);
        I2CX->CR2 |=(I2C_CR2_ITBUFEN);
        if(I2CX == I2C1)
        {
            NVIC_IRQ31_I2C1_EV_Enable();
            NVIC_IRQ32_I2C1_ER_Disable();
        }else
        {
            NVIC_IRQ33_I2C2_EV_Enable();
            NVIC_IRQ34_I2C2_ER_Enable();

        }
        I2CX->SR1 = 0 ;
        I2CX->SR2 = 0 ;

    }

    I2CX->CR1 = I2C_CR1_PE;
}
void MCAL_I2C_gpio_Set_Pins(I2C_Typedef *I2CX)
{		GPIO_PinConfig_t I2CConfg;

if(I2CX == I2C1)
{
	I2CConfg.GPIO__PinNumber=GPIO__Pin6;
	I2CConfg.GPIO_MODE= GPIO_Alternate_function_output_Open_drain;
	I2CConfg.GPIO_SPEED=GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &I2CConfg);
	I2CConfg.GPIO__PinNumber=GPIO__Pin7;
	I2CConfg.GPIO_MODE= GPIO_Alternate_function_output_Open_drain;
	I2CConfg.GPIO_SPEED=GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &I2CConfg);
}else
{
	I2CConfg.GPIO__PinNumber=GPIO__Pin10;
	I2CConfg.GPIO_MODE= GPIO_Alternate_function_output_Open_drain;
	I2CConfg.GPIO_SPEED=GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &I2CConfg);
	I2CConfg.GPIO__PinNumber=GPIO__Pin11;
	I2CConfg.GPIO_MODE= GPIO_Alternate_function_output_Open_drain;
	I2CConfg.GPIO_SPEED=GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &I2CConfg);
}


}

void MCAL_I2C_Master_TX(I2C_Typedef *I2CX ,uint16_t defAddr , uint8_t* dataout ,uint32_t datalen ,E_STOP_CONDITION stop , E_START_CONDITION Start  )
{
	volatile uint32_t i;

	I2C_GenerateStart(I2CX , Enab , start);
	while(!I2C_Get_StatusFlag(I2CX, EV5));
	I2C_Send_Addrss(I2CX , defAddr , I2C_Dirction_Transimiter);
	while(!I2C_Get_StatusFlag(I2CX, EV6));
	while(!I2C_Get_StatusFlag(I2CX, MASTER_EVENT_BYTE_TRNSDIMETING));
	for(i=0;i<datalen ;i++){
		I2CX->DR=dataout[i];
		while(!I2C_Get_StatusFlag(I2CX, EV8));
	}
	if(stop == Stop)
		I2C_GenerateStop(I2CX , Enab);

}
void MCAL_I2C_Master_RX(I2C_Typedef *I2CX ,uint16_t defAddr , uint8_t* dataout ,uint32_t datalen ,E_STOP_CONDITION stop , E_START_CONDITION Start  )
{
	volatile uint32_t i;

	I2C_GenerateStart(I2CX , Enab , Start);
	while(!I2C_Get_StatusFlag(I2CX, EV5));
	I2C_Send_Addrss(I2CX , defAddr , I2C_Dirction_Receiver);
	while(!I2C_Get_StatusFlag(I2CX, EV6));
	I2C_AckConfig(I2CX, Enab);
	if(datalen)
	{
		for(i=datalen ; i>1 ; i--)
		{
			while(!I2C_Get_StatusFlag(I2CX, EV7));
			*dataout=I2CX->DR;
			dataout++;
		}
		I2C_AckConfig(I2CX, Disab);
	}if(stop==Stop)
		I2C_GenerateStop(I2CX, Enab);
	if(I2CX==I2C1)
	{
		if(I2C_config[0].I2C_ACK==I2C_Ack)
			I2C_AckConfig(I2CX, Enab);

	}else
	{
		if(I2C_config[1].I2C_ACK==I2C_Ack)
			I2C_AckConfig(I2CX, Enab);

	}

}
void MCAL_I2C_SLAVE_TX (I2C_Typedef* I2Cx, uint8_t Data)
{
	I2Cx->DR = Data;

}
uint8_t MCAL_I2C_SLAVE_RX (I2C_Typedef* I2Cx)
{
	return (uint8_t) I2Cx->DR ;

}

void I2C_GenerateStart(I2C_Typedef *I2CX , FunctinalState NewState , E_START_CONDITION Start)
{
	if(Start == start)
		while(I2C_Get_StatusFlag(I2CX, I2C_Flag_Busy));
	if( NewState != Disab)
		I2CX->CR1 |=I2C_CR1_START;
	else
		I2CX->CR1 &=~(I2C_CR1_START);

}
FlagStatus I2C_Get_StatusFlag(I2C_Typedef* I2CX , Status flag)
{
	Status BitStatus =reset;
	volatile uint32_t Temp=0 , flag1=0 , flag2 = 0 ,lastevent =0;
	switch(flag)
	{
	case I2C_Flag_Busy:
		if((I2CX->SR2) & (I2C_SR2_BUSY))
			BitStatus = set;
		else
			BitStatus=reset;
		break ;
	case EV5:
		if(I2CX->SR1 & I2C_SR1_SB)
			BitStatus = set;
		else
			BitStatus=reset;
		break ;

	case EV6 :
		if(I2CX->SR1 &I2C_SR1_ADDR)
			BitStatus = set;
		else
			BitStatus=reset;

		break ;
	case MASTER_EVENT_BYTE_TRNSDIMETING:
		flag1=I2CX->SR1;
		flag2=I2CX->SR2;
		flag2=(flag2<<16);
		lastevent = (flag1 | flag2) & ((uint32_t) 0x00FFFFFF);
		if((lastevent &flag)==flag)
			BitStatus = set;
		else
			BitStatus=reset;
		break ;
	case EV8_1:
	case EV8:
		if(I2CX->SR1&I2C_SR1_TXE)
			BitStatus = set;
		else
			BitStatus=reset;
		break ;
	case EV7:
		if(I2CX->SR1 &I2C_SR1_RXNE)
			BitStatus = set;
		else
			BitStatus=reset;
		break ;
	}

	return BitStatus;
}
void I2C_Send_Addrss(I2C_Typedef *I2CX , uint16_t address , I2C_Dirction Dirction)
{
	address=(address<<1);
	if(Dirction !=I2C_Dirction_Transimiter)
		address |=(1<<0);
	else
		address &=~(1<<0);
	I2CX->DR=address;
}
void I2C_GenerateStop(I2C_Typedef *I2CX , FunctinalState NewState )
{
	if(NewState !=Disab)
		I2CX->CR1 |=I2C_CR1_STOP;
	else
		I2CX->CR1 &=~(I2C_CR1_STOP);

}
void I2C_AckConfig (I2C_Typedef* I2CX, FunctinalState NewState)
{
	if(NewState ==Enab)
		I2CX->CR1 |=I2C_CR1_ACK;
	else
		I2CX->CR1 &=~(I2C_CR1_ACK);


}



