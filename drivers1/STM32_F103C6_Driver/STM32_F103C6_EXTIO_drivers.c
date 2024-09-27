/*
 * STM32_F103C6_EXTIO_drivers.c
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#include "STM32_F103C6_EXTIO_drivers.h"
#include <stm32f103x6.h>
#include "STM32_F103C6_gpio_drivers.h"
#define AFIO_GPIO_EXTI_Mapping(x) 		((x == GPIOA) ? 0 : \
										 (x == GPIOB) ? 1 : \
										 (x == GPIOC) ? 2 : \
										 (x == GPIOD) ? 3 : 0 )



void (*Gp_IRQ_CallBack[15])(void);
void Enable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Enable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Enable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Enable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 4:
		NVIC_IRQ9_EXTI3_Enable;
		break;
	case 5:

	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTIO5_9_Enable;
		break;
	case 10:

	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTIO10_15_Enable;
		break;
	}



}
void Disable_NVIC(uint16_t IRQ){
	switch(IRQ){
	case 0:
		NVIC_IRQ6_EXTI0_Disable;
		break;
	case 1:
		NVIC_IRQ7_EXTI1_Disable;
		break;
	case 2:
		NVIC_IRQ8_EXTI2_Disable;
		break;
	case 3:
		NVIC_IRQ9_EXTI3_Disable;
		break;
	case 4:
		NVIC_IRQ10_EXTI4_Disable;
		break;
	case 5:

	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable;
		break;
	case 10:

	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable;
		break;
	}
}
void MCAL_EXTI_GPIO_Deinit(void){
	EXTIO->EMR=0x00000000;
	EXTIO->FTSR=0x00000000;
	EXTIO->IMR=0x00000000;
	EXTIO->PR=0xffffffff;
	EXTIO->RTSR=0x00000000;
	EXTIO->SWIER=0x00000000;
	NVIC_IRQ6_EXTI0_Disable;
	NVIC_IRQ7_EXTI1_Disable;
	NVIC_IRQ8_EXTI2_Disable;
	NVIC_IRQ9_EXTI3_Disable;
	NVIC_IRQ10_EXTI4_Disable;
	NVIC_IRQ23_EXTI5_9_Disable;
	NVIC_IRQ40_EXTI10_15_Disable;

}

void Update_EXTI(EXIT_Pinconfg_t *EXIT_confg){

	GPIO_PinConfig_t pinconfg;
	pinconfg.GPIO__PinNumber=EXIT_confg->EXTI_PIN.GPIO_PIN;
	pinconfg.GPIO_MODE=GPIO_Floating_input;
	MCAL_GPIO_INIT(EXIT_confg->EXTI_PIN.GPIO_Port, &pinconfg);

	uint8_t AFIO_EXIT_Index=EXIT_confg->EXTI_PIN.ETI_InputLineNumber / 4 ;

	uint8_t AFIO_EXIT_postion=(EXIT_confg->EXTI_PIN.ETI_InputLineNumber % 4)*4 ;


	AFIO->EXTICR[AFIO_EXIT_Index] &=~(0xf<<AFIO_EXIT_postion);
	AFIO->EXTICR[AFIO_EXIT_Index] |= ((AFIO_GPIO_EXTI_Mapping(EXIT_confg->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXIT_postion);	EXTIO->RTSR &=~(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
	EXTIO->FTSR &=~(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
	EXTIO->RTSR &=~(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);

	if (EXIT_confg->trigger==EXIT_Trigger_Rising){
		EXTIO->RTSR |=(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXIT_confg->trigger==EXIT_Trigger_Falling){
		EXTIO->FTSR |=(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);

	}else if(EXIT_confg->trigger==EXIT_Trigger_RisingAndFalling){
		EXTIO->RTSR |=(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
		EXTIO->FTSR |=(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);

	}
	Gp_IRQ_CallBack[EXIT_confg->EXTI_PIN.ETI_InputLineNumber]=EXIT_confg->p_IRQ_CallBack;

	if(EXIT_confg->IRQ_EN==EXIT_IRQ_Enable){
		EXTIO->IMR |=(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
		Enable_NVIC(EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
	}else{
		EXTIO->IMR &=~(1<<EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
		Disable_NVIC(EXIT_confg->EXTI_PIN.ETI_InputLineNumber);
	}





}




void MCAL_EXTI_GPIO_Init(EXIT_Pinconfg_t *EXIT_confg){

	Update_EXTI(EXIT_confg );


}
void MCAL_EXTI_GPIO_Update(EXIT_Pinconfg_t *EXIT_confg){

	Update_EXTI(EXIT_confg );












}


void EXTI0_IRQHandler(void){
	EXTIO->PR |=1<<0;


	Gp_IRQ_CallBack[0]();

}
void EXTI1_IRQHandler(void){
	EXTIO->PR |=1<<1;


	Gp_IRQ_CallBack[1]();
}
void EXTI2_IRQHandler(void){
	EXTIO->PR |=1<<2;


	Gp_IRQ_CallBack[2]();
}
void EXTI3_IRQHandler(void){
	EXTIO->PR |=1<<3;


	Gp_IRQ_CallBack[3]();
}
void EXTI4_IRQHandler(void){
	EXTIO->PR |=1<<4;


	Gp_IRQ_CallBack[4]();
}
void EXTI9_5_IRQHandler(void){
	if(EXTIO->PR & 1<<5){ EXTIO->PR |= 1<<5 ;	 Gp_IRQ_CallBack[5](); }
	if(EXTIO->PR & 1<<6){ EXTIO->PR |= 1<<6 ;	 Gp_IRQ_CallBack[6](); }
	if(EXTIO->PR & 1<<7){ EXTIO->PR |= 1<<7 ;	 Gp_IRQ_CallBack[7](); }
	if(EXTIO->PR & 1<<8){ EXTIO->PR |= 1<<8 ;	 Gp_IRQ_CallBack[8](); }
	if(EXTIO->PR & 1<<9){ EXTIO->PR |= 1<<9 ;	 Gp_IRQ_CallBack[9](); }

}
void EXTI15_10_IRQHandler(void){
	if(EXTIO->PR & 1<<10){ EXTIO->PR |= 1<<10 ;	 Gp_IRQ_CallBack[10](); }
	if(EXTIO->PR & 1<<11){ EXTIO->PR |= 1<<11 ;	 Gp_IRQ_CallBack[11](); }
	if(EXTIO->PR & 1<<12){ EXTIO->PR |= 1<<12 ;	 Gp_IRQ_CallBack[12](); }
	if(EXTIO->PR & 1<<13){ EXTIO->PR |= 1<<13 ;	 Gp_IRQ_CallBack[13](); }
	if(EXTIO->PR & 1<<14){ EXTIO->PR |= 1<<14 ;	 Gp_IRQ_CallBack[14](); }
	if(EXTIO->PR & 1<<15){ EXTIO->PR |= 1<<15 ;	 Gp_IRQ_CallBack[15](); }

}



