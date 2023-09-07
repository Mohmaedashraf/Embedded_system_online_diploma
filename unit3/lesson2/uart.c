#include"uart.h"
#define UART0DR *((volatile unsigned int*)((unsigned int*)0x101f1000))
void uart_send_massage(unsigned char* pst){
while(*pst!=0){
UART0DR=(unsigned int)*pst;
pst++;
}
}