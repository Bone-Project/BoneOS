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

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <drv/ps2/kbd/kbd.h>

int scank(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    int integer_format;

    for(int i=0;fmt[i]!='\0';i++)
    {
      if(!(fmt[i] == '%')) continue;
      else
      {
        switch(fmt[i+1])
        {
          case 'd':
            integer_format = va_arg(arg,int);
            kbd_info.until_enter.active = true;
            while(kbd_info.until_enter.active == true);
            printk(">>> %s <<<" , kbd_info.until_enter.buffer);
            break;
           case 's':
            break;
           case 'c':
             break;
            case 'x':
              break;   
        }
      }  
    }
   

    va_end(arg);
}