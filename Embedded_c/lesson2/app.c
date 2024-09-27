#include"uart.h"
unsigned char string_buffer[100]="learn-in-depth:Mohamed";
void main(void){
uart_send_massage(string_buffer);
}