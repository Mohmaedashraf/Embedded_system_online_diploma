#include "linked.h"
struct Sstudent* gpfirststudent=NULL;

void add_student() {
	struct Sstudent* new_student;
	struct Sstudent* last_student;

	if (gpfirststudent == NULL) {
		new_student = (struct Sstudent*)malloc(sizeof(struct Sstudent));
		gpfirststudent = new_student;
	} else {
		last_student = gpfirststudent;
		while (last_student->PNextstudent) {
			last_student = last_student->PNextstudent;
		}

		new_student = (struct Sstudent*)malloc(sizeof(struct Sstudent));
		last_student->PNextstudent = new_student;
	}

	fill_recorcd(new_student);
	new_student->PNextstudent = NULL;
}

void fill_recorcd(struct Sstudent* new_student){
	char temp_text[40];
	DPRINTF("\n enter the student ID :");
	gets(temp_text);
	new_student->student.ID=atoi(temp_text);
	DPRINTF("\n enter the student Name :");
	gets(new_student->student.name);
	DPRINTF("\n enter the student Height :");
	gets(temp_text);
	new_student->student.height=atof(temp_text);
}
int delet_student() {
	char temp_text[40];
	int selected_id;
	DPRINTF("\n enter the student ID you want to delete:\n");
	gets(temp_text);
	selected_id = atoi(temp_text);

	if (gpfirststudent) {
		struct Sstudent* previous_student = NULL;
		struct Sstudent* current_student = gpfirststudent;

		while (current_student) {
			if (current_student->student.ID == selected_id) {
				if (previous_student) {
					previous_student->PNextstudent = current_student->PNextstudent;
				} else {
					gpfirststudent = current_student->PNextstudent;
				}

				free(current_student);
				DPRINTF("\n Student with ID %d deleted successfully.", selected_id);
				return 1;
			}

			previous_student = current_student;
			current_student = current_student->PNextstudent;
		}
	}

	DPRINTF("\n Cannot find student with ID %d", selected_id);
	return 0;
}

void view_student(){
	int count=0;
	struct Sstudent* current_student=gpfirststudent;
	if(gpfirststudent==NULL)
		DPRINTF("\n list is empty");
	while(current_student){
		DPRINTF("\n\n record number : %d",count+1);
		DPRINTF("\n student ID :%d",current_student->student.ID);
		DPRINTF("\n student name :%s",current_student->student.name);
		DPRINTF("\n student height :%f",current_student->student.height);
		current_student=current_student->PNextstudent;
		count++;
	}
}
void delete_all(){
	struct Sstudent* current_student = gpfirststudent;

	if (gpfirststudent == NULL)
		DPRINTF("\n list is empty");

	while (current_student) {
		struct Sstudent* temp_student = current_student;
		current_student = current_student->PNextstudent;
		free(temp_student);
	}

	gpfirststudent = NULL;
}
int student_index()
{
	char temp[40];
	DPRINTF("please enter the index : ");
	gets(temp);
	int select_index;
	select_index=atoi(temp);
	int count =1;
	struct Sstudent* current_student=gpfirststudent;
	if (gpfirststudent == NULL){
		DPRINTF("\n list is empty");
		return 0;
	}
	while(count!=select_index){
		current_student=current_student->PNextstudent;
		count++;

	}
	if(count==select_index){
		DPRINTF("\n the data of student is :");
		DPRINTF("\n\n record number : %d",count);
		DPRINTF("\n student ID :%d",current_student->student.ID);
		DPRINTF("\n student name :%s",current_student->student.name);
		DPRINTF("\n student height :%f",current_student->student.height);
	}else{
		DPRINTF("\n cannot find the student that have index :%d",select_index);
	}
}
int length_studentdata() {
	if (gpfirststudent == NULL) {
		DPRINTF("\n list is empty");
		return 0;
	}

	int count = 0;
	struct Sstudent* current_student = gpfirststudent;

	while (current_student) {
		count++;
		current_student = current_student->PNextstudent;
	}

	DPRINTF("\n the number of data student: %d", count);
	return count;
}
void reverse_index() {
    DPRINTF("\n the student with reverse index :");
    int count = length_studentdata(); // Assume you have a function to get the length

    while (count > 0) {
        struct Sstudent* current_student = gpfirststudent;
        int current_count = 1;

        while (current_count < count) {
            current_student = current_student->PNextstudent;
            current_count++;
        }

        DPRINTF("\n\n record number : %d", count);
        DPRINTF("\n student ID : %d", current_student->student.ID);
        DPRINTF("\n student name : %s", current_student->student.name);
        DPRINTF("\n student height : %f", current_student->student.height);

        count--;
    }
}
