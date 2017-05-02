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

#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>
#include <misc/status_codes.h>
#include <drv/driver.h>
#include <assertk.h>
#include <stdint.h>
#include <stddef.h>


size_t video_driver_width = 320;
size_t video_driver_height = 200;
char* video_driver_name = "VGA";
char* video_driver_mode = "GRAPHICS";
char* video_driver_fullname = "VGA_TEXTMODE_320_x_200";


//Video Driver Handler
struct device_driver_t video_driver =
{
    .name = "Video Driver",
    .version = "STATUS_VERSION_NA"
};



struct video_driver_t *video_drivers[] =
{
    &vga_driver,
    0
};
