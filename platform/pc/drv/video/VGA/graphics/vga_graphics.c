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
 
#include <misc/status_codes.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>
#include <drv/driver.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/graphics/graphics.h>
#include <string/string.h>


int init_graphics_mode() 
{
    video_driver_width = RES_1_WIDTH;
    video_driver_height = RES_1_HEIGHT;
    video_driver_mode = "GRAPHICS";
    
    setMode(RES_1_WIDTH,RES_1_HEIGHT,RES_1_COLORDEPTH);
    
    return STATUS_OK;
}