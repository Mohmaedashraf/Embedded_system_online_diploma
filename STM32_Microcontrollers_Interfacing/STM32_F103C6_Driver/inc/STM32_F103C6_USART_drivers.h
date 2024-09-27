/*
 * STM32_F103C6_USART_drivers.h
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVERS_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVERS_H_
#include <STM32_F103C6_gpio_drivers.h>
#include <stm32f103x6.h>
#include "STM32_F103C6_RCC_drivers.h"
typedef struct {
	uint8_t USART_Mode ; //TX,RX
	//@ref USART_Mode_define


	uint32_t	BaudRate; // BaudRate speed of MCU
	//@ref BaudRate speed



	uint8_t	Parity;		// odd , even or non
	//@ref UART_Parity



	uint8_t  	PayloadLength; //UART data rate length
	//@ref UART_Length


	uint8_t		StopBite ; 		//STOP: STOP bits
	//	These bits are used for programming the stop bits.
	//	 1 Stop bit
	//	 0.5 Stop bit
	//	 2 Stop bits
	//	 1.5 Stop bit
	//	The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5.
	////@ref UART_Stopbit_define

	uint8_t   HFlowCtl ;		//specifies whether the hardware flow control enable or disable
	////@ref UART_HFlowCtl_define

	uint8_t  IRQ_Enable;		//enable or disable uart TX/RX
	////@ref UART_IRQ_Enable_define

	void ( * P_IRQ_CallBack)(void);

}UART_Config;

//@ref USART_Mode_define

#define USART_Mode_TX		(uint32_t)(1<<3)
#define USART_Mode_RX		(uint32_t)(1<<2)
#define USART_Mode_TX_RX	(uint32_t)(1<<2 | 1<<3)



//@ref BaudRate speed

#define UART_BaudRate_2400		2400
#define UART_BaudRate_9600		9600
#define UART_BaudRate_19200		19200
#define UART_BaudRate_57600		57600
#define UART_BaudRate_115200	115200
#define UART_BaudRate_230400	230400
#define UART_BaudRate_460800	460800
#define UART_BaudRate_921600	921600
#define UART_BaudRate_2250000	2250000
#define UART_BaudRate_4500000	4500000


//@ref UART_Parity
#define UART_Parity_NONE	(uint32_t)(0)
#define UART_Parity_even	(uint32_t)(1<<10)
#define UART_Parity_odd		(uint32_t)(1<<10 |1<<9)


//@ref UART_Length
#define UART_Payload_Length_8B		(uint32_t)(0)
#define UART_Payload_Length_9B		(uint32_t)(1<<12)

////@ref UART_Stopbit_define

#define UART_Stopbit_half			(uint32_t)(1<<12)
#define UART_Stopbit_1				(uint32_t)(0)
#define UART_Stopbit_1_half			(uint32_t)(3<<12)
#define UART_Stopbit_2				(uint32_t)(2<<12)

////@ref UART_HFlowCtl_define
#define UART_HFlowCtl_NONE			(uint32_t)(0)
#define UART_HFlowCtl_RTS			(uint32_t)(1<<8)
#define UART_HFlowCtl_CTS			(uint32_t)(1<<9)
#define UART_HFlowCtl_RTS_CTS		(uint32_t)(1<<8 | 1<<9)



////@ref UART_IRQ_Enable_define


#define UART_IRQ_Enable_NONE		(uint32_t)(0)
#define UART_IRQ_Enable_TXE			(uint32_t)(1<<7)
#define UART_IRQ_Enable_TC			(uint32_t)(1<<6)
#define UART_IRQ_Enable_RXNE		(uint32_t)(1<<5)
#define UART_IRQ_Enable_PE			(uint32_t)(1<<8)



#define USARTDIV(_PCLK_ , _BAUD_)				(uint32_t)(_PCLK_/(16*_BAUD_))
#define USARTDIV_MUL100(_PCLK_ , _BAUD_)		(uint32_t)((25*_PCLK_)/(4*_BAUD_))
#define Matissa_MUL100(_PCLK_ , _BAUD_)			(uint32_t)(USARTDIV(_PCLK_ , _BAUD_)*100)
#define Matissa(_PCLK_ , _BAUD_)				(uint32_t)(USARTDIV(_PCLK_ , _BAUD_))
#define DIV_Fraction(_PCLK_ , _BAUD_)			(uint32_t)(((USARTDIV_MUL100(_PCLK_ , _BAUD_)-Matissa_MUL100(_PCLK_ , _BAUD_))*16)/100)
#define UART_BRR_Register(_PCLK_ , _BAUD_)		(( Matissa(_PCLK_ , _BAUD_)<<4)|((DIV_Fraction(_PCLK_ , _BAUD_)) & 0xf))



typedef enum {

	enable,
	disable


}Polling_mechism;
void MCAL_UART_INIT(USART_Typedef *UARTX , UART_Config *UART_Config );
void MCAL_UART_DEINIT(USART_Typedef *UARTX  );
void MCAL_UART_GPIO_Set_Pins(USART_Typedef *UARTX  );
void MCAL_UART_SendData(USART_Typedef *UARTX ,uint16_t *PTXBuffer ,Polling_mechism pollingEn);
void MCAL_UART_ReceiveData(USART_Typedef *UARTX ,uint16_t *PTXBuffer ,Polling_mechism pollingEn);
void MCAL_UART_Wait_TC(USART_Typedef *UARTX );

#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_USART_DRIVERS_H_ */
