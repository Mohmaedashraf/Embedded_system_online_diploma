/*
 * STM32_F103C6_EXTIO_drivers.h
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#ifndef STM32_F103C6_DRIVERS_INC_STM32_F103C6_EXTIO_DRIVERS_H_
#define STM32_F103C6_DRIVERS_INC_STM32_F103C6_EXTIO_DRIVERS_H_

// Include necessary headers
#include <STM32_F103C6_gpio_drivers.h>
#include <stm32f103x6.h>

// Structure to hold GPIO pin configuration for external interrupts
typedef struct {
	uint16_t ETI_InputLineNumber;	// Specifies the EXTI line number (e.g., EXTI0, EXTI1)
	GPIO_Typedef *GPIO_Port;         // Specifies the GPIO port for the EXTI line (e.g., GPIOA, GPIOB)
	uint16_t GPIO_PIN;               // Specifies the GPIO pin for the EXTI line (e.g., GPIO_PIN_0, GPIO_PIN_1)
	uint8_t IVT_IRQ_Numeber;         // Specifies the IRQ number for the EXTI line (e.g., EXTI0_IRQ)
} EXIT_GPIO_Mapping_t;

// Structure to configure EXTI (External Interrupt) pins
typedef struct {
	EXIT_GPIO_Mapping_t EXTI_PIN;	// Specifies the external interrupt mapping
									// This parameter must be set based on @ref EXIT_define
	uint8_t trigger;             	// Specifies the trigger (rising, falling, or both)
									// This parameter must be set based on @ref EXIT_Trigger_define
	uint8_t IRQ_EN;					// Enable or disable the EXTI IRQ
									// This parameter must be set based on @ref EXIT_IRQ_define
	void(* p_IRQ_CallBack)(void);	// Pointer to callback function for the IRQ handler
} EXIT_Pinconfg_t;

// Define macros for EXTI line numbers
#define EXTI0			0
#define EXTI1			1
#define EXTI2			2
#define EXTI3			3
#define EXTI4			4
#define EXTI5			5
#define EXTI6			6
#define EXTI7			7
#define EXTI8			8
#define EXTI9			9
#define EXTI10			10
#define EXTI11			11
#define EXTI12			12
#define EXTI13			13
#define EXTI14			14
#define EXTI15			15

// Define macros for IRQ numbers for EXTI lines
#define EXTI0_IRQ	6
#define EXTI1_IRQ	7
#define EXTI2_IRQ	8
#define EXTI3_IRQ	9
#define EXTI4_IRQ	10
#define EXTI5_IRQ	23
#define EXTI6_IRQ	23
#define EXTI7_IRQ	23
#define EXTI8_IRQ	23
#define EXTI9_IRQ	23
#define EXTI10_IRQ	40
#define EXTI11_IRQ	40
#define EXTI12_IRQ	40
#define EXTI13_IRQ	40
#define EXTI14_IRQ	40
#define EXTI15_IRQ	40
#define USART1_IRQ	37
#define USART2_IRQ	38
#define USART3_IRQ	39
#define SPI1_IRQ	35
#define SPI2_IRQ	36
#define I2C1_EV_IRQ	31
#define I2C1_ER_IRQ	32

#define I2C2_EV_IRQ	33
#define I2C2_ER_IRQ	34

// GPIO pin mapping for EXTI0 line
#define EXTI0PA0 		(EXIT_GPIO_Mapping_t){EXTI0,GPIOA,GPIO__Pin0,EXTI0_IRQ}
#define EXTI0PB0 		(EXIT_GPIO_Mapping_t){EXTI0,GPIOB,GPIO__Pin0,EXTI0_IRQ}
#define EXTI0PC0 		(EXIT_GPIO_Mapping_t){EXTI0,GPIOC,GPIO__Pin0,EXTI0_IRQ}
#define EXTI0PD0 		(EXIT_GPIO_Mapping_t){EXTI0,GPIOD,GPIO__Pin0,EXTI0_IRQ}

// GPIO pin mapping for EXTI1 line
#define EXTI1PA1      (EXIT_GPIO_Mapping_t){EXTI1, GPIOA, GPIO__Pin1, EXTI1_IRQ}
#define EXTI1PB1      (EXIT_GPIO_Mapping_t){EXTI1, GPIOB, GPIO__Pin1, EXTI1_IRQ}
#define EXTI1PC1      (EXIT_GPIO_Mapping_t){EXTI1, GPIOC, GPIO__Pin1, EXTI1_IRQ}
#define EXTI1PD1      (EXIT_GPIO_Mapping_t){EXTI1, GPIOD, GPIO__Pin1, EXTI1_IRQ}

// GPIO pin mapping for EXTI2 line
#define EXTI2PA2      (EXIT_GPIO_Mapping_t){EXTI2, GPIOA, GPIO__Pin2, EXTI2_IRQ}
#define EXTI2PB2      (EXIT_GPIO_Mapping_t){EXTI2, GPIOB, GPIO__Pin2, EXTI2_IRQ}
#define EXTI2PC2      (EXIT_GPIO_Mapping_t){EXTI2, GPIOC, GPIO__Pin2, EXTI2_IRQ}
#define EXTI2PD2      (EXIT_GPIO_Mapping_t){EXTI2, GPIOD, GPIO__Pin2, EXTI2_IRQ}

// GPIO pin mapping for EXTI3 line
#define EXTI3PA3      (EXIT_GPIO_Mapping_t){EXTI3, GPIOA, GPIO__Pin3, EXTI3_IRQ}
#define EXTI3PB3      (EXIT_GPIO_Mapping_t){EXTI3, GPIOB, GPIO__Pin3, EXTI3_IRQ}
#define EXTI3PC3      (EXIT_GPIO_Mapping_t){EXTI3, GPIOC, GPIO__Pin3, EXTI3_IRQ}
#define EXTI3PD3      (EXIT_GPIO_Mapping_t){EXTI3, GPIOD, GPIO__Pin3, EXTI3_IRQ}

// GPIO pin mapping for EXTI4 line
#define EXTI4PA4      (EXIT_GPIO_Mapping_t){EXTI4, GPIOA, GPIO__Pin4, EXTI4_IRQ}
#define EXTI4PB4      (EXIT_GPIO_Mapping_t){EXTI4, GPIOB, GPIO__Pin4, EXTI4_IRQ}
#define EXTI4PC4      (EXIT_GPIO_Mapping_t){EXTI4, GPIOC, GPIO__Pin4, EXTI4_IRQ}
#define EXTI4PD4      (EXIT_GPIO_Mapping_t){EXTI4, GPIOD, GPIO__Pin4, EXTI4_IRQ}

// GPIO pin mapping for EXTI5 line
#define EXTI5PA5      (EXIT_GPIO_Mapping_t){EXTI5, GPIOA, GPIO__Pin5, EXTI5_IRQ}
#define EXTI5PB5      (EXIT_GPIO_Mapping_t){EXTI5, GPIOB, GPIO__Pin5, EXTI5_IRQ}
#define EXTI5PC5      (EXIT_GPIO_Mapping_t){EXTI5, GPIOC, GPIO__Pin5, EXTI5_IRQ}
#define EXTI5PD5      (EXIT_GPIO_Mapping_t){EXTI5, GPIOD, GPIO__Pin5, EXTI5_IRQ}

// GPIO pin mapping for EXTI6 line
#define EXTI6PA6      (EXIT_GPIO_Mapping_t){EXTI6, GPIOA, GPIO__Pin6, EXTI6_IRQ}
#define EXTI6PB6      (EXIT_GPIO_Mapping_t){EXTI6, GPIOB, GPIO__Pin6, EXTI6_IRQ}
#define EXTI6PC6      (EXIT_GPIO_Mapping_t){EXTI6, GPIOC, GPIO__Pin6, EXTI6_IRQ}
#define EXTI6PD6      (EXIT_GPIO_Mapping_t){EXTI6, GPIOD, GPIO__Pin6, EXTI6_IRQ}

// GPIO pin mapping for EXTI7 line
#define EXTI7PA7      (EXIT_GPIO_Mapping_t){EXTI7, GPIOA, GPIO__Pin7, EXTI7_IRQ}
#define EXTI7PB7      (EXIT_GPIO_Mapping_t){EXTI7, GPIOB, GPIO__Pin7, EXTI7_IRQ}
#define EXTI7PC7      (EXIT_GPIO_Mapping_t){EXTI7, GPIOC, GPIO__Pin7, EXTI7_IRQ}
#define EXTI7PD7      (EXIT_GPIO_Mapping_t){EXTI7, GPIOD, GPIO__Pin7, EXTI7_IRQ}

// GPIO pin mapping for EXTI8 line
#define EXTI8PA8      (EXIT_GPIO_Mapping_t){EXTI8, GPIOA, GPIO__Pin8, EXTI8_IRQ}
#define EXTI8PB8      (EXIT_GPIO_Mapping_t){EXTI8, GPIOB, GPIO__Pin8, EXTI8_IRQ}
#define EXTI8PC8      (EXIT_GPIO_Mapping_t){EXTI8, GPIOC, GPIO__Pin8, EXTI8_IRQ}
#define EXTI8PD8      (EXIT_GPIO_Mapping_t){EXTI8, GPIOD, GPIO__Pin8, EXTI8_IRQ}

// GPIO pin mapping for EXTI9 line
#define EXTI9PA9      (EXIT_GPIO_Mapping_t){EXTI9, GPIOA, GPIO__Pin9, EXTI9_IRQ}
#define EXTI9PB9      (EXIT_GPIO_Mapping_t){EXTI9, GPIOB, GPIO__Pin9, EXTI9_IRQ}
#define EXTI9PC9      (EXIT_GPIO_Mapping_t){EXTI9, GPIOC, GPIO__Pin9, EXTI9_IRQ}
#define EXTI9PD9      (EXIT_GPIO_Mapping_t){EXTI9, GPIOD, GPIO__Pin9, EXTI9_IRQ}

// GPIO pin mapping for EXTI10 line
#define EXTI10PA10    (EXIT_GPIO_Mapping_t){EXTI10, GPIOA, GPIO__Pin10, EXTI10_IRQ}
#define EXTI10PB10    (EXIT_GPIO_Mapping_t){EXTI10, GPIOB, GPIO__Pin10, EXTI10_IRQ}
#define EXTI10PC10    (EXIT_GPIO_Mapping_t){EXTI10, GPIOC, GPIO__Pin10, EXTI10_IRQ}
#define EXTI10PD10    (EXIT_GPIO_Mapping_t){EXTI10, GPIOD, GPIO__Pin10, EXTI10_IRQ}

// GPIO pin mapping for EXTI11 line
#define EXTI11PA11    (EXIT_GPIO_Mapping_t){EXTI11, GPIOA, GPIO__Pin11, EXTI11_IRQ}
#define EXTI11PB11    (EXIT_GPIO_Mapping_t){EXTI11, GPIOB, GPIO__Pin11, EXTI11_IRQ}
#define EXTI11PC11    (EXIT_GPIO_Mapping_t){EXTI11, GPIOC, GPIO__Pin11, EXTI11_IRQ}
#define EXTI11PD11    (EXIT_GPIO_Mapping_t){EXTI11, GPIOD, GPIO__Pin11, EXTI11_IRQ}

// GPIO pin mapping for EXTI12 line
#define EXTI12PA12    (EXIT_GPIO_Mapping_t){EXTI12, GPIOA, GPIO__Pin12, EXTI12_IRQ}
#define EXTI12PB12    (EXIT_GPIO_Mapping_t){EXTI12, GPIOB, GPIO__Pin12, EXTI12_IRQ}
#define EXTI12PC12    (EXIT_GPIO_Mapping_t){EXTI12, GPIOC, GPIO__Pin12, EXTI12_IRQ}
#define EXTI12PD12    (EXIT_GPIO_Mapping_t){EXTI12, GPIOD, GPIO__Pin12, EXTI12_IRQ}

// GPIO pin mapping for EXTI13 line
#define EXTI13PA13    (EXIT_GPIO_Mapping_t){EXTI13, GPIOA, GPIO__Pin13, EXTI13_IRQ}
#define EXTI13PB13    (EXIT_GPIO_Mapping_t){EXTI13, GPIOB, GPIO__Pin13, EXTI13_IRQ}
#define EXTI13PC13    (EXIT_GPIO_Mapping_t){EXTI13, GPIOC, GPIO__Pin13, EXTI13_IRQ}
#define EXTI13PD13    (EXIT_GPIO_Mapping_t){EXTI13, GPIOD, GPIO__Pin13, EXTI13_IRQ}

// GPIO pin mapping for EXTI14 line
#define EXTI14PA14    (EXIT_GPIO_Mapping_t){EXTI14, GPIOA, GPIO__Pin14, EXTI14_IRQ}
#define EXTI14PB14    (EXIT_GPIO_Mapping_t){EXTI14, GPIOB, GPIO__Pin14, EXTI14_IRQ}
#define EXTI14PC14    (EXIT_GPIO_Mapping_t){EXTI14, GPIOC, GPIO__Pin14, EXTI14_IRQ}
#define EXTI14PD14    (EXIT_GPIO_Mapping_t){EXTI14, GPIOD, GPIO__Pin14, EXTI14_IRQ}

// GPIO pin mapping for EXTI15 line
#define EXTI15PA15    (EXIT_GPIO_Mapping_t){EXTI15, GPIOA, GPIO__Pin15, EXTI15_IRQ}
#define EXTI15PB15    (EXIT_GPIO_Mapping_t){EXTI15, GPIOB, GPIO__Pin15, EXTI15_IRQ}
#define EXTI15PC15    (EXIT_GPIO_Mapping_t){EXTI15, GPIOC, GPIO__Pin15, EXTI15_IRQ}
#define EXTI15PD15    (EXIT_GPIO_Mapping_t){EXTI15, GPIOD, GPIO__Pin15, EXTI15_IRQ}

// Define macros for EXTI trigger modes
//@ref EXIT_Trigger_define
#define EXIT_Trigger_Rising						0   // Trigger on rising edge
#define EXIT_Trigger_Falling					1   // Trigger on falling edge
#define EXIT_Trigger_RisingAndFalling			2   // Trigger on both edges

// Define macros for EXTI IRQ enable/disable
//@ref EXIT_IRQ_define
#define EXIT_IRQ_Enable					1   // Enable the EXTI IRQ
#define EXIT_IRQ_Disable				0   // Disable the EXTI IRQ

// Macros to enable NVIC interrupts for EXTI lines
#define NVIC_IRQ6_EXTI0_Enable   (NVIC_ISER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_Enable   (NVIC_ISER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_Enable   (NVIC_ISER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_Enable   (NVIC_ISER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_Enable  (NVIC_ISER0 |= 1 << 10)
#define NVIC_IRQ23_EXTIO5_9_Enable  (NVIC_ISER0 |= 1 << 23)
#define NVIC_IRQ40_EXTIO10_15_Enable  (NVIC_ISER1 |= 1 << 8) // (40 - 32 = 8)

// Macros to disable NVIC interrupts for EXTI lines
#define NVIC_IRQ6_EXTI0_Disable   (NVIC_ICER0 |= 1 << 6)
#define NVIC_IRQ7_EXTI1_Disable   (NVIC_ICER0 |= 1 << 7)
#define NVIC_IRQ8_EXTI2_Disable   (NVIC_ICER0 |= 1 << 8)
#define NVIC_IRQ9_EXTI3_Disable   (NVIC_ICER0 |= 1 << 9)
#define NVIC_IRQ10_EXTI4_Disable  (NVIC_ICER0 |= 1 << 10)
#define NVIC_IRQ23_EXTI5_9_Disable  (NVIC_ICER0 |= 1 << 23)
#define NVIC_IRQ40_EXTI10_15_Disable  (NVIC_ICER1 |= 1 << 8) // (40 - 32 = 8)

// Macros to enable NVIC interrupts for USART
#define NVIC_IRQ37_USART1_Enable  (NVIC_ISER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_Enable  (NVIC_ISER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_Enable  (NVIC_ISER1 |= 1<<(USART3_IRQ - 32))

// Macros to disable NVIC interrupts for USART
#define NVIC_IRQ37_USART1_Disable  (NVIC_ICER1 |= 1<<(USART1_IRQ - 32))
#define NVIC_IRQ38_USART2_Disable  (NVIC_ICER1 |= 1<<(USART2_IRQ - 32))
#define NVIC_IRQ39_USART3_Disable  (NVIC_ICER1 |= 1<<(USART3_IRQ - 32))

// Macros to enable NVIC interrupts for SPI
#define NVIC_IRQ35_SPI1_Enable  (NVIC_ISER1 |= 1<<(SPI1_IRQ - 32))
#define NVIC_IRQ36_SPI2_Enable  (NVIC_ISER1 |= 1<<(SPI2_IRQ - 32))

// Macros to disable NVIC interrupts for SPI
#define NVIC_IRQ35_SPI1_Disable  (NVIC_ICER1 |= 1<<(SPI1_IRQ - 32))
#define NVIC_IRQ36_SPI2_Disable  (NVIC_ICER1 |= 1<<(SPI2_IRQ - 32))

// Macros to enable NVIC interrupts for I2C


#define NVIC_IRQ31_I2C1_EV_Enable()			(NVIC_ISER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_Enable()			(NVIC_ISER1 |= 1<<(I2C1_ER_IRQ - 32))
#define NVIC_IRQ33_I2C2_EV_Enable()			(NVIC_ISER1 |= 1<<(I2C2_EV_IRQ - 32))
#define NVIC_IRQ34_I2C2_ER_Enable()			(NVIC_ISER1 |= 1<<(I2C2_ER_IRQ - 32))

// Macros to disable NVIC interrupts for I2C


#define NVIC_IRQ31_I2C1_EV_Disable()		(NVIC_ICER0 |= 1<<(I2C1_EV_IRQ))
#define NVIC_IRQ32_I2C1_ER_Disable()		(NVIC_ICER1 |= 1<<(I2C1_ER_IRQ - 32))
#define NVIC_IRQ33_I2C2_EV_Disable()		(NVIC_ICER1 |= 1<<(I2C2_EV_IRQ - 32))
#define NVIC_IRQ34_I2C2_ER_Disable()		(NVIC_ICER1 |= 1<<(I2C2_ER_IRQ - 32))


// Function prototypes for initializing, deinitializing, and updating EXTI
void MCAL_EXTI_GPIO_Init(EXIT_Pinconfg_t *EXIT_confg);  // Initialize EXTI
void MCAL_EXTI_GPIO_Deinit(void);                      // Deinitialize EXTI
void MCAL_EXTI_GPIO_Update(EXIT_Pinconfg_t *EXIT_confg); // Update EXTI configuration

#endif /* STM32_F103C6_DRIVERS_INC_STM32_F103C6_EXTIO_DRIVERS_H_ */
