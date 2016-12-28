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
 **   Amanuel Bogale <amanuel2> : start
 **/

#include <cpu/interrupts/interrupts.h>
#include <misc/status_codes.h>
#include <cpu/interrupts/irq.h>
#include <libc/unistd/sleep/sleep.h>
#include <libc/stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>


volatile uint32_t pit_ticks = 0;

/*
 * @function send_pit_command: 
 *    Sends Operation Command Word
 *    to PIT.
 */
static void send_pit_command(uint8_t cmd)
{
  outb(I386_PIT_CONTROL_WORD_REG, cmd);
}

/*
 * @function send_pit_command: 
 *    Sends Messages to Counter
 *    0 of PIT's Internal Registers.
 */
static void send_msg_counter_0(uint8_t cmd)
{
  outb(I386_PIT_COUNTER_0_REG,cmd);
}

/*
 * @function send_pit_command: 
 *    Initalizes the PIT Intenally
 *    with the number of IRQ's per
 *    second specified.
 */
static void pit_phase(int htz)
{
  //1.19MHz / htz
  //dictates how any times
  //the IRQ Should fire
  int divisor = 1193180 / htz;

  send_pit_command( I386_PIT_OCW_BINCOUNT_BINARY     | 
                    I386_PIT_OCW_MODE_SQUAREWAVEGEN  |
                    I386_PIT_OCW_RL_DATA             |
                    I386_PIT_OCW_SCO_COUNTER_0);

  send_msg_counter_0(divisor & 0xFF);
  send_msg_counter_0(divisor >> 8);
}

/*
 * @function pit_handler_nest :
 *    Functions that gets called
 *    every time PIT IRQ Fires.
 *
 *      @return int:
 *      @if 0 == RETURN_OK
 *      @if !0 == RETURN_ERROR
 */
static int pit_handler_nest()
{
  //printk("%d SECONDS\n", (pit_ticks/IRQ_SEC_HIT));

  return 0;
}

/*
 * @function pit_handler :
 *    Function that gets called
 *    that calls the nested handler
 *    if second pass.
 */
static void pit_handler(int_regs *r)
{
  if(r){};
  pit_ticks++;
  if (pit_ticks % IRQ_SEC_HIT == 0)
       if(pit_handler_nest()!=0) 
              panik("PIT Handler Nest Exception");
}

/*
 * @function init_pit:
 *    Initalizes the Programmable
 *    interrupt controller, and installs
 *    the IRQ For PIT.
 */
int init_pit()
{
  pit_driver.initalized = true;
  pit_driver.status = STATUS_DRIVER_OK;
  pit_phase(IRQ_SEC_HIT);
  install_irq_handler(IRQ_NUM_PIT,pit_handler);
  return STATUS_OK;
}

int uninit_pit()
{
  pit_driver.initalized = false;
  uninstall_irq_handler(IRQ_NUM_PIT);
  return STATUS_OK;
}



