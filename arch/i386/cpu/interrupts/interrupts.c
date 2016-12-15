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
#include <io/io.h>
#include <libc/stdio/printk/printk.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/isr.h>
#include <cpu/interrupts/irq.h>
#include <cpu/interrupts/pic.h>
#include <libc/stdlib/panik/panik.h>

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
		panik("ERROR : %s" , exception_messages[regs->int_no]);
	}
	else if(regs->int_no >= 32 && regs->int_no<48)
	{
		int_routines handler = irq_routines[(regs->int_no)-32];
		if(handler)
			handler(regs);
	}
	else
		printk("UNDOCUMENTED INTERRUPT");

	if(regs->int_no >= 32+8)
	{
		outb(I386_SLAVE_REG_COMMAND,PIC_EOI);
	}
	
	outb(I386_MASTER_REG_COMMAND,PIC_EOI);
}


