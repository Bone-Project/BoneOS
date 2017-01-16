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

//All Drivers
struct device_driver_t *drivers[] =
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
void setup_driver_handler(void)
{
    /*Initalize and Uninitalize functions for Video Driver*/
    video_driver.init = video_drivers[VGA_VIDEO_DRIVER_INDEX]->init;
    video_driver.uninit = video_drivers[VGA_VIDEO_DRIVER_INDEX]->uninit;
    video_driver.status = video_drivers[VGA_VIDEO_DRIVER_INDEX]->status;

    init_all_drivers();
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
int init_all_drivers(void)
{
    for(uint32_t i = 0; drivers[i]; i++)
        init_device_driver(i);
    return 0;
}

//unintalize all device drivers
int uninit_all_drivers(void)
{
    for(uint32_t i = 0; drivers[i]; i++)
        uninit_device_driver(i);
    return 0;
}
