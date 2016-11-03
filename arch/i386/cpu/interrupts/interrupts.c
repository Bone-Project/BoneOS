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
#include <io/i386/io.h>
#include <libc/stdio/printk/printk.h>
#include <arch/cpu/i386/interrupts/interrupts.h>
#include <arch/cpu/i386/interrupts/isr.h>
#include <arch/cpu/i386/interrupts/irq.h>
#include <arch/cpu/i386/interrupts/pic.h>

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
		printk("ERROR : %s" , exception_messages[regs->int_no]);
		for( ; ; ) __asm__ __volatile__ ("cli \n\t hlt");
	}
	else if(regs->int_no >= 32 && regs->int_no<48)
	{
		int_routines handler = irq_routines[(regs->int_no)-32];
		if(handler)
			handler(regs);
	}
	else
		printk("UNDOCUMENTED ERROR");

	if(regs->int_no >= 8)
		outb8(I386_MASTER_REG_COMMAND,PIC_EOI);

	outb8(I386_SLAVE_REG_COMMAND,PIC_EOI);

}