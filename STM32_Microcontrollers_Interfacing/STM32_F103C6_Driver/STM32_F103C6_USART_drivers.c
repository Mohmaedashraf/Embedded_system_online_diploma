/*
 * STM32_F103C6_RCC_drivers.c
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#include "STM32_F103C6_USART_drivers.h"
#include "STM32_F103C6_EXTIO_drivers.h"
#include "STM32_F103C6_RCC_drivers.h"
UART_Config *Global_UART_Config = NULL;
void MCAL_UART_INIT(USART_Typedef *UARTX , UART_Config *UART_Config ){

	uint32_t pclk , BRR;
	Global_UART_Config=UART_Config;
	if(UARTX==USART1){
		RCC_USART1_CLK_EN();
	}else if(UARTX==USART2){
		RCC_USART2_CLK_EN();
	}else{
		RCC_USART3_CLK_EN();

	}
	UARTX->CR1 |=1<<13;
	UARTX->CR1 |= UART_Config->USART_Mode;
	UARTX->CR1 |= UART_Config->PayloadLength;
	UARTX->CR1 |= UART_Config->Parity;
	UARTX->CR2 |= UART_Config->StopBite;
	UARTX->CR3 |= UART_Config->HFlowCtl;
	if (UARTX==USART1)
		pclk=MCAL_RCC_GetPCLK2Freq();
	else
		pclk=MCAL_RCC_GetPCLK1Freq();

	BRR=UART_BRR_Register(pclk,UART_Config->BaudRate);
	UARTX->BRR = BRR;
	if(UART_Config->IRQ_Enable != UART_IRQ_Enable_NONE){
		UARTX->CR1 |= UART_Config->IRQ_Enable;
		if(UARTX==USART1)
			NVIC_IRQ37_USART1_Enable ;
		else if(UARTX==USART2)
			NVIC_IRQ38_USART2_Enable;
		else
			NVIC_IRQ39_USART3_Enable;
	}
}

void MCAL_UART_DEINIT(USART_Typedef *UARTX){
	if(UARTX == USART1){
		NVIC_IRQ37_USART1_Disable;
		RCC_USART1_Reset();
	}
	else if(UARTX == USART2){
		NVIC_IRQ38_USART2_Disable;
		RCC_USART2_Reset();
	}
	else{
		NVIC_IRQ39_USART3_Disable;
		RCC_USART3_Reset();
	}
}

void MCAL_UART_SendData(USART_Typedef *UARTX ,uint16_t *PTXBuffer ,Polling_mechism pollingEn){

	if(pollingEn==enable)
		while(!(UARTX->SR &(1<<7)));
	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
	//	because it is replaced by the parity.
	//	When receiving with the parity enabled, the value read in the MSB bit is the received parity
	//	bit.

	if(Global_UART_Config->PayloadLength==UART_Payload_Length_9B)
		UARTX->DR=(*PTXBuffer & (uint16_t)0x01ff);
	else
		UARTX->DR=(*PTXBuffer & (uint16_t)0xff);




}

void MCAL_UART_Wait_TC(USART_Typedef *UARTX ){

	while(!(UARTX->SR &(1<<6)));


}


void MCAL_UART_ReceiveData(USART_Typedef *UARTX, uint16_t *PTXBuffer, Polling_mechism pollingEn) {
	// Polling mechanism to wait until RXNE (Read Data Register Not Empty) is set
	if (pollingEn == enable) {
		while (!(UARTX->SR & (1 << 5))); // Wait until RXNE flag is set
	}

	// Check the payload length configured globally
	if (Global_UART_Config->PayloadLength == UART_Payload_Length_9B) {
		// If no parity is configured
		if (Global_UART_Config->Parity == UART_Parity_NONE) {
			*((uint16_t *)PTXBuffer) = (UARTX->DR); // Read the entire DR register
		} else {
			*((uint16_t *)PTXBuffer) = (UARTX->DR & (uint8_t)0xFF); // Mask the data
		}
	} else {
		// For payload length 8 bits
		if (Global_UART_Config->Parity == UART_Parity_NONE) {
			*((uint16_t *)PTXBuffer) = (UARTX->DR & (uint8_t)0xFF); // Read 8 bits of data
		} else {
			*((uint16_t *)PTXBuffer) = (UARTX->DR & (uint8_t)0x7F); // Read 7 bits of data
		}
	}
}

void MCAL_UART_GPIO_Set_Pins(USART_Typedef *UARTX  ){
	GPIO_PinConfig_t PinCfg;

	if(UARTX == USART1){
		// PA9 TX
		// PA10 RX
		// PA11 CTS
		// PA12 RTS
		PinCfg.GPIO__PinNumber = GPIO__Pin9;

		PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
		PinCfg.GPIO_SPEED = GPIO_SPEED10;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);
		PinCfg.GPIO__PinNumber = GPIO__Pin10;

		PinCfg.GPIO_MODE = GPIO_Floating_input;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_CTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO__PinNumber = GPIO__Pin11;

			PinCfg.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO__PinNumber = GPIO__Pin12;

			PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			PinCfg.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}

	else if(UARTX == USART2){
		// PA2 TX
		// PA3 RX
		// PA0 CTS
		// PA1 RTS
		PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
		PinCfg.GPIO__PinNumber = GPIO__Pin2;
		PinCfg.GPIO_SPEED = GPIO_SPEED10;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		PinCfg.GPIO_MODE = GPIO_Floating_input;
		PinCfg.GPIO__PinNumber = GPIO__Pin3;
		MCAL_GPIO_INIT(GPIOA, &PinCfg);

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_CTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO_MODE = GPIO_Floating_input;
			PinCfg.GPIO__PinNumber = GPIO__Pin0;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			PinCfg.GPIO__PinNumber = GPIO__Pin1;
			PinCfg.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOA, &PinCfg);
		}
	}

	else if(UARTX == USART3){
		// PB10 TX
		// PB11 RX
		// PB13 CTS
		// PB14 RTS
		PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
		PinCfg.GPIO__PinNumber = GPIO__Pin10;
		PinCfg.GPIO_SPEED = GPIO_SPEED10;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		PinCfg.GPIO_MODE = GPIO_Floating_input;
		PinCfg.GPIO__PinNumber = GPIO__Pin11;
		MCAL_GPIO_INIT(GPIOB, &PinCfg);

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_CTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO_MODE = GPIO_Floating_input;
			PinCfg.GPIO__PinNumber = GPIO__Pin13;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}

		if(Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS || Global_UART_Config->HFlowCtl == UART_HFlowCtl_RTS_CTS){
			PinCfg.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			PinCfg.GPIO__PinNumber = GPIO__Pin14;
			PinCfg.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOB, &PinCfg);
		}
	}
}


void USART1_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();
}
void USART2_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();


}

void USART3_IRQHandler(void){

	Global_UART_Config->P_IRQ_CallBack();


}
