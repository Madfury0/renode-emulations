#include <stdint.h>

#define SCB_CPACR (*(volatile uint32_t *) 0xE000EDE8)

/* External symbols from linker.ld*/
extern uint32_t _estack;
extern uint32_t _etext;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

/* Functions*/
void Reset_Handler(void);
void Default_Handler(void);
int main (void);

/* Vector table*/
__attribute__((section(".isr_vector")))
const void *vector_table[] = {
    (void *) &_estack,
    Reset_Handler
};

void Default_Handler (void){
    while(1);
}

/* Reset handler: initializes .data and .bss and then calls main*/
void Reset_Handler(){
    SCB_CPACR |= (0xF << 20); //enabling fpu
    __asm volatile ("dsb");
    __asm volatile ("isb");

    // copy data from flash to ram
    uint32_t *src = &_etext;
    uint32_t *dst = &_sdata;
    while (dst < &_edata)
        *dst++ = *src++;

    // zero .bss
    dst = &_sbss;
    while (dst < &_ebss)
        *dst++ = 0;

    /* call main*/
    main();
    while(1); // traps cpu if main returns
}
