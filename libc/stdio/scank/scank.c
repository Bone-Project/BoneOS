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
#include <libc/stdlib/strtoi/strtoi.h>
#include <libc/string/strcpy/strcpy.h>

volatile uint32_t index_scank;
volatile bool active_scank;
volatile bool print_scank;
volatile char buffer_scank[4096];
volatile int __backspace_count=0;
volatile bool __backspace_count_active=false;

/*
 * @function scank:
 *     Asks for user input
 *     for each of the format
 *     specifiers  
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @var_arg ...:
 *            formatting conversion
 *            utility.
 */

int scank(bool backspace_count,bool print , const char *fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
    vscank(backspace_count,print,fmt,arg);
    va_end(arg);
    return 0;
}

/*
 * @function vscank:
 *     Asks for user input
 *     with `va_list` instead,
 *     also supplied to scank.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @va_list arg:
 *            formatting conversion
 *            utility in form of 
 *            `va_list`
 */


void vscank(bool backspace_count,bool print ,const char *fmt , va_list arg)
{
    __backspace_count_active = backspace_count;
    print_scank = print;
    int* integer_format;
    char* string_format;
    char* char_format;
    int* hex_format;


    for(int i=0;fmt[i]!='\0';i++)
    {
      if(!(fmt[i] == '%')) continue;
      switch(fmt[i+1])
      {
          case 'd':
            integer_format = va_arg(arg,int*);
            active_scank = true;
            index_scank=0 ;
            while(active_scank == true) hlt();
            *integer_format = atoi((char*)buffer_scank);
            break;
           case 's':
             string_format = va_arg(arg,char*);
             active_scank = true;
             index_scank=0 ;
             buffer_scank[0] = 0;
             while(active_scank == true) hlt();
             strcpy(string_format,(char*)buffer_scank);
            break;
           case 'c':
             char_format = va_arg(arg,char*);
             active_scank = true;
             index_scank=0 ;
             while(active_scank == true) hlt();
             *char_format = buffer_scank[0];
             break;
           case 'x':
             hex_format = va_arg(arg,int*);
             active_scank = true;
             index_scank = 0;
             while(active_scank == true) hlt();
             *hex_format = strtoi((char*)buffer_scank, 0, 16);
              break;   
        }
      }  
  print_scank = false;
}