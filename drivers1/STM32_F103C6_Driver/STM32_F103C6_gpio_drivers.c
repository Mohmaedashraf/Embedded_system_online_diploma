/*
 * STM32_F103C6_gpio_drivers.c
 *
 *  Created on: Jul 21, 2024
 *      Author: 3m.B
 */


#include <STM32_F103C6_gpio_drivers.h>
uint8_t Get_CRLH_Position(uint16_t PinNumber){
	switch(PinNumber){
	case GPIO__Pin0:
		return 0;
		break;
	case GPIO__Pin1:
		return 4;
		break;
	case GPIO__Pin2:
		return 8;
		break;
	case GPIO__Pin3:
		return 12 ;
		break;
	case GPIO__Pin4:
		return 16;
		break;
	case GPIO__Pin5:
		return 20;
		break;
	case GPIO__Pin6:
		return 24;
		break;
	case GPIO__Pin7:
		return 28;
		break;
	case GPIO__Pin8:
		return 0;
		break;
	case GPIO__Pin9:
		return 4;
		break;
	case GPIO__Pin10:
		return 8;
		break;
	case GPIO__Pin11:
		return 12 ;
		break;
	case GPIO__Pin12:
		return 16;
		break;
	case GPIO__Pin13:
		return 20;
		break;
	case GPIO__Pin14:
		return 24;
		break;
	case GPIO__Pin15:
		return 28;
		break;
	}
	return 0;
}
/**================================================================
 * @Fn- : MCAL_GPIO_INIT
 * @brief -	:init the GPIOX piny according to specified parameter in pinconfig
 * @param [in] -	:GPIOX (X = A,B,C,D,E)
 * @param [in] - : PinConfig pointer to GPIO_PinConfig_t that contain information about GPIOX
 * Note-
 */
void MCAL_GPIO_INIT(GPIO_Typedef *GPIOX , GPIO_PinConfig_t *PinConfig){
	// Port configuration register high (GPIOX_CRH) configure PINs from 0 >> 7
		// Port configuration register high (GPIOX_CRH) configure PINs from 8 >> 15
		volatile uint32_t *confg_reg = NULL;
		uint8_t PinConf = 0;
		//see if it's CRL or CRH
		confg_reg = (PinConfig->GPIO__PinNumber < GPIO__Pin8)? &GPIOX->CRL: &GPIOX->CRH ;
		//Reset CNF and MODE
		*confg_reg &= ~(0xf<<Get_CRLH_Position(PinConfig->GPIO__PinNumber));//* because we will write value
		/*
			 * ------------------
			 * | CNF    | MODE	|
			 * ------------------
			 * |  3	| 2 | 1	| 0	| //clear it to write what i want
			 * ------------------
		*/
		//see if the pin is Input or Output so that if it's output i put the speed with it if input then it's only mode
		if((PinConfig->GPIO_MODE == GPIO_General_purpose_output_push_pull)||(PinConfig->GPIO_MODE == GPIO_General_purpose_output_Open_drain)||(PinConfig->GPIO_MODE == GPIO_Alternate_function_output_Push_pull)||(PinConfig->GPIO_MODE == GPIO_Alternate_function_output_Open_drain))
		{
			/*
			 * 00: General purpose output push-pull		--> GPIO_MODE_OUTPUT_PP		>>	0x00000004u
			 * 01: General purpose output Open-drain	--> GPIO_MODE_OUTPUT_OD		>>	0x00000005u
			 * 10: Alternate function output Push-pull	--> GPIO_MODE_OUTPUT_AF_PP	>>	0x00000006u
			 * 11: Alternate function output Open-drain	--> GPIO_MODE_OUTPUT_AF_OD	>>	0x00000007u
			 */
			PinConf = ((((PinConfig->GPIO_MODE - 4) <<2)|(PinConfig->GPIO_SPEED))&0xf);
		}
		else
		{
			/*
			 * 00: Analog mode			--> GPIO_MODE_ANALOG		>>	0x00000000u
			 * 01: Floating input		--> GPIO_MODE_INPUT_FLO		>>	0x00000001u
			 * 01: Alternative input	--> GPIO_MODE_INPUT_FLO
			 * 11: Input with PU or PD	--> GPIO_MODE_INPUT_PU
			 * //the only thing to diff from PU or PD
			 * 		PU: ODR --> 1
			 * 		PD: ODR --> 0
			 */
			if((PinConfig->GPIO_MODE == GPIO_Analog_mode)||(PinConfig->GPIO_MODE == GPIO_Floating_input))
			{
				PinConf = (((PinConfig->GPIO_MODE << 2))&0xf);
			}
			else if(PinConfig->GPIO_MODE == GPIO_Alternate_function_input)
			{
				PinConf = (((GPIO_Floating_input << 2))&0xf);
			}
			else
			{
				PinConf = (((GPIO_Input_with_pull_up << 2))&0xf);
				if(PinConfig->GPIO_MODE == GPIO_Input_with_pull_up)
					GPIOX->ODR |= PinConfig->GPIO__PinNumber;
				else
					GPIOX->ODR &= ~PinConfig->GPIO__PinNumber;
			}
		}
		//put values in CNF AND MODE
		*confg_reg |= (PinConf<<Get_CRLH_Position(PinConfig->GPIO__PinNumber));



}



