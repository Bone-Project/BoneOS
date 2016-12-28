#ifndef  _ARCH_CPU_INTERRUPTS_IDT_H
#define _ARCH_CPU_INTERRUPTS_IDT_H

/*
 * @IDT_SIZE : 256 Interrupt Descriptor tables
 */
#define IDT_SiZE 256

typedef void(*int_handler)(void);

/*
 * @struct idt_ptr : 
 *   Pointer to the Interupt Descriptor Table.
 *      @limit : Limit Of IDT which is 256-1 , since 
 *               start from index 0.
 *      @base : 32 Bit Full Base Address of IDT.
 */
 typedef struct 
 {
    uint16_t limit;
    uint64_t base;
 }__attribute__((packed)) idt_ptr;


extern void init_idt();

#endif /*_ARCH_CPU_INTERRUPTS_IDT_H*/



