#include "stdio.h"
#include "stdint.h"
#ifndef FIFO_H_
#define FIFO_H_
#define element_type uint8_t
#define width 5
element_type buffer[width];
typedef struct{
	element_type length;
	element_type* base;
	element_type* head;
	element_type count;
	element_type* tail;

}FIFO_buf_t;
typedef enum{
	FIFO_NULL,
	FIFO_full,
	FIFO_empty,
	FIFO_NO_ERROR

}FIFO_status;
FIFO_status FIFO_init(FIFO_buf_t* fifo,element_type* buf,uint32_t length);
FIFO_status FIFO_enqueue(FIFO_buf_t* buf1,element_type item);
FIFO_status FIFO_dequeue(FIFO_buf_t* buf2,element_type* item);
FIFO_status FIFO_check(FIFO_buf_t* fifo);
void print_fifo(FIFO_buf_t* fifo);




#endif
