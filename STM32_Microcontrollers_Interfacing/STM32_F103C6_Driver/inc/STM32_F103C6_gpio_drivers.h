/*
 * STM32_F103C6_gpio_drivers.h
 *
 *  Created on: Jul 21, 2024
 *      Author: 3m.B
 */

#ifndef INC_STM32_F103C6_GPIO_DRIVERS_H_
#define INC_STM32_F103C6_GPIO_DRIVERS_H_
#include <stm32f103x6.h>
typedef struct{
	uint16_t	GPIO__PinNumber;
	uint8_t		GPIO_MODE ;
	uint8_t		GPIO_SPEED ;


}GPIO_PinConfig_t;
//GPIO_PIN_NUMBER
//************************
#define GPIO__Pin0			((uint16_t)0x0001)
#define GPIO__Pin1			((uint16_t)0x0002)
#define GPIO__Pin2			((uint16_t)0x0004)
#define GPIO__Pin3			((uint16_t)0x0008)
#define GPIO__Pin4			((uint16_t)0x0010)
#define GPIO__Pin5			((uint16_t)0x0020)
#define GPIO__Pin6			((uint16_t)0x0040)
#define GPIO__Pin7			((uint16_t)0x0080)
#define GPIO__Pin8			((uint16_t)0x0100)
#define GPIO__Pin9			((uint16_t)0x0200)
#define GPIO__Pin10			((uint16_t)0x0400)
#define GPIO__Pin11			((uint16_t)0x0800)
#define GPIO__Pin12			((uint16_t)0x1000)
#define GPIO__Pin13			((uint16_t)0x2000)
#define GPIO__Pin14			((uint16_t)0x4000)
#define GPIO__Pin15			((uint16_t)0x8000)

#define GPIO__PinAll		((uint16_t)0xFFFF)
//******************************

//GPIO_PIN_STATE
#define GPIO_PIN_SET		1
#define GPIO_PIN_RESET		0

#define GPIO_Analog_mode								((uint8_t)0x00U)
#define GPIO_Floating_input								((uint8_t)0x01U)
#define GPIO_Input_with_pull_up 						((uint8_t)0x02U)
#define GPIO_Input_with_pull_down 						((uint8_t)0x03U)
#define GPIO_General_purpose_output_push_pull			((uint8_t)0x04U)
#define GPIO_General_purpose_output_Open_drain			((uint8_t)0x05U)
#define GPIO_Alternate_function_output_Push_pull		((uint8_t)0x06U)
#define GPIO_Alternate_function_output_Open_drain		((uint8_t)0x07U)
#define GPIO_Alternate_function_input					((uint8_t)0x08U)


#define GPIO_SPEED10		((uint8_t)0x01U)
#define GPIO_SPEED20		((uint8_t)0x02U)
#define GPIO_SPEED50		((uint8_t)0x03U)
#define GPIO_LOCK_OK 		1U
#define GPIO_LOCK_ERROR		0U

void MCAL_GPIO_INIT(GPIO_Typedef *GPIOX , GPIO_PinConfig_t *PinConfig);
void MCAL_GPIO_DEINIT(GPIO_Typedef *GPIOX );
uint8_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOX ,uint16_t PinNumber );
uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOX  );
void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOX ,uint16_t PinNumber  ,uint8_t value  );

void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOX ,uint16_t value  );

void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOX ,uint16_t PinNumber );

uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOX ,uint16_t PinNumber );




#endif /* INC_STM32_F103C6_GPIO_DRIVERS_H_ */
