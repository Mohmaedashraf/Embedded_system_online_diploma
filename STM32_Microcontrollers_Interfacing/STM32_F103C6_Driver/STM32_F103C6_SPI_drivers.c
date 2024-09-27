/*
 * STM32_F103C6_SPI_drivers.c
 *
 *  Created on: Aug 16, 2024
 *      Author: 3m.B
 */

#include "STM32_F103C6_SPI_drivers.h"       // SPI driver header for SPI configuration and control
#include "STM32_F103C6_EXTIO_drivers.h"     // External interrupt (EXTI) driver header for handling external interrupts

// Global array to store SPI configurations for SPI1 and SPI2
SPI_Config_t *global_SPI_Config[2] = {NULL, NULL};  // Array to hold pointers to SPI configuration structures

// Define indices for SPI1 and SPI2 in the global configuration array
#define SPI1_Index       0   // Index for SPI1 in the global configuration array
#define SPI2_Index       1   // Index for SPI2 in the global configuration array

// Definitions for SPI status register flags
#define SPI_SR_TXE			((uint8_t)0x02)  // Transmit buffer empty flag
#define SPI_SR_RXNE			((uint8_t)0x01)  // Receive buffer not empty flag

/**
 * @brief  Initializes the specified SPI peripheral with the provided configuration.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 *         - SPI1: First SPI peripheral
 *         - SPI2: Second SPI peripheral
 * @param  SPI_config: Pointer to the SPI configuration structure, which includes
 *         settings such as mode (Master/Slave), clock polarity, clock phase, data size, etc.
 * @retval None
 *
 * @details This function configures the SPI peripheral according to the settings provided
 *          in the SPI configuration structure. It enables the peripheral clock, sets up the
 *          SPI control registers (CR1 and CR2), and optionally enables interrupts if they
 *          are configured. The configuration is stored in a global array for future reference.
 */
void Mcal_SPI_Init(SPI_Typedef* SPIX, SPI_Config_t* SPI_config) {
	uint16_t temp_CR1 = 0;  // Temporary variable to accumulate the configuration for the SPI_CR1 register
	uint16_t temp_CR2 = 0;  // Temporary variable to accumulate the configuration for the SPI_CR2 register

	// Determine which SPI peripheral (SPI1 or SPI2) is being initialized and store the configuration globally
	if (SPIX == SPI1) {
		global_SPI_Config[SPI1_Index] = SPI_config;  // Store the configuration for SPI1 in the global array
		RCC_SPI1_CLK_EN();  // Enable the clock for SPI1 to allow its operation
	} else if (SPIX == SPI2) {
		global_SPI_Config[SPI2_Index] = SPI_config;  // Store the configuration for SPI2 in the global array
		RCC_SPI2_CLK_EN();  // Enable the clock for SPI2 to allow its operation
	}

	// Start configuring the SPI_CR1 register
	// Enable the SPI by setting the SPE (SPI Enable) bit
	temp_CR1 |= (1 << 6);  // Set SPE bit to 1 to enable the SPI peripheral

	// Configure the SPI mode (Master or Slave)
	temp_CR1 |= SPI_config->SPI_Mode;  // Set the mode (Master/Slave) based on the configuration

	// Configure the clock phase (CPHA)
	temp_CR1 |= SPI_config->CLK_Phase;  // Set the clock phase (CPHA) according to the configuration

	// Configure the clock polarity (CPOL)
	temp_CR1 |= SPI_config->CLK_Polarity;  // Set the clock polarity (CPOL) according to the configuration

	// Configure the data size (8-bit or 16-bit)
	temp_CR1 |= SPI_config->Data_S;  // Set the data size according to the configuration

	// Configure the NSS (Slave Select) management based on the configuration
	if (SPI_config->NSS == SPI_NSS_Master_HARD_Output_enable) {
		temp_CR2 |= (0x1U << 2);  // Enable hardware NSS output for Master mode
	} else if (SPI_config->NSS == SPI_NSS_Master_HARD_Output_disable) {
		temp_CR2 &= ~(0x1U << 2);  // Disable hardware NSS output for Master mode
	} else {
		temp_CR1 |= SPI_config->NSS;  // If using software NSS, set it in the CR1 register
	}

	// Set the baud rate prescaler
	temp_CR1 |= SPI_config->SPI_Baudrate;  // Configure the baud rate prescaler for SPI clock speed

	// Set the SPI data direction (full-duplex, half-duplex, etc.)
	temp_CR1 |= SPI_config->SPI_Direction;  // Set the data direction based on the configuration

	// Set the frame format (MSB first or LSB first)
	temp_CR1 |= SPI_config->frame_formate;  // Configure the frame format as MSB or LSB first

	// If interrupts are enabled in the configuration, enable the corresponding NVIC interrupts
	if (SPI_config->IRQ_Enable != IRQ_Enable_None) {
		if (SPIX == SPI1) {
			NVIC_IRQ35_SPI1_Enable;  // Enable NVIC interrupt for SPI1
		} else if (SPIX == SPI2) {
			NVIC_IRQ36_SPI2_Enable;  // Enable NVIC interrupt for SPI2
		}
		temp_CR2 |= SPI_config->IRQ_Enable;  // Set the IRQ enable bits in the CR2 register
	}

	// Write the final configuration to the SPI control registers
	SPIX->CR1 = temp_CR1;  // Write the accumulated configuration to the SPI_CR1 register
	SPIX->CR2 = temp_CR2;  // Write the accumulated configuration to the SPI_CR2 register
}

