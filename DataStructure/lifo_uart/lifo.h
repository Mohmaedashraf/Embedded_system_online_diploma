
/*
 * lifo.h
 *
 *  Created on: Feb 22, 2024
 *      Author: 3m.B
 */

#ifndef LIFO_H_
#define LIFO_H_
#include <stdio.h>
#include <stdlib.h>
typedef struct{
	unsigned int length;
	unsigned int* base;
	unsigned int* head;
	unsigned int count;
}lifo_buf_t;
typedef enum{
	LIFO_NULL,
	LIFO_full,
	LIFO_empty,
	LIFO_NO_ERROR

}lifo_status;


lifo_status lifo_add(lifo_buf_t* buf1,unsigned int item);
lifo_status lifo_get(lifo_buf_t* buf2,unsigned int* item);
lifo_status LIFO_init(lifo_buf_t* lifo_buf,unsigned int* buf,unsigned int length);
#endif

