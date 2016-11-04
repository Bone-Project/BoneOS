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
 **		Amanuel Bogale <amanuel2> : start
 **/

#include <arch/cpu/i386/interrupts/interrupts.h>
#include <arch/cpu/i386/interrupts/irq.h>
#include <drv/i386/pit/pit.h>
#include <io/i386/io.h>
#include <libc/stdio/stdio.h>
#include <stdint.h>
#include <stddef.h>

uint32_t pit_ticks = 0;

inline void send_pit_command(uint8_t cmd)
{
	outb8(I386_PIT_COMMAND_REG, cmd);
}

inline void send_msg_counter_0(uint8_t cmd)
{
	outb8(I386_PIT_COUTNER_0,cmd);
}

void pit_phase(int htz)
{
	//IRQ 0 Hits every 10 milliseconds 
	//or 100 hertz
	int divisor = 1193180 / htz;

	send_pit_command(COMMAND_FULL);

	send_msg_counter_0(divisor & 0xFF);
	send_msg_counter_0(divisor >> 8);
}

void pit_handler(int_routines *r)
{
	pit_ticks++;
	printk("Spam");
}

void init_pit()
{
	pit_phase(19);
	install_irq_handler(0,(int_routines)pit_handler);
}
