/*
 * LCD.c
 *

 * Created: 2/6/2024 7:09:02 AM
 *  Author: hassan
 */


#include "lcd.h"
#include "stm32f103x6.h"


GPIO_PinConfig_t pinCfg;

//***************************Delay Function***********************************

void wait_ms(uint32_t time){


	uint32_t i,j;
	for(i=0 ;i<time;i++){

		for(j=0;j<255;j++);

	}

}



//***************************KICK FUNCTION***********************************
void LCD_KICK(void){
	MCAL_GPIO_WritePin(GPIOA, Enable_Switch, GPIO_PIN_RESET);
	MCAL_GPIO_WritePin(GPIOA, Enable_Switch, GPIO_PIN_RESET);

    wait_ms(50);
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, Enable_Switch, GPIO_PIN_SET);
}

//***************************LCD INIT FUNCTION***********************************

void LCD_GPIO_init(void)
{
    // Setting control pins (RS, RW, EN) to be output
    pinCfg.GPIO__PinNumber = RS_Switch;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_CTRL_PORTB, &pinCfg);

    pinCfg.GPIO__PinNumber = RW_Switch;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_CTRL_PORTB, &pinCfg);

    pinCfg.GPIO__PinNumber = Enable_Switch;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_CTRL_PORTB, &pinCfg);

    // Setting Data Pins D0 -> D7 to be output with 10MHz speed
    pinCfg.GPIO__PinNumber = LCD_D0_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D1_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D2_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D3_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D4_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D5_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D6_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    pinCfg.GPIO__PinNumber = LCD_D7_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    // RS -> 0 (Command Mode)
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RS_Switch, GPIO_PIN_RESET);
    // RW -> 0 (Write Mode)
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RW_Switch, GPIO_PIN_RESET);
    // EN -> 0
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, Enable_Switch, GPIO_PIN_RESET);
}

void LCD_Init(void)
{
    wait_ms(20);
    LCD_GPIO_init();
    wait_ms(20);
    LCD_clear_screen();

    #ifdef Eight_Bit_MODE
    Write_Command(eight_bit_2Line);
    #endif

    Write_Command(Entry_mode);
    Write_Command(Beginning_first_line);
    Write_Command(Display_on_Curosr_blinking);
}


//***************************LCD CLEAR FUNCTION***********************************

void LCD_clear_screen(void)
{
	Write_Command(Clear_display);
}



 //***************************COMMAND FUNCTION***********************************

void Write_Command(unsigned char command){

    LCD_Busy();

    #ifdef Eight_Bit_MODE

    //RS == 0 (Command Mode)
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RS_Switch, GPIO_PIN_RESET);
    //RW == 0 (Write Mode)
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RW_Switch, GPIO_PIN_RESET);

    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D0_PIN, checkbit(command,0));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D1_PIN, checkbit(command,1));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D2_PIN, checkbit(command,2));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D3_PIN, checkbit(command,3));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D4_PIN, checkbit(command,4));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D5_PIN, checkbit(command,5));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D6_PIN, checkbit(command,6));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D7_PIN, checkbit(command,7));

    wait_ms(30);
    LCD_KICK();
    #endif
}


void Write_char(unsigned char data){

    #ifdef Eight_Bit_MODE
    LCD_Busy();

    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RS_Switch, GPIO_PIN_SET);

    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D0_PIN, checkbit(data,0));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D1_PIN, checkbit(data,1));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D2_PIN, checkbit(data,2));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D3_PIN, checkbit(data,3));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D4_PIN, checkbit(data,4));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D5_PIN, checkbit(data,5));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D6_PIN, checkbit(data,6));
    MCAL_GPIO_WritePin(LCD_PORTA, LCD_D7_PIN, checkbit(data,7));

    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RW_Switch, GPIO_PIN_RESET);

    LCD_KICK();

    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RS_Switch, GPIO_PIN_RESET);
    #endif
}

//*************************STRING FUNCTION*************************************



void Write_String(char* data){

	int count  = 0;

	while(*data > 0){


		Write_char(*data++);

		count++;

		if(count == 16){

			LCD_GOTO_XY(2,0);


		}

		else if(count == 32){
			LCD_clear_screen();
			LCD_GOTO_XY(1,0);
			count = 0;
		}



	}


	}

//****************************BUSY FUNCTION**********************************

void LCD_Busy(void)
{
    #ifdef Eight_Bit_MODE

    pinCfg.GPIO__PinNumber = GPIO__Pin7;
    pinCfg.GPIO_MODE = GPIO_Floating_input;
    MCAL_GPIO_INIT(GPIOA, &pinCfg);

    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RW_Switch, GPIO_PIN_SET);
    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RS_Switch, GPIO_PIN_RESET);

    while (MCAL_GPIO_ReadPin(LCD_PORTA, LCD_D7_PIN) & 1);

    LCD_KICK();

    pinCfg.GPIO__PinNumber = LCD_D7_PIN;
    pinCfg.GPIO_MODE = GPIO_General_purpose_output_push_pull;
    pinCfg.GPIO_SPEED = GPIO_SPEED10;
    MCAL_GPIO_INIT(LCD_PORTA, &pinCfg);

    MCAL_GPIO_WritePin(LCD_CTRL_PORTB, RW_Switch, GPIO_PIN_RESET);
    #endif
}

//*****************************POSITION FUNCTION*********************************

void LCD_GOTO_XY(int line , int position){

	if(line == 1){

		if(position < 16 &&  position >=0){

			Write_Command(Beginning_first_line + position);

		}



	}


	else if(line == 2){

		if(position < 32  && position >=0)

		Write_Command(Beginning_second_line + position);


	}




}

void LCD_command_4bit(unsigned char command){


	/*LCD_Busy();
	LCD_PORTA &= 0x0F;
	LCD_PORTA |= (0xF0 & command);
	LCD_CTRL_PORTB &= ~((1<<RW_Switch)|(1<<RW_Switch));
	LCD_KICK();
	LCD_PORTA &= 0x0F;
	LCD_PORTA |= ((command << DATA_SHIFT) & 0xF0);
	LCD_KICK();
	*/


}
