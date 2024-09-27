#include"fifo.h"
FIFO_status FIFO_init(FIFO_buf_t* fifo,element_type* buf,uint32_t length)
{
	if(fifo==NULL)
		return FIFO_NULL;
	if(FIFO_check(fifo)==FIFO_full)
		return FIFO_full;
	fifo->base=buf;
	fifo->head=buf;
	fifo->tail=buf;
	fifo->length=length;
	fifo->count=0;
	return FIFO_NO_ERROR;

}
FIFO_status FIFO_enqueue(FIFO_buf_t* buf1,element_type item)
{
	if(buf1==NULL)
		return FIFO_NULL;
	if(FIFO_check(buf1)==FIFO_full)
		return FIFO_full;
	*(buf1->head)=item;
	if(buf1->head==(buf1->base+(buf1->length*sizeof(element_type))))
		buf1->head=buf1->base;
	else
		buf1->head++;
	buf1->count++;
	return FIFO_NO_ERROR;
}
FIFO_status FIFO_dequeue(FIFO_buf_t* buf2,element_type* item)
{
	if(buf2==NULL)
		return FIFO_NULL;
	if(buf2->count==0)
		return FIFO_empty;
	*item=*(buf2->tail);

	if(buf2->tail==(buf2->base+(buf2->length*sizeof(element_type))))
		buf2->tail=buf2->base;
	else
		buf2->tail++;
	buf2->count--;
	return FIFO_NO_ERROR;

}
FIFO_status FIFO_check(FIFO_buf_t* fifo)
{
	if(fifo==NULL)
		return FIFO_NULL;
	if(fifo->count==fifo->length)
		return FIFO_full;
}
void print_fifo(FIFO_buf_t* fifo){
	element_type* temp;
	int i;
	if(fifo->count==0)
		printf("=======FIFO empty========\n");
	else{
		temp=fifo->tail;
		printf("====FIFO print=====\n");
		for(i=0;i<fifo->count;i++){
			printf("\t  %x  \n",*temp);
			temp++;
		}
		printf("========\n");
	}

}




