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

#include <drv/video/VGA/textmode/80x25/utils.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

size_t terminal_column=0;
size_t terminal_row=0;
uint8_t FG = 0x7; // Foreground - White
uint8_t BG = 0x0; // Background - BLACK 
const size_t VGA_WIDTH = 80;
const size_t VGA_HEIGHT = 25; 
extern void term_scroll(int offset);


/*
 * @function putch_vga_80_x_25:
 *    Puts a single character
 *    on the screen.
 *
 *      @param c:
 *          character to put on
 *          the screen
 */

void putch_vga_80_x_25(char c)
{
  const size_t index =  (terminal_row * 80 +  terminal_column);
  uint16_t* VideoMemory = (uint16_t*)0xB8000;
  uint8_t terminal_color = make_color(FG,BG);
  
  VideoMemory[index] = make_vgaentry(' ', terminal_color);
  VideoMemory[index+1] = make_vgaentry(' ', terminal_color);

  VideoMemory[index]= (VideoMemory[index] & 0xFF00)|c;
  terminal_column++;
  if(terminal_row>25)
  {
    term_scroll(2);
  }
}
