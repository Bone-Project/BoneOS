/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/  
#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <libc/stdio/printf/printf.h>
#include <arch/cpu/i386/interrupts/interrupts.h>




static const char *exception_messages[32] = {
    "Division by zero","Debug","Non-maskable interrupt",
    "Breakpoint","Detected overflow","Out-of-bounds",
    "Invalid opcode","No coprocessor","Double fault",
    "Coprocessor segment overrun","Bad TSS",
    "Segment not present","Stack fault",
    "General protection fault","Page fault","Unknown interrupt",
    "Coprocessor fault","Alignment check","Machine check",
    "Reserved","Reserved","Reserved","Reserved","Reserved",
    "Reserved","Reserved","Reserved","Reserved","Reserved",
    "Reserved","Reserved","Reserved"
};

typedef struct 
{
    uint16_t ds; /*Segment the current routine is running in*/
    uint32_t edx, ecx, eax;/*Regisers pushed*/
    uint32_t int_no, err_code; /*Error Code and Number of exception*/
}int_regs;





//Routine Handlers for Exceptions
extern void isr0(void);
extern void isr1(void);
extern void isr2(void);
extern void isr3(void);
extern void isr4(void);
extern void isr5(void);
extern void isr6(void);
extern void isr7(void);
extern void isr8(void);
extern void isr9(void);
extern void isr10(void);
extern void isr11(void);
extern void isr12(void);
extern void isr13(void);
extern void isr14(void);
extern void isr15(void);
extern void isr16(void);
extern void isr17(void);
extern void isr18(void);
extern void isr19(void);
extern void isr20(void);
extern void isr21(void);
extern void isr22(void);
extern void isr23(void);
extern void isr24(void);
extern void isr25(void);
extern void isr26(void);
extern void isr27(void);
extern void isr28(void);
extern void isr29(void);
extern void isr30(void);
extern void isr31(void);


void init_isr()
{
    idt_set_gate(0, isr0, 0x08, 0x8e);
    idt_set_gate(1, isr1, 0x08, 0x8e);
    idt_set_gate(2, isr2, 0x08, 0x8e);
    idt_set_gate(3, isr3, 0x08, 0x8e);
    idt_set_gate(4, isr4, 0x08, 0x8e);
    idt_set_gate(5, isr5, 0x08, 0x8e);
    idt_set_gate(6, isr6, 0x08, 0x8e);
    idt_set_gate(7, isr7, 0x08, 0x8e);
    idt_set_gate(8, isr8, 0x08, 0x8e);
    idt_set_gate(9, isr9, 0x08, 0x8e);
    idt_set_gate(10, isr10, 0x08, 0x8e);
    idt_set_gate(11, isr11, 0x08, 0x8e);
    idt_set_gate(12, isr12, 0x08, 0x8e);
    idt_set_gate(13, isr13, 0x08, 0x8e);
    idt_set_gate(14, isr14, 0x08, 0x8e);
    idt_set_gate(15, isr15, 0x08, 0x8e);
    idt_set_gate(16, isr16, 0x08, 0x8e);
    idt_set_gate(17, isr17, 0x08, 0x8e);
    idt_set_gate(18, isr18, 0x08, 0x8e);
    idt_set_gate(19, isr19, 0x08, 0x8e);
    idt_set_gate(20, isr20, 0x08, 0x8e);
    idt_set_gate(21, isr21, 0x08, 0x8e);
    idt_set_gate(22, isr22, 0x08, 0x8e);
    idt_set_gate(23, isr23, 0x08, 0x8e);
    idt_set_gate(24, isr24, 0x08, 0x8e);
    idt_set_gate(25, isr25, 0x08, 0x8e);
    idt_set_gate(26, isr26, 0x08, 0x8e);
    idt_set_gate(27, isr27, 0x08, 0x8e);
    idt_set_gate(28, isr28, 0x08, 0x8e);
    idt_set_gate(29, isr29, 0x08, 0x8e);
    idt_set_gate(30, isr30, 0x08, 0x8e);
    idt_set_gate(31, isr31, 0x08, 0x8e);
    printf("INITALIZED ISR");
}

extern void common_interrupt_exception_handler(int_regs* regs)
{
    if(regs->int_no < 32)
        printf("ERROR : %s" , exception_messages[regs->int_no]);
    else
        printf("UNDOCUMENTED ERROR");

    for( ; ; ) __asm__ __volatile__ ("hlt");
}