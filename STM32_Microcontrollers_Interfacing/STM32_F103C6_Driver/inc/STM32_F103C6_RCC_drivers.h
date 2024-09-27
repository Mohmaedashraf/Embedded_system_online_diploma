/*
 * STM32_F103C6_RCC_drivers.h
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVERS_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVERS_H_
#include <STM32_F103C6_gpio_drivers.h>
#include <stm32f103x6.h>
#define HSI_RC_CLK 			(uint32_t)8000000
#define HSE_CLOCK			(uint32_t)16000000
uint32_t MCAL_RCC_GetSYS_PCLKFreq(void);
uint32_t MCAL_RCC_GetHPCLKFreq(void);

uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);




#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_RCC_DRIVERS_H_ */
