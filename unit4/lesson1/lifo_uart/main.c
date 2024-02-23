
/*
 * main.c
 *
 *  Created on: Feb 22, 2024
 *      Author: 3m.B
 */
#include "lifo.h"
unsigned int buffer[5];
int main(void){

    lifo_buf_t uart_lifo;
    int i;
    unsigned int temp = 0;
LIFO_init(&uart_lifo,buffer,5);
    for (i = 0; i < 5; i++){
        if (lifo_add(&uart_lifo, i) == LIFO_NO_ERROR)
        		{printf("uart_lifo add :%d \n", i);}
    }
    printf("\n");
    for (i = 0; i < 5; i++){
        if (lifo_get(&uart_lifo, &temp) == LIFO_NO_ERROR){
            printf("uart_lifo get :%d \n", temp);}
    }
}

