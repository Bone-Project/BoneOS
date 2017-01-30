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
#include <libc/stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/pcspkr/pcspkr.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>

//PC Speaker Driver Handler
struct device_driver_t pcspkr_driver =
{
    .name = "PC Speaker",
    .version = "STATUS_VERSION_NA",
    .init = &pcspkr_init,
    .uninit = &pcspkr_uninit
};

/*
 * @function send_msg_counter_2:
 *   Send message to Counter 2(Channel) ,
 *   where the PC Speaker is located ,
 *   for the 8254 PIC Intel Microcontroller.
 */
void send_msg_counter_2 (uint8_t cmd)
{
  outb(I386_PIT_COUNTER_2_REG,cmd);
}

/*
 * @function set_freq_pcspkr :
 *    Set the frequency of the
 *    PC Speaker.
 */
void set_freq_pcspkr (uint32_t freq)
{
  uint32_t __div;

  __div = I386_PIT_OSCILLATOR_CHIP_FREQ / freq;
 	outb(0x43, I386_PIT_OCW_BINCOUNT_BINARY |
             I386_PIT_OCW_MODE_SQUAREWAVEGEN |
             I386_PIT_OCW_RL_DATA |
             I386_PIT_OCW_SCO_COUNTER_2);
 	send_msg_counter_2((uint8_t)(__div));
 	send_msg_counter_2((uint8_t)(__div>>8));
}

void pc_speaker_silent()
{
  uint8_t pcspkr = inb(I86_PC_SPKR_STATUS_REG)&I86_PC_SPKR_DISABLE;
  outb(0x61,pcspkr);
}


/*
 * @function pcspkr_beep :
 *    Makes the PC Speaker
 *    beep.
 *    
 *    @param freq : Frequency given
 *                  for speaker to beep.
 */
int pcspkr_beep(uint32_t freq)
{
  //TODO: IMPLEMENT
  if(pcspkr_driver.initalized == true)
  {
    set_freq_pcspkr(freq);
    uint8_t pcspkr = inb(I86_PC_SPKR_STATUS_REG);
  	if (pcspkr != (pcspkr | I86_PC_SPKR_ENABLE)) //If PC_Speaker is not already set at out
 		   outb(0x61, pcspkr | I86_PC_SPKR_ENABLE);
  }
  else
    panik("PC SPEAKER Not Initalized or Uninitalized!");
  return STATUS_OK;
}
int pcspkr_init()
{
  pcspkr_driver.initalized = true;
  return STATUS_OK;
}

int pcspkr_uninit()
{
  pcspkr_driver.initalized = false;
  return STATUS_OK;
}
