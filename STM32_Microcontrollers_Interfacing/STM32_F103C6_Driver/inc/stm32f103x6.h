/*
 * stm32f103x6.h
 *
 *  Created on: Jul 21, 2024
 *      Author: 3m.B
 */

#ifndef INC_STM32F103X6_H_
#define INC_STM32F103X6_H_

//-----------------------------
// Includes
//-----------------------------
#include <stdio.h>
#include <stdint.h>

//-----------------------------
// Base addresses for Memories
//-----------------------------

// Base address for Flash memory
#define FLASH_MEMORY_BASE				0x08000000UL

// Base address for System memory (usually used for bootloader)
#define SYSTEM_MEMORY_BASE				0x1FFFF000UL

// Base address for SRAM (Static RAM) memory
#define SRAM_MEMORY_BASE				0x20000000UL

// Base address for peripherals (APB1, APB2, AHB peripherals)
#define Peripherals_BASE				0x40000000UL

// Base address for Cortex-M3 internal peripherals (like SysTick, NVIC, etc.)
#define Cortex_M3_Internal_Peripherals	0xE0000000UL

// Base address for NVIC (Nested Vectored Interrupt Controller) register block
#define NVIC_BASR						(0xE000E100UL)

// Base address for SPI1 peripheral
#define SPI1_BASE						0x40013000UL

// Base address for SPI2 peripheral
#define SPI2_BASE						0x40003800UL
// Base address for I2C1 peripheral
#define I2C1_BASE						0x40005400UL
// Base address for I2C2 peripheral
#define I2C2_BASE						0x40005800UL

//-----------------------------
// NVIC (Interrupt Controller) Registers
//-----------------------------

// Interrupt Set Enable Registers
#define NVIC_ISER0						*(volatile uint32_t *)(NVIC_BASR+0x0)
#define NVIC_ISER1						*(volatile uint32_t *)(NVIC_BASR+0x4)
#define NVIC_ISER2						*(volatile uint32_t *)(NVIC_BASR+0x8)

// Interrupt Clear Enable Registers
#define NVIC_ICER0						*(volatile uint32_t *)(NVIC_BASR+0x80)
#define NVIC_ICER1						*(volatile uint32_t *)(NVIC_BASR+0x84)
#define NVIC_ICER2						*(volatile uint32_t *)(NVIC_BASR+0x88)

//-----------------------------
// Base addresses for APB1 Peripherals
//-----------------------------

// Base address for USART1 peripheral (APB2)
#define USART1_BASE   						0x40013800UL

// Base address for USART2 peripheral (APB1)
#define USART2_BASE   						0x40004400UL

// Base address for USART3 peripheral (APB1)
#define USART3_BASE   						0x40004800UL

//-----------------------------
// Base addresses for AHB Peripherals
//-----------------------------

// Base address for RCC (Reset and Clock Control) peripheral
#define RCC_BASE							0x40021000UL

//-----------------------------
// Base addresses for APB2 Peripherals
//-----------------------------

// Base address for GPIOA peripheral (APB2)
#define GPIOA_BASE								0x40010800UL

// Base address for GPIOB peripheral (APB2)
#define GPIOB_BASE								0x40010C00UL

// Base address for GPIOC peripheral (APB2)
#define GPIOC_BASE								0x40011000UL

// Base address for GPIOD peripheral (APB2)
#define GPIOD_BASE								0x40011400UL

// Base address for GPIOE peripheral (APB2)
#define GPIOE_BASE								0x40011800UL

// Base address for EXTI (External Interrupt/Event Controller) peripheral (APB2)
#define EXTIO_BASE								0x40010400UL

