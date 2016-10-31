#ifndef _ARCH_CPU_INTERRUPTS_H_
#define _ARCH_CPU_INTERRUPTS_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

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

 extern void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,uint8_t flags);
 #endif