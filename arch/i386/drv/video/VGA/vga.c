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
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/80x25/putch/putch.h>

struct video_driver_t vga_driver = 
{
   #if VIDEO_MODE == TEXTMODE
    .mode = TEXT_MODE,
    .put_pixel = 0,
  #endif
     .res.w = ACTIVE_RES_W,
     .res.h = ACTIVE_RES_H,
     .init =  &init_vga_driver,
     .uninit = &uninit_vga_driver,
     .status = STATUS_DRIVER_OK
};

void set_mode_util(putch_t putch_v, put_pixel_t put_pixel_v, clear_t clear_v, update_cursor_t update_cursor_v)
{
  vga_driver.putch = putch_v;
  vga_driver.put_pixel = put_pixel_v;
  vga_driver.clear = clear_v;
  vga_driver.update_cursor = update_cursor_v;
}

int uninit_vga_driver()
{
  set_mode_util(0,0,0,0);
  return STATUS_OK;
}

int init_vga_driver()
{
     #if VIDEO_MODE == TEXTMODE && ACTIVE_RES_W == 80 && ACTIVE_RES_H == 25
     
        set_mode_util(
                       vga_textmodes_arr[eighty_twentyfive_TEXTMODE_INDEX]->putch,
                       0,
                       vga_textmodes_arr[eighty_twentyfive_TEXTMODE_INDEX]->clear,
                       vga_textmodes_arr[eighty_twentyfive_TEXTMODE_INDEX]->update_cursor
                     );
                      
        vga_driver.name = vga_textmodes_arr[eighty_twentyfive_TEXTMODE_INDEX]->name;
        
     #endif
     return STATUS_OK;   
}