/**================================================================
 * @Fn- :MCAL_GPIO_DEINIT
 * @brief - :DEinit the GPIOX piny according to specified parameter in pinconfig
 * @param [in] - :GPIOX (X = A,B,C,D,E)
 *
 * Note-
 */




void MCAL_GPIO_DEINIT(GPIO_Typedef *GPIOX ){
if (GPIOX==GPIOA)
	RCC->APB2RSTR |=GPIO__Pin2;
else if (GPIOX==GPIOB)
	RCC->APB2RSTR |=GPIO__Pin3;
else if (GPIOX==GPIOC)
	RCC->APB2RSTR |=GPIO__Pin4;
else if (GPIOX==GPIOD)
	RCC->APB2RSTR |=GPIO__Pin5;
else
	RCC->APB2RSTR |=GPIO__Pin6;


}
/**================================================================
 * @Fn- : MCAL_GPIO_ReadPin
 * @brief -	:readpin from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)
 * @param [in] - : PinNumber
 *  @param [out] - : high or low (based on @ref GPIO_PIN_STATE)
 * Note-
 */

uint8_t MCAL_GPIO_ReadPin(GPIO_Typedef *GPIOX ,uint16_t PinNumber ){
	uint8_t bitstatu=0;
	if (((GPIOX->IDR)&PinNumber)!=GPIO_PIN_RESET)
		bitstatu=GPIO_PIN_SET;
	else
		bitstatu=GPIO_PIN_RESET;
	return bitstatu;
}
/**================================================================
 * @Fn- : MCAL_GPIO_ReadPort
 * @brief -	:readport from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)
 *  @param [out] - : high or low (based on @ref GPIO_PIN_STATE)
 * Note-
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_Typedef *GPIOX  ){

	uint16_t Port_value=0;
	Port_value=	(uint16_t)GPIOX->IDR;
	return Port_value;





}


/**================================================================
 * @Fn- : MCAL_GPIO_WritePin
 * @brief -	:Write Pin from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)
 *  @param [in] - : PinNumber
 *
 *  @param [in] - : input Pin value
 * Note-
 */
void MCAL_GPIO_WritePin(GPIO_Typedef *GPIOX ,uint16_t PinNumber  ,uint8_t value  ){
	if(value!=GPIO_PIN_RESET)
		GPIOX->BSRR=(uint32_t)PinNumber;
	else
		GPIOX->BRR=(uint32_t)PinNumber;

}
/**================================================================
 * @Fn- : MCAL_GPIO_WritePort
 * @brief -	:Write Pin from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)

 *
 *  @param [in] - : input Port value
 * Note-
 */
void MCAL_GPIO_WritePort(GPIO_Typedef *GPIOX ,uint16_t value  ){


	GPIOX->ODR=(uint32_t)value;

}
/**================================================================
 * @Fn- : MCAL_GPIO_TogglePin
 * @brief -	:toggle Pin from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)

 *
 *  @param [in] - : Pin number
 * Note-
 */
void MCAL_GPIO_TogglePin(GPIO_Typedef *GPIOX ,uint16_t PinNumber ){


	GPIOX->ODR ^=(uint32_t)PinNumber;

}
/*
 * @Fn- : MCAL_GPIO_LockPin
 * @brief -	:Lock Pin from GPIOX according to specified GPIO_PIN_NUMBER
 * @param [in] -	:GPIOX (X = A,B,C,D,E)

 *
 *  @param [in] - : Pin number
 * Note-
 */
uint8_t MCAL_GPIO_LockPin(GPIO_Typedef *GPIOX ,uint16_t PinNumber ){
	volatile uint32_t temp =0;
	temp |=1<<16;
	temp |=PinNumber;
	//Write 1
	GPIOX->LCKR=temp;
	//Write 0
	GPIOX->LCKR=PinNumber;
	//Write 1
	GPIOX->LCKR=temp;

	//Read 0
	temp=GPIOX->LCKR;
	//Read 1 (this read is optional but confirms that the lock is active)
	if((uint32_t)(GPIOX->LCKR & 1<<16))
		return GPIO_LOCK_OK;
	else {
		return GPIO_LOCK_ERROR;
	}

}