/**
 * @brief  Deinitializes the specified SPI peripheral.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 *         - SPI1: First SPI peripheral
 *         - SPI2: Second SPI peripheral
 * @retval None
 *
 * @details This function disables the SPI peripheral and resets its configuration,
 *          including disabling the corresponding NVIC interrupt and resetting the SPI clock.
 */
void Mcal_SPI_Deinit(SPI_Typedef* SPIX){
	if(SPIX == SPI1){
		NVIC_IRQ35_SPI1_Disable;  // Disable NVIC interrupt for SPI1
		RCC_SPI1_Reset();  // Reset SPI1 peripheral
	} else if(SPIX == SPI2){
		NVIC_IRQ36_SPI2_Disable;  // Disable NVIC interrupt for SPI2
		RCC_SPI2_Reset();  // Reset SPI2 peripheral
	}
}

/**
 * @brief  Sends data over the specified SPI peripheral.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 * @param  Data: Pointer to the data to be sent.
 * @param  poll: Specifies whether to wait for the transmit buffer to be empty before sending.
 *         - Enable: Wait for the transmit buffer to be empty before sending.
 *         - Disable: Do not wait.
 * @retval None
 *
 * @details This function sends data over SPI. If polling is enabled, it waits
 *          until the transmit buffer is empty before sending the data.
 */
void Mcal_SPI_Sent(SPI_Typedef* SPIX, uint16_t* Data, polling poll){
	if(poll == Enable)
		while(!((SPIX->SR) & SPI_SR_TXE));  // Wait until the transmit buffer is empty
	SPIX->DR = *Data;  // Write data to the SPI data register
}

/**
 * @brief  Receives data from the specified SPI peripheral.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 * @param  Data: Pointer to the variable where the received data will be stored.
 * @param  poll: Specifies whether to wait for data to be received.
 *         - Enable: Wait for data to be received before reading.
 *         - Disable: Do not wait.
 * @retval None
 *
 * @details This function receives data from SPI. If polling is enabled, it waits
 *          until data is received before reading it from the data register.
 */
void Mcal_SPI_Receive(SPI_Typedef* SPIX, uint16_t* Data, polling poll){
	if(poll == Enable)
		while(!((SPIX->SR) & SPI_SR_RXNE));  // Wait until data is received
	*Data = SPIX->DR;  // Read data from the SPI data register
}

/**
 * @brief  Sends and receives data over the specified SPI peripheral.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 * @param  Data: Pointer to the data to be sent and the variable to store the received data.
 * @param  poll: Specifies whether to wait for the transmit buffer to be empty and for data to be received.
 *         - Enable: Wait for the transmit buffer to be empty and for data to be received.
 *         - Disable: Do not wait.
 * @retval None
 *
 * @details This function sends and receives data simultaneously over SPI. If polling is enabled,
 *          it waits until the transmit buffer is empty before sending, and waits until data is
 *          received before reading it from the data register.
 */
void Mcal_SPI_TX_RX(SPI_Typedef* SPIX, uint16_t* Data, polling poll){
	if(poll == Enable)
		while(!((SPIX->SR) & SPI_SR_TXE));  // Wait until the transmit buffer is empty
	SPIX->DR = *Data;  // Write data to the SPI data register
	if(poll == Enable)
		while(!((SPIX->SR) & SPI_SR_RXNE));  // Wait until data is received
	*Data = SPIX->DR;  // Read data from the SPI data register
}

/**
 * @brief  Configures the GPIO pins used by the specified SPI peripheral.
 * @param  SPIX: Pointer to the SPI peripheral (SPI1 or SPI2).
 * @retval None
 *
 * @details This function configures the GPIO pins (NSS, SCK, MISO, MOSI) for the specified SPI peripheral.
 *          The pin configuration depends on whether the SPI is in Master or Slave mode, and whether
 *          hardware NSS management is enabled.
 */
