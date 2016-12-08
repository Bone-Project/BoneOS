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
#include <drv/video/video.h>
#include <drv/ps2/kbd/kbd.h>
#include <misc/status_codes.h>
#include <assertk.h>

//Timer Driver Handler
struct device_driver pit_driver = 
{
   .name = "8253 Programmable Interval Timer",
   .init = &init_pit,
   .uninit = &uninit_pit,
   .version = "8253"
};

//Keyboard Driver Handler
struct device_driver kbd_driver = 
{
   .name = "8042 Keyboard PS/2 Driver",
   .init = &init_kbd,
   .uninit = &uninit_kbd,
   .version = "8042"
};

//Video Driver Handler
struct device_driver video_driver = 
{
  .name = "Video Driver",
  .version = "STATUS_VERSION_NA"
};

//All Drivers 
struct device_driver *drivers[] = 
{
    &pit_driver,
    &kbd_driver,
    &video_driver,
    0
};

/*
 * @function setup_driver_handler:
 *    First called (initalizer) before
 *    using device driver handler.
 *    Initalizes values for drivers.
 */
void setup_driver_handler()
{
  assertdokm(status_pit,"PIT MALFUNCTION");
  assertdokm(status_ps2_kbd,"PS2/KBD MALFUNCTION");
  assertdokm(video_drivers[VGA_VIDEO_DRIVER_INDEX]->status,"Video Driver MALFUNCTION");
  
  
  pit_driver.initalized = initalized_pit;
  pit_driver.status = status_pit;
  kbd_driver.initalized = initalized_ps2_kbd;
  kbd_driver.status = status_ps2_kbd;
  
  /*Initalize and Uninitalize functions for Video Driver*/
  video_driver.init = video_drivers[VGA_VIDEO_DRIVER_INDEX]->init;
  video_driver.uninit = video_drivers[VGA_VIDEO_DRIVER_INDEX]->uninit;
  video_driver.status = video_drivers[VGA_VIDEO_DRIVER_INDEX]->status;
}

//check if device is initalized
bool device_initalized(int index)
{
  return (drivers[index]->initalized);
}

//initalize device driver
int init_device_driver(uint32_t index)
{
  drivers[index]->init();
  return 0;
}

//uninitalize device driver
int uninit_device_driver(uint32_t index)
{
  drivers[index]->uninit();
  return 0;
}

//initalize all device drivers
int init_all_drivers()
{
  for(uint32_t i=0; drivers[i]; i++)
    drivers[i]->init();
  return 0;
}

//unintalize all device drivers
int uninit_all_drivers()
{
  for(uint32_t i=0; drivers[i]; i++)
    drivers[i]->uninit();
  return 0;
}