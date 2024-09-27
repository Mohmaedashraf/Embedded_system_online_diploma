#include "fifo.h"

void main(){
	element_type i ,temp=0;
	FIFO_buf_t uart_fifo;
	if(FIFO_init(&uart_fifo,buffer,5)==FIFO_NO_ERROR)
		printf("-------FIFO init------\n");
	for(i=0;i<7;i++){
		printf("=====FIFO enqueue (%x)=====\n",i);
		if(FIFO_enqueue(&uart_fifo,i)==FIFO_NO_ERROR)
			printf("=====FIFO enqueue Done=====\n");
		else
			printf("=====FIFO enqueue failed=====\n");

	}
	print_fifo(&uart_fifo);
	if(FIFO_dequeue(&uart_fifo,&temp)==FIFO_NO_ERROR)
		printf("========fifo dqueue %x Done\n ",temp);
	if(FIFO_dequeue(&uart_fifo,&temp)==FIFO_NO_ERROR)
			printf("========fifo dqueue %x Done\n ",temp);

	print_fifo(&uart_fifo);


	}