void Mcal_SPI_Gpio_Set_Pins(SPI_Typedef* SPIX){

	GPIO_PinConfig_t gpio_pin;  // Structure to configure GPIO pins
	if(SPIX == SPI1){
		if(global_SPI_Config[SPI1_Index]->SPI_Mode == SPI_Mode_Master){
			// Configure NSS pin for Master mode
			switch(global_SPI_Config[SPI1_Index]->NSS){
			case SPI_NSS_Master_HARD_Output_disable:
				gpio_pin.GPIO__PinNumber = GPIO__Pin4;
				gpio_pin.GPIO_MODE = GPIO_Floating_input;
				MCAL_GPIO_INIT(GPIOA, &gpio_pin);
				break;
			case SPI_NSS_Master_HARD_Output_enable:
				gpio_pin.GPIO__PinNumber = GPIO__Pin4;
				gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
				gpio_pin.GPIO_SPEED = GPIO_SPEED10;
				MCAL_GPIO_INIT(GPIOA, &gpio_pin);
				break;
			}

			// Configure SCK, MISO, and MOSI pins for Master mode
			gpio_pin.GPIO__PinNumber = GPIO__Pin5;  // SCK
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin6;  // MISO
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin7;  // MOSI
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);
		}else{
			// Configure NSS, SCK, MISO, and MOSI pins for Slave mode
			if(global_SPI_Config[SPI1_Index]->NSS == SPI_NSS_HARD_Slave){
				gpio_pin.GPIO__PinNumber = GPIO__Pin4;  // NSS
				gpio_pin.GPIO_MODE = GPIO_Floating_input;
				MCAL_GPIO_INIT(GPIOA, &gpio_pin);
			}
			gpio_pin.GPIO__PinNumber = GPIO__Pin5;  // SCK
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin6;  // MISO
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin7;  // MOSI
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOA, &gpio_pin);
		}
	}else if(SPIX == SPI2){
		if(global_SPI_Config[SPI2_Index]->SPI_Mode == SPI_Mode_Master){
			// Configure NSS pin for Master mode
			switch(global_SPI_Config[SPI2_Index]->NSS){
			case SPI_NSS_Master_HARD_Output_disable:
				gpio_pin.GPIO__PinNumber = GPIO__Pin12;
				gpio_pin.GPIO_MODE = GPIO_Floating_input;
				MCAL_GPIO_INIT(GPIOB, &gpio_pin);
				break;
			case SPI_NSS_Master_HARD_Output_enable:
				gpio_pin.GPIO__PinNumber = GPIO__Pin12;
				gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
				gpio_pin.GPIO_SPEED = GPIO_SPEED10;
				MCAL_GPIO_INIT(GPIOB, &gpio_pin);
				break;
			}

			// Configure SCK, MISO, and MOSI pins for Master mode
			gpio_pin.GPIO__PinNumber = GPIO__Pin13;  // SCK
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin14;  // MISO
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin15;  // MOSI
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);
		}else{
			// Configure NSS, SCK, MISO, and MOSI pins for Slave mode
			if(global_SPI_Config[SPI2_Index]->NSS == SPI_NSS_HARD_Slave){
				gpio_pin.GPIO__PinNumber = GPIO__Pin12;  // NSS
				gpio_pin.GPIO_MODE = GPIO_Floating_input;
				MCAL_GPIO_INIT(GPIOB, &gpio_pin);
			}
			gpio_pin.GPIO__PinNumber = GPIO__Pin13;  // SCK
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin14;  // MISO
			gpio_pin.GPIO_MODE = GPIO_Alternate_function_output_Push_pull;
			gpio_pin.GPIO_SPEED = GPIO_SPEED10;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);

			gpio_pin.GPIO__PinNumber = GPIO__Pin15;  // MOSI
			gpio_pin.GPIO_MODE = GPIO_Floating_input;
			MCAL_GPIO_INIT(GPIOB, &gpio_pin);
		}
	}
}

/**
 * @brief  SPI1 interrupt handler.
 * @retval None
 *
 * @details This function handles the SPI1 interrupt by checking the status flags for transmit buffer empty,
 *          receive buffer not empty, and error conditions. It then calls the appropriate user-defined
 *          interrupt callback function.
 */
void SPI1_IRQHandler(void){

	Intyrrpt SPI_Inturrpt;  // Structure to hold interrupt flags
	SPI_Inturrpt.TXEIE = (((SPI1->SR) & (1 << 1)) >> 1);  // Check the TXE (Transmit buffer empty) flag
	SPI_Inturrpt.RXNEIE = (((SPI1->SR) & (1 << 0)) >> 0);  // Check the RXNE (Receive buffer not empty) flag
	SPI_Inturrpt.ERRIE = (((SPI1->SR) & (1 << 4)) >> 4);  // Check the error flag

	global_SPI_Config[SPI1_Index]->P_SPI_IRQ(SPI_Inturrpt);  // Call the user-defined callback function
}

/**
 * @brief  SPI2 interrupt handler.
 * @retval None
 *
 * @details This function handles the SPI2 interrupt by checking the status flags for transmit buffer empty,
 *          receive buffer not empty, and error conditions. It then calls the appropriate user-defined
 *          interrupt callback function.
 */
void SPI2_IRQHandler(void){
	Intyrrpt SPI_Inturrpt;  // Structure to hold interrupt flags
	SPI_Inturrpt.TXEIE = (((SPI2->SR) & (1 << 1)) >> 1);  // Check the TXE (Transmit buffer empty) flag
	SPI_Inturrpt.RXNEIE = (((SPI2->SR) & (1 << 0)) >> 0);  // Check the RXNE (Receive buffer not empty) flag
	SPI_Inturrpt.ERRIE = (((SPI2->SR) & (1 << 4)) >> 4);  // Check the error flag

	global_SPI_Config[SPI2_Index]->P_SPI_IRQ(SPI_Inturrpt);  // Call the user-defined callback function
}