// Base address for AFIO (Alternate Function I/O) peripheral (APB2)
#define AFIO_BASE								0x40010000UL

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register definitions
//-*-*-*-*-*-*-*-*-*-*-*

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: GPIO
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for GPIO registers
typedef struct {
	volatile uint32_t CRL;    // GPIO port configuration register low (for pins 0-7)
	volatile uint32_t CRH;    // GPIO port configuration register high (for pins 8-15)
	volatile uint32_t IDR;    // GPIO port input data register
	volatile uint32_t ODR;    // GPIO port output data register
	volatile uint32_t BSRR;   // GPIO port bit set/reset register
	volatile uint32_t BRR;    // GPIO port bit reset register
	volatile uint32_t LCKR;   // GPIO port configuration lock register
} GPIO_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: RCC
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for RCC registers
typedef struct {
	volatile uint32_t CR;        // Clock control register
	volatile uint32_t CFGR;      // Clock configuration register
	volatile uint32_t CIR;       // Clock interrupt register
	volatile uint32_t APB2RSTR;  // APB2 peripheral reset register
	volatile uint32_t APB1RSTR;  // APB1 peripheral reset register
	volatile uint32_t AHBENR;    // AHB peripheral clock enable register
	volatile uint32_t APB2ENR;   // APB2 peripheral clock enable register
	volatile uint32_t APB1ENR;   // APB1 peripheral clock enable register
	volatile uint32_t BDCR;      // Backup domain control register
	volatile uint32_t CSR;       // Control/status register
	volatile uint32_t AHBSTR;    // AHB peripheral reset register
	volatile uint32_t CFGR2;     // Clock configuration register 2
} RCC_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: EXTI
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for EXTI registers
typedef struct {
	volatile uint32_t IMR;    // Interrupt mask register
	volatile uint32_t EMR;    // Event mask register
	volatile uint32_t RTSR;   // Rising trigger selection register
	volatile uint32_t FTSR;   // Falling trigger selection register
	volatile uint32_t SWIER;  // Software interrupt event register
	volatile uint32_t PR;     // Pending register
} EXTI_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: AFIO
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for AFIO registers
typedef struct {
	volatile uint32_t EVCR;      // Event control register
	volatile uint32_t MAPR;      // Remap and debug I/O configuration register
	volatile uint32_t EXTICR[4]; // External interrupt configuration registers
	uint32_t		  reserver;  // Reserved memory space
	volatile uint32_t MAPR2;     // Remap and debug I/O configuration register 2
} AFIO_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: USART
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for USART registers
typedef struct {
	volatile uint32_t SR;    // Status register
	volatile uint32_t DR;    // Data register
	volatile uint32_t BRR;   // Baud rate register
	volatile uint32_t CR1;   // Control register 1
	volatile uint32_t CR2;   // Control register 2
	volatile uint32_t CR3;   // Control register 3
	volatile uint32_t GTPR;  // Guard time and prescaler register
} USART_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for SPI registers
typedef struct {
	volatile uint32_t CR1;     // Control register 1
	volatile uint32_t CR2;     // Control register 2
	volatile uint32_t SR;      // Status register
	volatile uint32_t DR;      // Data register
	volatile uint32_t CRCPR;   // CRC polynomial register
	volatile uint32_t RXCRCR;  // RX CRC register
	volatile uint32_t TXCRCR;  // TX CRC register
	volatile uint32_t I2SCFGR; // I2S configuration register
	volatile uint32_t I2SPR;   // I2S prescaler register
} SPI_Typedef;


//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral register: SPI
//-*-*-*-*-*-*-*-*-*-*-*

// Structure definition for SPI registers
typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t OAR1;
	volatile uint32_t OAR2;
	volatile uint32_t DR;
	volatile uint32_t SR1;
	volatile uint32_t SR2;
	volatile uint32_t CCR;
	volatile uint32_t TRISE;
} I2C_Typedef;

//-*-*-*-*-*-*-*-*-*-*-*-
// Peripheral Instances (typecasting base addresses to the corresponding register structures)
//-*-*-*-*-*-*-*-*-*-*-*

// GPIO Peripheral Instances
#define GPIOA				((GPIO_Typedef *)GPIOA_BASE)
#define GPIOB				((GPIO_Typedef *)GPIOB_BASE)
#define GPIOC				((GPIO_Typedef *)GPIOC_BASE)
#define GPIOD				((GPIO_Typedef *)GPIOD_BASE)
#define GPIOE				((GPIO_Typedef *)GPIOE_BASE)

