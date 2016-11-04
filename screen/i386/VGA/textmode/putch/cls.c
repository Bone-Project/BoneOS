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


#include <include/libc/stdio/printk/printk.h>
#include <include/libc/string/memset/memset.h>

extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 
extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT; 

void term_zero()
{
  terminal_row=0;
  terminal_column=0;
}

/*
 * @function cls:
 *    Function for clearing
 *    the screen in normal text
 *    mode 32bit VGA.
 */

void cls()    
{
  term_zero();
  char buf[80*25+1];
  memset(buf, ' ', 80*25);
  buf[80*25] = 0; 
  printk("%s", buf);
  term_zero();
}