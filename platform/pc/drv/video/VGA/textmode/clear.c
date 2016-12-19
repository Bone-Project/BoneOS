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


#include <drv/video/VGA/textmode/putch.h>
#include <libc/string/memset/memset.h>
#include <drv/video/VGA/textmode/utils.h>
#include <drv/video/video.h>
#include <drv/video/VGA/vga.h>


void term_zero()
{
  vga_driver.video_row=0;
  vga_driver.video_column=0;
}

/*
 * @function cls:
 *    Function for clearing
 *    the screen in normal text
 *    mode 80x25 VGA.
 */


void clear_vga_textmode(void)    
{
  term_zero();
  for(unsigned i=0; i<video_driver_width; i++)
  {
    for(unsigned j=0; j<video_driver_height; j++)
    {
        const size_t index =  (vga_driver.video_row * 80 +  vga_driver.video_column);
        uint16_t* VideoMemory = (uint16_t*)0xB8000;
        uint8_t terminal_color = make_color(vga_driver.fg,vga_driver.bg);
        
        VideoMemory[index]= (VideoMemory[index] & 0xFF00)|(char)0;
        VideoMemory[index+1] = make_vgaentry(' ', terminal_color);

        vga_driver.video_column++;
    }
  }
  term_zero();
}