// RCC Peripheral Instance
#define RCC					((RCC_Typedef *)RCC_BASE)

// EXTI Peripheral Instance
#define EXTIO				((EXTI_Typedef *)EXTIO_BASE)

// AFIO Peripheral Instance
#define AFIO				((AFIO_Typedef *)AFIO_BASE)

// SPI Peripheral Instances
#define SPI1				((SPI_Typedef *)SPI1_BASE)
#define SPI2					((SPI_Typedef *)SPI2_BASE)

// USART Peripheral Instances
#define USART1				((USART_Typedef *)USART1_BASE)
#define USART2				((USART_Typedef *)USART2_BASE)
#define USART3				((USART_Typedef *)USART3_BASE)

// I2C Peripheral Instances
#define I2C1				((I2C_Typedef *)I2C1_BASE)
#define I2C2				((I2C_Typedef *)I2C2_BASE)


//-*-*-*-*-*-*-*-*-*-*-*-
// Clock enable Macros
//-*-*-*-*-*-*-*-*-*-*-*

// Enable clock for GPIOA
#define RCC_GPIOA_CLK_EN()			(RCC->APB2ENR |= 1<<2)

// Enable clock for GPIOB
#define RCC_GPIOB_CLK_EN()			(RCC->APB2ENR |= 1<<3)

// Enable clock for GPIOC
#define RCC_GPIOC_CLK_EN()			(RCC->APB2ENR |= 1<<4)

// Enable clock for GPIOD
#define RCC_GPIOD_CLK_EN()			(RCC->APB2ENR |= 1<<5)

// Enable clock for GPIOE
#define RCC_GPIOE_CLK_EN()			(RCC->APB2ENR |= 1<<6)

// Enable clock for AFIO
#define RCC_AFIO_CLK_EN()			(RCC->APB2ENR |= 1<<0)

// Enable clock for USART1
#define RCC_USART1_CLK_EN()			(RCC->APB2ENR |= 1<<14)

// Enable clock for USART2
#define RCC_USART2_CLK_EN()			(RCC->APB1ENR |= 1<<17)

// Enable clock for USART3
#define RCC_USART3_CLK_EN()			(RCC->APB1ENR |= 1<<18)

// Enable clock for SPI1
#define RCC_SPI1_CLK_EN()			(RCC->APB2ENR |= 1<<12)

// Enable clock for SPI2
#define RCC_SPI2_CLK_EN()			(RCC->APB1ENR |= 1<<14)

// Enable clock for I2C1
#define RCC_I2C1_CLK_EN()			(RCC->APB1ENR |= 1<<21)
// Enable clock for I2C1
#define RCC_I2C2_CLK_EN()			(RCC->APB1ENR |= 1<<22)



//-*-*-*-*-*-*-*-*-*-*-*-
// Reset Macros
//-*-*-*-*-*-*-*-*-*-*-*

// Reset USART1 peripheral
#define RCC_USART1_Reset()			(RCC->APB2RSTR |= 1<<14)

// Reset USART2 peripheral
#define RCC_USART2_Reset()			(RCC->APB1RSTR |= 1<<17)

// Reset USART3 peripheral
#define RCC_USART3_Reset()			(RCC->APB1RSTR |= 1<<18)

// Reset SPI2 peripheral
#define RCC_SPI2_Reset()			(RCC->APB1RSTR |= 1<<14)

// Reset SPI1 peripheral
#define RCC_SPI1_Reset()			(RCC->APB2RSTR |= 1<<12)


// Reset I2C1 peripheral
#define RCC_I2C1_Reset()			(RCC->APB1RSTR |= 1<<21)

// Reset I2C2 peripheral
#define RCC_I2C2_Reset()			(RCC->APB1RSTR |= 1<<22)


//-*-*-*-*-*-*-*-*-*-*-*-
// Generic Macros (for other configurations)
//-*-*-*-*-*-*-*-*-*-*-*

#endif /* INC_STM32F103X6_H_ */
