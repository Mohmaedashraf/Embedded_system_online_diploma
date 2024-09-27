#ifndef LINKED_H_
#define LINKED_H_
#define DPRINTF(...)	{fflush(stdout); \
		fflush(stdin); \
		printf(__VA_ARGS__); \
		fflush(stdout); \
		fflush(stdin);}

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "conio.h"
struct Sdata{
	int ID ;
	char name[50];
	float height;
};
struct Sstudent{
	struct Sdata student;
	struct Sstudent* PNextstudent;
};

void add_student();
void fill_recorcd(struct Sstudent* new_student);
int delet_student();
void view_student();
void delete_all();
int student_index();
int length_studentdata();
void reverse_index();




#endif
