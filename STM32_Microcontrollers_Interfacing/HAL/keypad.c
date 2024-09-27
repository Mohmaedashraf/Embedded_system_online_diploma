/*
 * KEYPAD.c
 *
 * Created: 2/7/2024 2:11:32 PM
 *  Author: hassa
 */



#include "stm32f103x6.h"
#include "keypad.h"

void wait_msk(uint32_t time) {
    uint32_t i, j;
    for (i = 0; i < time; i++) {
        for (j = 0; j < 255; j++);
    }
}

int KEYPAD_R[] = {GPIO__Pin0, GPIO__Pin1, GPIO__Pin3, GPIO__Pin4};
int KEYPAD_C[] = {GPIO__Pin5, GPIO__Pin6, GPIO__Pin7, GPIO__Pin8};

GPIO_PinConfig_t keypad;

void KEYPAD_init(void) {
    // Rows (B0, B1, B3, B4) as Input with Pull-Up
    for (int i = 0; i < 4; i++) {
        keypad.GPIO__PinNumber = KEYPAD_R[i];
        keypad.GPIO_MODE = GPIO_Floating_input;
        MCAL_GPIO_INIT(KEYBAD_PORT, &keypad);
    }

    // Columns (B5, B6, B7, B8) as Output
    for (int i = 0; i < 4; i++) {
        keypad.GPIO__PinNumber = KEYPAD_C[i];
        keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
        keypad.GPIO_SPEED = GPIO_SPEED10;
        MCAL_GPIO_INIT(KEYBAD_PORT, &keypad);
        MCAL_GPIO_WritePin(KEYBAD_PORT, KEYPAD_C[i], GPIO_PIN_SET); // Set columns high initially
    }
}

char KEYPAD_GETCHAR(void) {
    uint8_t i, j;
    for (i = 0; i < 4; i++) {
        // Set current column low
        MCAL_GPIO_WritePin(KEYBAD_PORT, KEYPAD_C[i], GPIO_PIN_RESET);

        // Check rows for pressed button
        for (j = 0; j < 4; j++) {
            if (MCAL_GPIO_ReadPin(KEYBAD_PORT, KEYPAD_R[j]) == GPIO_PIN_RESET) {
            	wait_ms(500);

                    while (MCAL_GPIO_ReadPin(KEYBAD_PORT, KEYPAD_R[j]) == GPIO_PIN_RESET);

                    return Keypad_Character[i][j];


            }
        }

        // Set current column back to high
        MCAL_GPIO_WritePin(KEYBAD_PORT, KEYPAD_C[i], GPIO_PIN_SET);
    }

    // If no button is pressed
    return 'N';
}

/*
void KEYPAD_init(void){


	//	KEYPAD_DataDir_PORTD &= ~((1<<R0) | (1<<R1) | (1<<R2) | (1<<R3));
	//KEYPAD_DataDir_PORTD |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));

	//KEYPAD_PORTD |= 0xFF;


	//Rows (B0,B1,B3,B4)
	//configuring higher pins(Rows) in keypad as Input(PULL-UP)

	//	int i = 0;

	/*
	keypadpinCfg.GPIO__PinNumber = KEYPAD_R[0];
	keypadpinCfg.GPIO_MODE = GPIO_CONFIG_Floating_Input;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);


	keypadpinCfg.GPIO__PinNumber = KEYPAD_R[1];
	keypadpinCfg.GPIO_MODE = GPIO_CONFIG_Floating_Input;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);
	keypadpinCfg.GPIO__PinNumber = KEYPAD_R[2];
	keypadpinCfg.GPIO_MODE = GPIO_CONFIG_Floating_Input;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);

	keypadpinCfg.GPIO__PinNumber = KEYPAD_R[3];
	keypadpinCfg.GPIO_MODE = GPIO_CONFIG_Floating_Input;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);


	//columns(B5,B6,B7,B8)
			//configuring lower pins(columns) in keypad as output(PUSH_PULL)

	keypadpinCfg.GPIO__PinNumber = KEYPAD_C[0];
	keypadpinCfg.GPIO__PinNumber = GPIO_General_purpose_output_push_pull;
	keypadpinCfg.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);


	keypadpinCfg.GPIO__PinNumber = KEYPAD_C[1];
	keypadpinCfg.GPIO__PinNumber = GPIO_General_purpose_output_push_pull;
	keypadpinCfg.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);

	keypadpinCfg.GPIO__PinNumber = KEYPAD_C[2];
	keypadpinCfg.GPIO__PinNumber = GPIO_General_purpose_output_push_pull;
	keypadpinCfg.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);

	keypadpinCfg.GPIO__PinNumber = KEYPAD_C[3];
	keypadpinCfg.GPIO__PinNumber = GPIO_General_purpose_output_push_pull;
	keypadpinCfg.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(KEYPAD_DataDir_PORTB, &keypadpinCfg);

	//set columns  high


	MCAL_GPIO_WritePin(KEYPAD_PORTB, KEYPAD_C[0] , GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORTB, KEYPAD_C[1] , GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORTB, KEYPAD_C[2] , GPIO_PIN_SET);
	MCAL_GPIO_WritePin(KEYPAD_PORTB, KEYPAD_C[3] , GPIO_PIN_SET);

 */
