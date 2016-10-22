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

#include <include/libc/i386/stdio/printf/printf.h>
#include <include/libc/i386/stdio/putchar/putchar.h>
#include <include/libc/i386/stdio/itoa/itoa.h>


size_t terminal_column=0;
size_t terminal_row=0;
uint8_t FG = 0x7; // Foreground - White
uint8_t BG = 0x0; // Background - BLACK  

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

void printf(const char* fmt, ...)
{
   va_list arg;

   va_start (arg, fmt);

   int integer_format; 
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
              for(int i=0;result_pt[i]!='\0';i++)
                putchar(result_pt[i]);
              i+=1;
              break;
            case 'c':
              putchar(va_arg(arg,int));
              i+=1;
              break; 
            case 's':
              result_pt = va_arg(arg,char*);
              for(int i=0;result_pt[i]!='\0';i++)
                putchar(result_pt[i]);  
              i+=1;
              break;   
            case 'x':
              integer_format = va_arg(arg,int);
              __itoa(integer_format, 16, result_pt);
              for(int i=0;result_pt[i]!='\0';i++)
                putchar(result_pt[i]);
              i+=1;
              break;
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
          putchar(fmt[i]);
          break;       
     }
   }  

   va_end (arg);
}