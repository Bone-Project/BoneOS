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

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>


extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK
extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;

void cls()    
{
  uint16_t* VideoMemory = (uint16_t*)0xB8000;
  terminal_column=0;
  terminal_row=0;
  char space = ' ';
  for(int i=0; i<=80; i++)
  {
    for(int y=0; y<=125; y++)
    {
       const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);   
       terminal_column++;
  
       VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
    }
  
  }
  for(int i=0; i<=80; i++)
  {
    for(int y=0; y<=125; y++)
    {
      const size_t index =  (terminal_row * VGA_WIDTH +  terminal_column);
      terminal_column--;

      VideoMemory[index]= (VideoMemory[index] & 0xFF00)|space;
    }
  }
}