#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

// Include necessary header files for STM32F103C6 and peripheral drivers
#include <stm32f103x6.h>
#include <STM32_F103C6_gpio_drivers.h>
#include <lcd.h>                            // LCD driver (assumed to control an external LCD)
#include <keypad.h>                         // Keypad driver (assumed to control an external keypad)
#include <STM32_F103C6_EXTIO_drivers.h>     // External interrupt (EXTI) driver for handling GPIO interrupts
#include "STM32_F103C6_USART_drivers.h"     // USART driver for serial communication
#include "STM32_F103C6_SPI_drivers.h"       // SPI driver for SPI communication
#include "STM32_F103C6_I2C_drivers.h"
#include "I2C_Slave_EEPROM.h"
// Define MCU operation mode
//#define MCU_Act_As_Master  // Define to configure MCU as SPI Master
//#define MCU_Act_As_Master
// #define MCU_Act_As_Slave                  // Uncomment to configure MCU as SPI Slave

unsigned int IRQ_Flag = 0;                  // Interrupt request flag
unsigned char ch;                           // Variable to store received character

/**
 * @brief Initializes the clock for GPIOA, GPIOB, and AFIO.
 * @retval None
 */
void clock_init() {
	RCC_GPIOA_CLK_EN();                     // Enable clock for GPIOA
	RCC_GPIOB_CLK_EN();                     // Enable clock for GPIOB
	RCC_AFIO_CLK_EN();                      // Enable clock for AFIO (Alternate Function I/O)
}
//void SPI_IRQ_CallBack(Intyrrpt SPI_IRQ){
//#ifdef MCU_Act_As_Slave
//	if(SPI_IRQ.RXNEIE){
//		ch=0x0f ;
//		Mcal_SPI_TX_RX(SPI1, &ch, Disable);
//		MCAL_UART_SendData(USART1, &ch, Enable);
//	}
//
//#endif
//}
//// UART Callback function to handle received data
//void Mohamed_UART_CallBack(void){
//#ifdef MCU_Act_As_Master
//	MCAL_UART_ReceiveData(USART1, &ch, Disable);  // Receive data from USART1 without polling
//	MCAL_UART_SendData(USART1, &ch, Disable);     // Echo received data back via USART1
//	MCAL_GPIO_WritePin(GPIOA, GPIO__Pin4, 0);    // Set NSS low (select SPI slave)
//	Mcal_SPI_TX_RX(SPI1, &ch, Enable);           // Transmit and receive data via SPI1
//	MCAL_GPIO_WritePin(GPIOA, GPIO__Pin4, 1);    // Set NSS high (deselect SPI slave)
//#endif
//}

/**
 * @brief Main program entry point.
 * @retval int
 */
int main(void) {
	//    GPIO_PinConfig_t pinconfg;                    // GPIO pin configuration structure
	clock_init();                                 // Initialize system clocks

	//    // UART configuration
	//    UART_Config uartCFG;
	//    uartCFG.BaudRate = UART_BaudRate_115200;
	//    uartCFG.HFlowCtl = UART_HFlowCtl_NONE;
	//    uartCFG.P_IRQ_CallBack = Mohamed_UART_CallBack;
	//    uartCFG.IRQ_Enable = UART_IRQ_Enable_RXNE;
	//    uartCFG.Parity = UART_Parity_NONE;
	//    uartCFG.PayloadLength = UART_Payload_Length_8B;
	//    uartCFG.StopBite = UART_Stopbit_1;
	//    uartCFG.USART_Mode = USART_Mode_TX_RX;
	//
	//    MCAL_UART_INIT(USART1, &uartCFG);              // Initialize UART1 with configuration
	//    MCAL_UART_GPIO_Set_Pins(USART1);               // Set UART1 GPIO pins
	//
	//    // SPI configuration
	//    SPI_Config_t SPI_Conf;
	//    SPI_Conf.CLK_Phase = CLK_Phase_second_clock;
	//    SPI_Conf.CLK_Polarity = CLK_Polarity_Idl_High;
	//    SPI_Conf.Data_S = Data_S_8_Bits;
	//    SPI_Conf.frame_formate = frame_formate_MSB;
	//    SPI_Conf.SPI_Direction = SPI_Direction_2_line;
	//    SPI_Conf.SPI_Baudrate = SPI_Baudrate_fPCLK_8;
	//
	//#ifdef MCU_Act_As_Master
	//    SPI_Conf.SPI_Mode = SPI_Mode_Master;
	//    SPI_Conf.IRQ_Enable = IRQ_Enable_None;         // No interrupts for SPI
	//    SPI_Conf.NSS = SPI_NSS_Slave_Software_set;     // Software NSS management
	//    SPI_Conf.P_SPI_IRQ = NULL;                     // No IRQ callback needed
	//    // Configure NSS as output push-pull
	//    pinconfg.GPIO__PinNumber = GPIO__Pin4;
	//    pinconfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	//    pinconfg.GPIO_SPEED = GPIO_SPEED10;
	//    MCAL_GPIO_INIT(GPIOA, &pinconfg);              // Initialize GPIOA Pin 4
	//    MCAL_GPIO_WritePin(GPIOA, GPIO__Pin4, 1);      // Set NSS high (deselect SPI slave)
	//
	//#endif
	//
	//#ifdef MCU_Act_As_Slave
	//    SPI_Conf.SPI_Mode = SPI_Mode_Slave;
	//    SPI_Conf.IRQ_Enable=IRQ_Enable_RXNEIE;
	//    SPI_Conf.NSS=SPI_NSS_HARD_Slave;
	//    SPI_Conf.P_SPI_IRQ=SPI_IRQ_CallBack;
	//
	//#endif
	//    Mcal_SPI_Init(SPI1, &SPI_Conf);                // Initialize SPI1 with configuration
	//    Mcal_SPI_Gpio_Set_Pins(SPI1);                  // Set SPI1 GPIO pins
	//

	unsigned char ch1[]={0x1,0x2,0x3,0x4,0x5,0x6,0x7};
	unsigned char ch2[7]={0};
	eeprom_init();
	eeprom_write_Nbytes(0xAF, ch1, 7);
	eeprom_read_byte(0xAF, ch2, 7);

	//test case 2
	ch1[0]=0xA;
	ch1[1]=0xB;
	ch1[2]=0xC;
	ch1[3]=0xD;
	eeprom_write_Nbytes(0xFFF, ch1, 4);
	eeprom_read_byte(0xFFF, ch2, 4);

	// Main loop
	while (1) {
		// Add any additional logic or checks here
	}

	return 0;
}
