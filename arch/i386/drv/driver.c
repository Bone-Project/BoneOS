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

#include <stdint.h>
#include <stddef.h>
#include <drv/driver.h>
#include <drv/pit/pit.h>
#include <drv/ps2/kbd/kbd.h>


struct device_driver PIT_DRIVER = 
{
   .name = "8253 Programmable Interval Timer",
   .init = &init_pit,
   .uninit = &uninit_pit
};

struct device_driver KBD_DRIVER = 
{
   .name = "8042 Keyboard PS/2 Driver",
   .init = &init_kbd,
   .uninit = &uninit_kbd
};

struct device_driver *drivers[] = 
{
    &PIT_DRIVER,
    &KBD_DRIVER,
    0
};


int init_device_driver(uint32_t index)
{
  drivers[index]->init();
  return 0;
}

int uninit_device_driver(uint32_t index)
{
  drivers[index]->uninit();
  return 0;
}

int init_all_drivers()
{
  for(uint32_t i=0; drivers[i]; i++)
    drivers[i]->init();
  return 0;
}

