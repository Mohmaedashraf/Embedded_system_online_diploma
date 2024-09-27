
#include "linked.h"
int main(){
	char temp[10];
	while(1){
		DPRINTF("\tSELECT YOUR OPTION\n");
		DPRINTF("1:Add Student\n");
		DPRINTF("2:Delete Student\n");
		DPRINTF("3:print All Student\n");
		DPRINTF("4:Delete All Student\n");
		DPRINTF("5:print Student using index\n");
		DPRINTF("6:print length of student database\n");
		DPRINTF("7:print student with reverse index\n");
		DPRINTF("\n  Enter option number: ");
		gets(temp);
		DPRINTF("\n");
		switch(atoi(temp))
		{
		case 1:
			add_student();
			break;
		case 2:
			delet_student();
			break;
		case 3:
			view_student();
			break;
		case 4:
			delete_all();
			break;
		case 5:
			student_index();
			break;
		case 6:
			length_studentdata();
			break;
		case 7:
			reverse_index();
			break;
		default:
			DPRINTF("\t\"WRONG OPTION PLEASE TRY AGAIN\"\n");
			break;
		}
		DPRINTF(" \n============================================\n");
	}
	return 0;
}
