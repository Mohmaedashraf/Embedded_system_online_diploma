/*
 * lifo.c
 *
 *  Created on: Feb 22, 2024
 *      Author: 3m.B
 */





#include "lifo.h"

lifo_status lifo_add(lifo_buf_t* buf1 , unsigned int item) {
    // lifo exist?
    if (!buf1->base || !buf1->head)
        return LIFO_NULL;
    // lifo full
    if (buf1->count >= buf1->length)
        return LIFO_full;
    *(buf1->head) = item;
    (buf1->head)++;
    (buf1->count)++;
    return LIFO_NO_ERROR ;
}

lifo_status lifo_get(lifo_buf_t* buf2, unsigned int* item) {
    // lifo exist?
    if (!buf2->base || !buf2->head)
        return LIFO_NULL;
    // lifo full
    if (buf2->count == 0)
        return LIFO_empty;
    (buf2->head)--;
    *item = *(buf2->head);
    (buf2->count)--;
    return LIFO_NO_ERROR;
}

lifo_status LIFO_init(lifo_buf_t* lifo_buf,unsigned int* buf,unsigned int length)
{
	if( buf == NULL )
		return LIFO_NULL;

	lifo_buf->base= buf;
	lifo_buf->head= buf;
	lifo_buf->length=length;
	lifo_buf->count=0;
	return LIFO_NO_ERROR;
}
