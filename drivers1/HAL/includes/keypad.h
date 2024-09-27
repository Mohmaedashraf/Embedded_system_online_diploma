/*
 * keypad.h
 *
 *  Created on: Jul 23, 2024
 *      Author: 3m.B
 */

#ifndef KEYPAD_DRIVER_KEYPAD_H_
#define KEYPAD_DRIVER_KEYPAD_H_
#include <stm32f103x6.h>
#include <STM32_F103C6_gpio_drivers.h>
#define KEYBAD_PORT GPIOB


#define R0	GPIO__Pin0
#define R1	GPIO__Pin1
#define R2	GPIO__Pin3
#define R3	GPIO__Pin4
#define C0	GPIO__Pin5
#define C1	GPIO__Pin6
#define C2	GPIO__Pin7
#define C3	GPIO__Pin8
static unsigned char Keypad_Character[4][4] ={{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'!','0','=','+'}};
void KEYBAD_INIT();
char KEYBAD_GETCHAR();



#endif /* KEYPAD_DRIVER_KEYPAD_H_ */
