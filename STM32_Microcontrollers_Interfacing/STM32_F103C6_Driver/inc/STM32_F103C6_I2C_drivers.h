/*
 * STM32_F103C6_I2C_drivers.h
 *
 *  Created on: Aug 22, 2024
 *      Author: 3m.B
 */

#ifndef INC_STM32_F103C6_I2C_DRIVERS_H_
#define INC_STM32_F103C6_I2C_DRIVERS_H_

#include "stm32f103x6.h"
#include "Bit_Field_I2C.h"

/*
 * S_I2C_Slave_Device_Address
 * -------------------------------------------------------------------
 * Structure for configuring the I2C slave addresses and addressing mode.
 * This structure allows for dual address configuration where a primary
 * and secondary address can be set. The addressing mode can be either
 * 7-bit or 10-bit.
 */
typedef struct
{
	uint16_t Enable_DUAL_Address; 		// 1 = Enable dual addressing mode, 0 = Disable dual addressing mode
	uint16_t Primary_Slave_Address;     // Primary address of the I2C slave
	uint16_t Secondary_Slave_Address;   // Secondary address of the I2C slave (used if dual addressing is enabled)
	uint32_t I2C_Addressing_Slave_Mode;	// Specifies the Addressing Mode of I2C Slave (7-bit or 10-bit)

} S_I2C_Slave_Device_Address;

/*
 * E_Slave_State
 * -------------------------------------------------------------------
 * Enumeration for different states of the I2C slave during communication.
 * This helps in identifying what action the application layer should take
 * when a specific event occurs.
 */
typedef enum
{
	I2C_EV_STOP,            // STOP condition detected
	I2C_ER_AF,              // Acknowledge failure (AF) detected
	I2C_EV_ADDR_Matched,    // Address matched with the slave address
	I2C_EV_DATA_REQ,		// Data requested by the master (slave should send data)
	I2C_EV_DATA_RCV			// Data received by the slave (slave should read data)

} E_Slave_State;


typedef enum
{
	Stop,
	without_stop
}E_STOP_CONDITION;
typedef enum
{
	start,
	repeated_start
}E_START_CONDITION;
typedef enum
{
	Disab=0,
	Enab=1
}FunctinalState;

typedef enum
{
	reset = 0,
	set = 1
}FlagStatus;
typedef enum
{
	I2C_Flag_Busy,
	EV5,
	EV6,
	EV8,
	EV8_1,
	EV7,
	MASTER_EVENT_BYTE_TRNSDIMETING = ((uint32_t ) 0x00070080)


}Status;

/*
 * I2C_Config
 * -------------------------------------------------------------------
 * Structure for configuring the I2C peripheral.
 * This structure contains all necessary configuration options like clock speed,
 * stretch mode, addressing mode, acknowledgment, general call, and a callback
 * function for handling slave events.
 */
typedef struct
{
	uint32_t I2C_clk_Speed;					// Clock speed of the I2C (standard or fast mode)

	uint32_t I2C_Strech_Mode;				// Stretch mode enable/disable

	uint32_t I2C_Mode;						// I2C mode (I2C or SMBus)

	S_I2C_Slave_Device_Address I2C_Slave_Address_Mode;	// Slave addressing mode configuration

	uint32_t I2C_ACK;						// Acknowledgment enable/disable

	uint32_t I2C_general_call;				// General call enable/disable

	void (* P_Slave_Event_CallBack)(E_Slave_State);	// Pointer to a callback function that handles slave events

} I2C_Config;

/*
 * Macros for I2C Configuration
 * -------------------------------------------------------------------
 * These macros define various configuration options like clock speed,
 * stretch mode, addressing mode, etc., for easier and cleaner code.
 */
#define I2C_SM_Speed_50K			(50000)  // Standard Mode with 50kHz clock speed
#define I2C_SM_Speed_100K			(100000)   // Standard Mode with 100kHz clock speed
#define I2C_FM_Speed_200K			(200000)   // Fast Mode with 200kHz clock speed
#define I2C_FM_Speed_400K			(400000)   // Fast Mode with 400kHz clock speed

