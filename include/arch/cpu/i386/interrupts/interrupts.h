#ifndef _ARCH_CPU_INTERRUPTS_H_
#define _ARCH_CPU_INTERRUPTS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

/*
 * PIC UTILITIES
 */
#define PIC_MASTER_CONTROL 0x20
#define PIC_SLAVE_CONTROL 0xA0
#define PIC_MASTER_MASK 0x21
#define PIC_SLAVE_MASK 0xA1

#define PIC_EOI 0x20

#ifndef IDT_SIZE
#define IDT_SIZE 256
#endif    


/*
 * @struct int_regs:
 *   Register getting pushed to 
 *   stack while calling routine
 *      @ds : Segment the current routine is running in
 *      @edx,@ecx,@eax :  General Purpose Regisers pushed
 *      @int_no @err_code : Error Code and ISR Number
 */

typedef struct 
{
    uint32_t ds; 
    uint32_t edx, ecx, eax;
    uint32_t int_no, err_code;
}__attribute__((packed)) int_regs;


typedef void(*regs_func)(int_regs *r);

/*
 * @struct idt_desc:
 *   Descriptor For an Interupt
 *   out of 256 interupts. 
 *      @base_lo : low 32 bit base addres for routine entry
 *      @sel : segment selector offset (0x8=CS)
 *      @reserved : Always 0.
 *      @flags :  Low 5 bits are 01110. Bits 5 and 6 
 *                is the DPL and bit 7 is the Present bit.
 *      @base_hi : High 32 bit base address for routine entry.
 */

 typedef struct 
 {
    uint16_t base_lo;
    uint16_t sel; // Kernel segment goes here.
    uint8_t  reserved;
    uint8_t flags; 
    uint16_t base_hi;
 }__attribute__((packed)) idt_desc;

 extern idt_desc idt[256];
 extern void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,uint8_t flags);
 #endif