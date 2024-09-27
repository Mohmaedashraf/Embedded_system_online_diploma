/*
 * STM32_F103C6_SPI_drivers.h
 *
 *  Created on: Aug 16, 2024
 *      Author: 3m.B
 */

#ifndef INC_STM32_F103C6_SPI_DRIVERS_H_
#define INC_STM32_F103C6_SPI_DRIVERS_H_

// Include the main STM32F103C6 header file for memory and peripheral definitions
#include "stm32f103x6.h"

// Include the GPIO driver header for controlling SPI-related GPIO pins
#include "STM32_F103C6_gpio_drivers.h"

// Define a structure for managing SPI interrupt settings
typedef struct{
	uint8_t TXEIE:1;    // Enable or disable the Tx buffer empty interrupt
	uint8_t RXNEIE:1;   // Enable or disable the Rx buffer not empty interrupt
	uint8_t ERRIE:1;    // Enable or disable the error interrupt
	uint8_t Receirve:5; // Reserved bits for future use or alignment

} Intyrrpt;

// Define an enumeration for polling options (Enable or Disable)
typedef enum{
	Enable,  // Enable polling
	Disable  // Disable polling
} polling;

// Define a structure for configuring the SPI peripheral
typedef struct{
	uint16_t SPI_Mode;        // Specifies the SPI mode (Master or Slave)
	uint16_t SPI_Direction;   // Specifies the data direction (full-duplex, half-duplex, etc.)
	uint16_t frame_formate;   // Specifies the frame format (MSB or LSB first)
	uint16_t Data_S;          // Specifies the data size (8-bit or 16-bit)
	uint16_t CLK_Polarity;    // Specifies the clock polarity (CPOL)
	uint16_t CLK_Phase;       // Specifies the clock phase (CPHA)
	uint16_t NSS;             // Specifies the NSS management (software or hardware)
	uint16_t SPI_Baudrate;    // Specifies the SPI baud rate prescaler
	uint16_t IRQ_Enable;      // Specifies whether to enable SPI interrupts
	void (* P_SPI_IRQ)(Intyrrpt SPI_Inturrpt);  // Pointer to the interrupt callback function

} SPI_Config_t;

// SPI Mode Definitions
#define SPI_Mode_Master			   (0x1U<<2)          // Set SPI to Master mode
#define SPI_Mode_Slave			   (0X00000000U)      // Set SPI to Slave mode

// SPI Direction Definitions
#define SPI_Direction_2_line 		   (0X00000000U)       // Full-duplex (2-line) mode
#define SPI_Direction_2_line_Receive_onle 		   (0x1U<<10) // Receive-only in full-duplex mode
#define SPI_Direction_1_line_Receive_onle 		   (0x1U<<15) // 1-line receive-only mode
#define SPI_Direction_1_line_transmite_onle 	   ((0x1U<<15) | (0x1U << 14)) // 1-line transmit-only mode

// SPI Frame Format Definitions
#define frame_formate_LSB			   (0x1U<<7)          // LSB first
#define frame_formate_MSB			   (0X00000000U)      // MSB first

// SPI Data Size Definitions
#define Data_S_8_Bits				   (0X00000000U)      // 8-bit data size
#define Data_S_16_Bits				   (0x1U<<11)         // 16-bit data size

// SPI Clock Polarity Definitions
#define CLK_Polarity_Idl_Low		   (0X00000000U)      // Clock polarity: idle low (CPOL=0)
#define CLK_Polarity_Idl_High		   (0x1U<<1)          // Clock polarity: idle high (CPOL=1)

// SPI Clock Phase Definitions
#define CLK_Phase_first_clock		   (0X00000000U)      // Clock phase: first clock transition (CPHA=0)
#define CLK_Phase_second_clock		   (0x1U<<0)          // Clock phase: second clock transition (CPHA=1)

// SPI NSS (Slave Select) Management Definitions
#define SPI_NSS_HARD_Slave	   (0X00000000U)
#define SPI_NSS_Master_HARD_Output_disable			   ~(0x1U<<2)      // Hardware NSS management for output
#define SPI_NSS_Master_HARD_Output_enable	   (0x1U<<2)          // Hardware NSS management for Master mode
#define SPI_NSS_Slave_Software_Reset	   (0x1U<<9)          // Software management of NSS in Slave mode
#define SPI_NSS_Slave_Software_set		   ((0x1U<<9)|(0x1U<<8))          // Software management of NSS in Slave mode

// SPI Baud Rate Prescaler Definitions
#define SPI_Baudrate_fPCLK_2           (0X00000000U)      // Baud rate = fPCLK/2
#define SPI_Baudrate_fPCLK_4           (0b001U<<3)        // Baud rate = fPCLK/4
#define SPI_Baudrate_fPCLK_8           (0b010U<<3)        // Baud rate = fPCLK/8
#define SPI_Baudrate_fPCLK_16          (0b011U<<3)        // Baud rate = fPCLK/16
#define SPI_Baudrate_fPCLK_32          (0b100U<<3)        // Baud rate = fPCLK/32
#define SPI_Baudrate_fPCLK_64          (0b101U<<3)        // Baud rate = fPCLK/64
#define SPI_Baudrate_fPCLK_128         (0b110U<<3)        // Baud rate = fPCLK/128
#define SPI_Baudrate_fPCLK_256         (0b111U<<3)        // Baud rate = fPCLK/256

// SPI Interrupt Enable/Disable Definitions
#define IRQ_Enable_None				(uint32_t)(0X00000000U)  // No interrupts enabled
#define IRQ_Enable_TXEIE			(uint32_t)(0x1U<<7)      // Enable TX buffer empty interrupt
#define IRQ_Enable_RXNEIE			(uint32_t)(0x1U<<6)      // Enable RX buffer not empty interrupt
#define IRQ_Enable_ERRIE			(uint32_t)(0x1U<<5)      // Enable error interrupt

// Function Prototypes for SPI Driver
void Mcal_SPI_Init(SPI_Typedef* SPIX, SPI_Config_t* SPI_config);  // Initialize SPI with the specified configuration
void Mcal_SPI_Deinit(SPI_Typedef* SPIX);                         // Deinitialize the specified SPI peripheral
void Mcal_SPI_Sent(SPI_Typedef* SPIX, uint16_t* Data, polling poll); // Send data via SPI, with optional polling
void Mcal_SPI_Receive(SPI_Typedef* SPIX, uint16_t* Data, polling poll); // Receive data via SPI, with optional polling

void Mcal_SPI_TX_RX(SPI_Typedef* SPIX, uint16_t* Data, polling poll);
void Mcal_SPI_Gpio_Set_Pins(SPI_Typedef* SPIX);                  // Configure the GPIO pins for the specified SPI peripheral

#endif /* INC_STM32_F103C6_SPI_DRIVERS_H_ */
