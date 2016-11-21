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
#include <libc/stdio/scank/scank.h>
#include <libc/stdlib/atoi/atoi.h>
#include <misc/asm_util.h>

volatile uint32_t index_scank;
volatile bool active_scank;
volatile char buffer_scank[];

int scank(const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    int* integer_format;
    char** string_format;
    char* char_format;

    for(int i=0;fmt[i]!='\0';i++)
    {
      if(!(fmt[i] == '%')) continue;
      else
      {
        switch(fmt[i+1])
        {
          case 'd':
           for(int i=0; i<index_scank; i++)
                buffer_scank[i] = 0;
            integer_format = va_arg(arg,int*);
            active_scank = true;
            index_scank=0 ;
            while(active_scank == true) hlt();
            *integer_format = atoi(buffer_scank);
            break;
           case 's':
             for(int i=0; i<index_scank; i++)
                buffer_scank[i] = 0;
             string_format = va_arg(arg,char**);
             active_scank = true;
             index_scank=0 ;
             while(active_scank == true) hlt();
             *string_format = buffer_scank;
            break;
           case 'c':
             char_format = va_arg(arg,char*);
             active_scank = true;
             index_scank=0 ;
             while(active_scank == true) hlt();
             *char_format = buffer_scank;
             break;
            case 'x':
              break;   
        }
      }  
    }
    va_end(arg);
    return 0;
}