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
 **     Doug Gale <doug65536> : update to printk
 **/  

#include <arch/cpu/i386/interrupts/interrupts.h>
#include <arch/cpu/i386/interrupts/irq.h>
#include <io/i386/io.h>
#include <libc/stdio/stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <drv/i386/kbd/kbd.h>

inline static uint8_t kbd_ctrl_read_status()
{
	return (inb8(I386_KBD_ONBOARD_PORT_READ));
}

void send_cmd_kbd_ctrl(uint8_t cmd)
{
	while(1)
		if((kbd_ctrl_read_status() & INPUT_BUFFER_FULL) ==0) break;

	outb8(I386_KBD_ONBOARD_PORT_WRITE,cmd);
}

void kbd_handler(int_regs *r)
{
 printk("KBD HIT");
}

void init_kbd()
{
 install_irq_handler(1,kbd_handler);	
}