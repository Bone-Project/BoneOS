#ifndef _ARCH_CPU_INTERRUPTS_H_
#define _ARCH_CPU_INTERRUPTS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

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


typedef void(*int_routines)(int_regs *r);

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

#define CS_SEGMENT 0x8

/*IDT_FLAGS*/
 #define SEGMENT_PRESENT 0x8
 #define SEGMENT_RING_LEVEL_0 0x0
 #define SEGMENT_STORAGE 0x0
 #define SEGMENT_32_BIT_INTERUPT_GATE 0xE
 #define SEGMENT_PRESENT_DPL_STORAGE 0x8

 #define SEGMENT_FLAG SEGMENT_PRESENT | \
                                                  SEGMENT_RING_LEVEL_0 | \
                                                  SEGMENT_STORAGE | \
                                                  SEGMENT_32_BIT_INTERUPT_GATE | \
                                                  SEGMENT_PRESENT_DPL_STORAGE

 extern idt_desc idt[256];
 extern void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,uint8_t flags);
 #endif