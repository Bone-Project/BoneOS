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


#include <include/libc/stdio/printf/printf.h>
#include <include/libc/string/memset/memset.h>

/*
 * @function cls:
 *    Function for clearing
 *    the screen in normal text
 *    mode 32bit VGA.
 */

void cls()    
{
  printf("Hello This is from Fucntion cls(); YAY!!");
  //char buf[80*25+1];
  //memset(buf, ' ', 80*25);
  //buf[80*25] = 0; 
  //printf("%s", buf);
}