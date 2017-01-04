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

#include <io/io.h>
#include <misc/status_codes.h>
#include <drv/video/VGA/textmode/clear.h>
#include <drv/video/VGA/textmode/putch.h>
#include <drv/video/VGA/textmode/vga_textmode.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/term_scroll.h>
#include <drv/video/VGA/textmode/cursor.h>
#include <drv/video/video.h>
#include <stddef.h>
#include <stdint.h>




int init_vga_textmode()
{
  __textmode.w = video_driver_width;
  __textmode.h = video_driver_height;
  __textmode.name = video_driver_fullname;
  return STATUS_OK;
}

vga_textmode_t __textmode = 
{
  .clear = &clear_vga_textmode,
  .putch = &putch_vga_textmode,
  .update_cursor = &update_cursor_textmode,
  .scroll = &term_scroll_vga_textmode,
  .init = &init_vga_textmode
};

vga_textmode_t *vga_textmodes_arr[] = 
{
  &__textmode,
  0
};




