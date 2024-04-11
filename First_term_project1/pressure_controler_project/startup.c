#include <stdint.h>
#define STACK_START 0x20001000

extern int main(void);

void Reset_Handler(void);

void Default_Handler()
{
    Reset_Handler();
}

void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void H_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void MM_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Bus_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));
void Usage_fault_Handler(void) __attribute__((weak, alias("Default_Handler")));

extern unsigned char _stack_top;
uint32_t vectors[] __attribute__((section(".vectors"))) = {
    (uint32_t)&_stack_top,
    (uint32_t)&Reset_Handler,
    (uint32_t)&NMI_Handler,
    (uint32_t)&H_fault_Handler,
    (uint32_t)&MM_fault_Handler,
    (uint32_t)&Bus_fault_Handler,
    (uint32_t)&Usage_fault_Handler,
};

// not actual variables, only symbols, to access add & before
extern unsigned char _E_text;
extern unsigned char _S_DATA;
extern unsigned char _E_DATA;
extern unsigned char _S_bss;
extern unsigned char _E_bss;

void Reset_Handler(void)
{
    // copy data from ROM to RAM
    unsigned int DATA_size = (unsigned char *)&_E_DATA - (unsigned char *)&_S_DATA;
    unsigned char *P_src = (unsigned char *)&_E_text;
    unsigned char *P_dst = (unsigned char *)&_S_DATA;

    unsigned int i;  // Declare 'i' outside the 'for' loop

    for (i = 0; i < DATA_size; i++)
    {
        *((unsigned char *)P_dst++) = *((unsigned char *)P_src++);
    }

    // init bss with zeros
    unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss;
    P_dst = (unsigned char *)&_S_bss;

    for (i = 0; i < bss_size; i++)  // Use the existing 'i' variable
    {
        *((unsigned char *)P_dst++) = (unsigned char)0;
    }

    // jump to main
    main();
}