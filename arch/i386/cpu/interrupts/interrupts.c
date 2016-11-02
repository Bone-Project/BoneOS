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


#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <libc/stdio/printf/printf.h>
#include <arch/cpu/i386/interrupts/interrupts.h>
#include <arch/cpu/i386/interrupts/isr.h>


void idt_set_gate(uint8_t num, void(*handler)(void), uint16_t sel,
              uint8_t flags) 
{
    idt[num].base_lo = (uintptr_t)handler >> 0 & 0xFFFF;
    idt[num].base_hi = (uintptr_t)handler >> 16 & 0xffff;
    idt[num].reserved = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

/*
 * @extern @function interupt_handler:
 *      The Interrupt Handler for all
 *      types of exceptions listed
 *      above on exception_messages.
 */

extern void interupt_handler(int_regs* regs)
{
	if(regs->int_no < 32)
	{
		printf("ERROR : %s" , exception_messages[regs->int_no]);
	}
	else if(regs->int_no >= 32 && regs->int_no<48)
	{
		printf("IRQ");
	}
	else
		printf("UNDOCUMENTED ERROR");

    for( ; ; ) __asm__ __volatile__ ("hlt");
}