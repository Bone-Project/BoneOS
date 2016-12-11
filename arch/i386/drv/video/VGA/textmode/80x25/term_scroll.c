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
#include <memmove/memmove.h>
#include <memset/memset.h>
#include <stdio/stdio.h>
#include <stddef.h>

extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 


void term_scroll_vga_80_x_25(int offset)
{
    uint16_t *screen = (uint16_t*)0xB8000;
    for(int i = 0; i < 25; i++)
    {
        for (int m = 0; m < 80; m++)
        {
            const size_t index =  (i * 80 +  m);
            uint8_t terminal_color = make_color(FG,BG);

              screen[index] = make_vgaentry(' ', terminal_color);
              screen[index+1] = make_vgaentry(' ', terminal_color);

              screen[index]=  screen[(i + offset) * 80 + m] | (char)0;

            screen[index] = screen[(i + offset) * 80 + m]; 
        }
      }

  terminal_row -=offset;    
}
