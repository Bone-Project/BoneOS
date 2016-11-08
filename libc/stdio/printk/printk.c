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
 **     Doug Gale <doug65536> : update to printk
 **/  

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#include <include/GlobalDefintions.h>
#include <include/com/i386/com.h>
#include <include/libc/stdio/printk/printk.h>
#if DISPLAY_ADAPTER == VGA && DISPLAY_ADAPTER_MODE == NORMAL_TEXT_MODE && com_met == SCREEN_DISPLAY
#include <include/screen/i386/VGA/textmode/putch/putch.h>
#endif
#include <include/libc/stdio/itoa/itoa.h>


/*
 * @function printf:
 *     Prints a string on
 *     on the string with
 *     format specifiers.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void printk(const char* fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  vprintk(fmt, arg);
  va_end(arg);
}

/*
 * @function vprintk:
 *     Prints string with
 *     a `va_list` instead
 *     of a variadic argument
 *     parameter. Used to supply
 *     the printk, and call printk
 *     with a va_list.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @va_list arg:
 *           formatting conversion
 *           utility in form of 
 *           `va_list`
 */

void vprintk(const char* fmt, va_list arg)
{
   int integer_format; 
   //float float_format;
   char *result_pt=" ";
  
   for(int i=0; fmt[i]!='\0';i++)
   {
     switch(fmt[i])
     {
        case '%':
          switch(fmt[i+1])
          {
            case 'd':
              integer_format = va_arg(arg,int);
              result_pt = itoa(integer_format);
              for(int x=0;result_pt[x]!='\0';x++)
                putch(result_pt[x]);
              i+=1;
              break;
            case 'c':
              putch(va_arg(arg,int));
              i+=1;
              break; 
            case 's':
              result_pt = va_arg(arg,char*);
              for(int x=0;result_pt[x]!='\0';x++)
                putch(result_pt[x]);  
              i+=1;
              break;   
            case 'x':
              integer_format = va_arg(arg,int);
              __itoa(integer_format, 16, result_pt);
              for(int x=0;result_pt[x]!='\0';x++)
                putch(result_pt[x]);
              i+=1;
              break;
            // case 'f':
            //   float_format = va_arg(arg,double);
            //   result_pt = itoa(float_format);
            //   for(int x=0;result_pt[x]!='\0';x++)
            //     putch(result_pt[x]);
            //   i+=1;
            //   break;  
          }
          break;
        case '\n':
          terminal_row++;
          terminal_column=0;
          break; 
        case '\b':
          terminal_column--;
          break;
        case '\t':
          for(int32_t t=0;t<=3;t++)terminal_column++;    
        default:
          putch(fmt[i]);
          break;       
     }
   }  
}