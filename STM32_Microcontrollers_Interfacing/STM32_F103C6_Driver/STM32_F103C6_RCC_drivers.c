/*
 * STM32_F103C6_RCC_drivers.c
 *
 *  Created on: Jul 25, 2024
 *      Author: 3m.B
 */

#include "STM32_F103C6_RCC_drivers.h"

//Set and cleared by software to control the division factor of the APB Low speed clock (PCLK1).
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16


const uint8_t APBPrescTable[8U]={0,0,0,0,1,2,3,4};
//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHPPrescTable[16U]={0,0,0,0,0,0,0,0,1,2,3,4,6,7,8,9};
uint32_t MCAL_RCC_GET_SYSCLK(void)
{

//	Bits 3:2 SWS: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: not applicable
	switch ((RCC->CFGR >> 2)& 0b11)
	{
	case 0 :
		return HSI_RC_CLK;
		break;
	case 1 :
		//To be implemented later
		return HSE_CLOCK;
		break;
	case 2 :
		//To be implemented later
		return 16000000;
		break;


	}


}


uint32_t MCAL_RCC_GetHPCLKFreq(void){

	return	(MCAL_RCC_GET_SYSCLK() >> AHPPrescTable[(RCC->CFGR>>4) & 0xf]);

}

uint32_t MCAL_RCC_GetPCLK1Freq(void){


	return	(MCAL_RCC_GetHPCLKFreq() >> APBPrescTable[(RCC->CFGR>>8) & 0b111]);
}
uint32_t MCAL_RCC_GetPCLK2Freq(void){
    return (MCAL_RCC_GetHPCLKFreq() >> APBPrescTable[(RCC->CFGR>>11) & 0b111]);
}

