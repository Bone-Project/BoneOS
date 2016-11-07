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
#include <libc/stdlib/stdlib.h>
#include <stdint.h>
#include <stddef.h>

uint32_t pit_ticks = 0;

/*
 * @function send_pit_command: 
 *    Sends Operation Command Word
 *    to PIT.
 */
inline void send_pit_command(uint8_t cmd)
{
	outb8(I386_PIT_CONTROL_WORD_REG, cmd);
}

/*
 * @function send_pit_command: 
 *    Sends Messages to Counter
 *	  0 of PIT's Internal Registers.
 */
inline void send_msg_counter_0(uint8_t cmd)
{
	outb8(I386_PIT_COUNTER_0_REG,cmd);
}

/*
 * @function send_pit_command: 
 *    Initalizes the PIT Intenally
 *	  with the number of IRQ's per
 *	  second specified.
 */
void pit_phase(int htz)
{
	//1.19MHz / htz
	//dictates how any times
	//the IRQ Should fire
	int divisor = 1193180 / htz;

	send_pit_command(I386_PIT_OCW_BINCOUNT_BINARY    | 
		 		     I386_PIT_OCW_MODE_SQUAREWAVEGEN |
		 		     I386_PIT_OCW_RL_DATA			 |
		 		     I386_PIT_OCW_SCO_COUNTER_0);

	send_msg_counter_0(divisor & 0xFF);
	send_msg_counter_0(divisor >> 8);
}

/*
 * @function pit_handler_nest :
 *    Functions that gets called
 *	  every time PIT IRQ Fires.
 *
 *      @return int:
 *			@if 0 == RETURN_OK
 *			@if !0 == RETURN_ERROR
 */
int pit_handler_nest()
{
	//TODO : Something to do every sec :).
	//printk("%d SECONDS\n", (pit_ticks/IRQ_SEC_HIT));
	return 0;
}

/*
 * @function pit_handler :
 *    Function that gets called
 *	  that calls the nested handler
 *	  if second pass.
 */
void pit_handler(int_regs *r)
{
	pit_ticks++;
	if (pit_ticks % IRQ_SEC_HIT == 0)
		if(pit_handler_nest()!=0) panik("PIT Handler Exception");
}

/*
 * @function init_pit:
 *    Initalizes the Programmable
 *	  interrupt controller, and installs
 *	  the IRQ For PIT.
 */
void init_pit()
{
	pit_phase(IRQ_SEC_HIT);
	install_irq_handler(IRQ_NUM_PIT,pit_handler);
}