#define I2C_StretcMode_Enable		(0x0U)      // Enable clock stretching
#define I2C_StretcMode_Disable		I2C_CR1_NOSTRETCH // Disable clock stretching

#define I2C_mode					(0x0U)      // Standard I2C mode
#define SMBus_Mode					I2C_CR1_SMBUS // SMBus mode

#define I2C_No_Ack					(0x0U)      // Disable acknowledgment
#define I2C_Ack						I2C_CR1_ACK // Enable acknowledgment

#define I2C_generalcall_disable		(0x0U)      // Disable general call
#define I2C_generalcall_enable		I2C_CR1_ENGC // Enable general call

#define I2C_Addressing_Slave_Mode_7Bits		(0x0U)   // 7-bit addressing mode
#define I2C_Addressing_Slave_Mode_10Bits	I2C_OAR1_ADDMODE // 10-bit addressing mode
#define I2C_MASTER_EVENT_PART_TRNSDIMETING	((uint32_t ) 0x00070080)
typedef enum
{
	I2C_Dirction_Transimiter=0,
	I2C_Dirction_Receiver=1
}I2C_Dirction;


/*
 * Function Prototypes
 * -------------------------------------------------------------------
 * These are the function prototypes for initializing, deinitializing,
 * and configuring the GPIO pins for the I2C peripheral.
 */

/*
 * MCAL_I2C_Init
 * -------------------------------------------------------------------
 * Initializes the I2C peripheral with the provided configuration.
 * Parameters:
 *  - I2CX: Pointer to the I2C peripheral (I2C1, I2C2, etc.)
 *  - I2C_conf: Pointer to the I2C configuration structure
 */
void MCAL_I2C_Init(I2C_Typedef *I2CX , I2C_Config *I2C_conf);

/*
 * MCAL_I2C_Deinit
 * -------------------------------------------------------------------
 * Deinitializes the I2C peripheral, resetting its registers to their default states.
 * Parameters:
 *  - I2CX: Pointer to the I2C peripheral (I2C1, I2C2, etc.)
 */
void MCAL_I2C_Deinit(I2C_Typedef *I2CX );

/*
 * MCAL_I2C_gpio_Set_Pins
 * -------------------------------------------------------------------
 * Configures the GPIO pins used by the I2C peripheral (SCL, SDA).
 * This function must be called after initializing the I2C peripheral.
 * Parameters:
 *  - I2CX: Pointer to the I2C peripheral (I2C1, I2C2, etc.)
 */
void MCAL_I2C_gpio_Set_Pins(I2C_Typedef *I2CX);

void MCAL_I2C_Master_TX(I2C_Typedef *I2CX ,uint16_t defAddr , uint8_t* dataout ,uint32_t datalen ,E_STOP_CONDITION stop , E_START_CONDITION start  );
void MCAL_I2C_Master_RX(I2C_Typedef *I2CX ,uint16_t defAddr , uint8_t* dataout ,uint32_t datalen ,E_STOP_CONDITION stop , E_START_CONDITION start  );
void I2C_GenerateStart(I2C_Typedef *I2CX , FunctinalState NewState , E_START_CONDITION Start);
FlagStatus I2C_Get_StatusFlag(I2C_Typedef* I2CX , Status flag);
void I2C_Send_Addrss(I2C_Typedef *I2CX , uint16_t address , I2C_Dirction Dirction);
void I2C_GenerateStop(I2C_Typedef *I2CX , FunctinalState NewState );
void I2C_AckConfig (I2C_Typedef* I2CX, FunctinalState NewState);
void MCAL_I2C_SLAVE_TX (I2C_Typedef* I2Cx, uint8_t Data);
uint8_t MCAL_I2C_SLAVE_RX (I2C_Typedef* I2Cx);

#endif /* INC_STM32_F103C6_I2C_DRIVERS_H_ */
