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
 * @function pcspkr_beep :
 *    Makes the PC Speaker
 *    beep.
 */
int pcspkr_beep()
{
  //TODO: IMPLEMENT
  if(pcspkr_driver.initalized == true)
    printk("PC Speaker BEEP Fired\n");
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