/*



	keypad.GPIO__PinNumber = GPIO__Pin0;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin1;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin3;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin4;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin5;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin6;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);

	keypad.GPIO__PinNumber = GPIO__Pin7;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);
	keypad.GPIO__PinNumber = GPIO__Pin8;
	keypad.GPIO_MODE = GPIO_General_purpose_output_push_pull;
	keypad.GPIO_SPEED = GPIO_SPEED10;
	MCAL_GPIO_INIT(GPIOB, &keypad);


	MCAL_GPIO_WritePort(GPIOB, (0xff<<0));

	/*	 MCAL_GPIO_WritePin(GPIOB, GPIO__Pin5 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, GPIO__Pin6 , GPIO_PIN_SET);

		MCAL_GPIO_WritePin(GPIOB, GPIO__Pin7 , GPIO_PIN_SET);
		MCAL_GPIO_WritePin(GPIOB, GPIO__Pin8 , GPIO_PIN_SET);*//*
}


char KEYPAD_GETCHAR(){

	unsigned char i = 0 , j = 0 , k = 0;
	for(i=0 ; i<4 ; i++){
		//Turning on all columns
		//KEYPAD_PORTD |= ((1<<C0) | (1<<C1) | (1<<C2) | (1<<C3));

			MCAL_GPIO_WritePin(GPIOB, KEYPAD_C[0], GPIO_PIN_SET);
			MCAL_GPIO_WritePin(GPIOB, KEYPAD_C[1], GPIO_PIN_SET);
			MCAL_GPIO_WritePin(GPIOB, KEYPAD_C[2], GPIO_PIN_SET);
			MCAL_GPIO_WritePin(GPIOB, KEYPAD_C[3], GPIO_PIN_SET);


			//		MCAL_GPIO_WritePin(KEYPAD_PORT, KEYPAD_C[k], GPIO_PIN_SET);


		//Turning off each column to check which (button/number) pressed
		MCAL_GPIO_WritePin(GPIOB, KEYPAD_C[i], GPIO_PIN_RESET);
		wait_msk(5);
		//KEYPAD_PORTD &= ~(1<<KEYPAD_C[i]);


		//checking which button pressed by looping on each Row
		for( j = 0 ; j < 4 ; j++ ){



			if(  MCAL_GPIO_ReadPin(GPIOB, KEYPAD_R[j]) == 0)
			{

				//For single Press
				while(MCAL_GPIO_ReadPin(GPIOB, KEYPAD_R[j]) == 0);
		        wait_msk(5);

				switch(i){

				case 0 :
					if(j == 0){return '7';}
					else if(j == 1){return '4';}
					else if(j == 2){return '1';}
					else if(j == 3){return '!';}

					break;

				case 1 :
					if(j == 0){return '8';}
					else if(j == 1){return '5';}
					else if(j == 2){return '2';}
					else if(j == 3){return '0';}
					break;

				case 2 :
					if(j == 0){return '9';}
					else if(j == 1){return '6';}
					else if(j == 2){return '3';}
					else if(j == 3){return '=';}
					break;

				case 3 :
					if(j == 0){return '/';}
					else if(j == 1){return '*';}
					else if(j == 2){return '-';}
					else if(j == 3){return '+';}
					break;

				}

			}

		}
	}



	//IF user didn't press on any button
	return 'N';


//}
		 */
