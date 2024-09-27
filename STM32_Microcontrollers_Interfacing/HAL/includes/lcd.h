/*
 * LCD.h
 *
 * Created: 2/6/2024 7:08:47 AM
 *  Author: hassa
 */


#ifndef LCD_H_
#define LCD_H_

#include "stdlib.h"
#include "stdint.h"
#include "STM32_F103C6_gpio_drivers.h"
#include "stm32f103x6.h"

 #define LCD_PORTA	GPIOA
 #define LCD_CTRL_PORTB GPIOA

//DATA Pins
#define LCD_D0_PIN	GPIO__Pin0
#define LCD_D1_PIN	GPIO__Pin1
#define LCD_D2_PIN	GPIO__Pin2
#define LCD_D3_PIN	GPIO__Pin3
#define LCD_D4_PIN	GPIO__Pin4
#define LCD_D5_PIN	GPIO__Pin5
#define LCD_D6_PIN	GPIO__Pin6
#define LCD_D7_PIN	GPIO__Pin7

//Control Pins
#define RS_Switch			GPIO__Pin8
#define RW_Switch			GPIO__Pin9
#define Enable_Switch 		GPIO__Pin10



//LCD Command Macros

#define Beginning_first_line	(0x80) //Force cursor to beginning of the first line#define Beginning_second_line   (0xc0) //Force cursor to beginning of the second line
#define Two_lines_and_5x7_matrix (0x38) //Use two lines and 5x7 matrix
#define Line1_pos3	(0x83) //Cursor line 1 position 3
#define Second_line_active (0x3c)  //Activate second line
#define Second_line_pos3 (0xC3) //Jump to second line position 3
#define Second_line_pos1 (0xC1) //Jump to second line  position 1


//LCD Instruction Set Macros
#define eight_bit_1Line	(0x30)
#define eight_bit_2Line (0x38)
#define four_bit_1line (0x20)
#define four_bit_2line (0x28)
#define Entry_mode	(0x06)
#define Display_off_Curosr_off (0x08)
#define Display_on_Curosr_on (0x0E)
#define Display_on_Curosr_off (0x0C)
#define Display_on_Curosr_blinking (0x0F)
#define Shift_entire_left  (0x18)
#define Shift_entire_right (0x1C)
#define Move_cursor_left_one_char (0x10)
#define Move_cursor_right_one_char (0x14)
#define Clear_display (0x01)	//this also clears DDRAM content

#define Beginning_second_line   (0xc0)
#define checkbit(data,bit)	((data>>bit)&1)
//MODES
//#define FOUR_Bit_MODE
#define Eight_Bit_MODE





//Shift Bits (for 4-bit use only)
#define DATA_SHIFT	(4)


//LCD FUNCTIONS
void LCD_Init(void);
void Write_Command(unsigned char command);
void Write_char(unsigned char data);
void Write_String(char* data);
void LCD_Busy(void);
void LCD_clear_screen(void);
void LCD_GOTO_XY(int line , int position);
void LCD_command_4bit(unsigned char command);
void wait_ms(uint32_t time);
void LCD_GPIO_init(void);


//LCD TESTS



#endif /* LCD_H_ */
