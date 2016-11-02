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

/*
 * @function irq_remap:
 *   Remaps the 8259 PIC.
 *   to IRQ's 32-47
 */

#include <io/i386/io.h>
#include <arch/cpu/i386/interrupts/interrupts.h>
#include <arch/cpu/i386/interrupts/pic.h>

void remap_pic_irq()
{
	outb8(I386_MASTER_REG_COMMAND,ICW1);
	outb8(I386_SLAVE_REG_COMMAND ,ICW1);

	outb8(I386_MASTER_REG_DATA,0x20); //0x20 = 32
	outb8(I386_SLAVE_REG_IMR,0x28); //0x28 = 47

	outb8(I386_MASTER_REG_DATA,0x04); //0x04 = 0100
	outb8(I386_SLAVE_REG_IMR ,0x02); //0x02 = 010

	outb8(I386_MASTER_REG_DATA,I386_PIC_ICW4_MASK_UPM); // 80x86 MODE
	outb8(I386_SLAVE_REG_IMR,I386_PIC_ICW4_MASK_UPM);  // 80x86 MODE

	//Null out data registers
	outb8(I386_MASTER_REG_DATA,0x0);
	outb8(I386_SLAVE_REG_IMR ,0x0);
}