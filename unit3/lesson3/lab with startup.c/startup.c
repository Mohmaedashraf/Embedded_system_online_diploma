#include <stdint.h>

void default_handler();
extern int main(void);
void Reset_handler();
void NMI_handler() __attribute__ ((weak, alias("default_handler")));
void H_fault_handler() __attribute__ ((weak, alias("default_handler")));
void MM_fault_handler() __attribute__ ((weak, alias("default_handler")));
void Bus_fault() __attribute__ ((weak, alias("default_handler")));
void Usage_fault_handler() __attribute__ ((weak, alias("default_handler")));
 
 
 extern unsigned int stack_top ;
 
uint32_t vectors[] __attribute__ ((section(".vectors"))) = {
    (uint32_t) &stack_top,
    (uint32_t) &Reset_handler,
    (uint32_t) &NMI_handler,
    (uint32_t) &H_fault_handler,
    (uint32_t) &MM_fault_handler,
    (uint32_t) &Bus_fault,
    (uint32_t) &Usage_fault_handler,
};
extern unsigned int _E_text ;
extern unsigned int _S_data ;
extern unsigned int _E_data ;
extern unsigned int _S_bss ;
extern unsigned int _E_bss ;


void Reset_handler(){
unsigned int data_size = (unsigned char*)&_E_data - (unsigned char*)&_S_data;
unsigned char* p_src = (unsigned char*)&_E_text;
unsigned char* p_dis = (unsigned char*)&_S_data;
int i ;
for(i=0;i<data_size;i++)
	*((unsigned char*)p_src++)=*((unsigned char*)p_dis++);
unsigned int bss_size = 	(unsigned char*)&_E_bss - (unsigned char*)&_S_bss;
unsigned char* bss_src = (unsigned char*)&_S_bss;
for(i=0;i<bss_size;i++)
	*((unsigned char*)bss_src++)=(unsigned char)0;

main();
}

void default_handler() {
   Reset_handler();
   }