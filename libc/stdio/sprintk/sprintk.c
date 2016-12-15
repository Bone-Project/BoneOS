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

 **   Amanuel Bogale <amanuel2> : start
 **/   

#include <libc/stdlib/itoa/itoa.h>
#include <libc/stdio/sprintk/sprintk.h>
#include <stdint.h>
#include <stddef.h>
#include <stdarg.h>


/*
 * @function sprintk:
 *     Puts a formatted
 *     string into a 
 *     specified string
 *    
 *         @param buffer:
 *             the specified buffer
 *             where the formatted
 *             string will be placed.
 *
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void sprintk(char *buffer, const char *fmt, ...)
{
  va_list arg;
  va_start(arg, fmt);
  vsprintk(fmt,buffer,arg);
  va_end(arg);
}

/*
 * @function vsprintk:
 *     puts a string to specified
 *     buffer with a `va_list`
 *      instead of a variadic 
 *      argument parameter.
 *    
 *         @param fmt:
 *            orignial string with
 *            no formatting.
 *
 *         @param buffer:
 *             the specified buffer
 *             where the formatted
 *             string will be placed.
 *
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void vsprintk(const char* fmt, char* buffer, va_list arg)
{
  int integer_format; 
  char *result_pt=" ";
  for(int i=0; fmt[i]!='\0'; i++)
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
                 buffer[i] = result_pt[x];
               i+=1;
             break;
           case 's':
            result_pt = va_arg(arg,char*);
              for(int x=0;result_pt[x]!='\0';x++)
                buffer[i] = result_pt[x];  
               i+=1;
             break;
           case 'c':
             buffer[i] = va_arg(arg,int);
               i+=1;
             break;
           case 'x':
             integer_format = va_arg(arg,int);
               __itoa(integer_format, 16, result_pt);
               for(int x=0;result_pt[x]!='\0';x++)
                 buffer[i] = result_pt[x];
               i+=1;
             break;    
         }
         break;
      default:
         buffer[i]=fmt[i];
         break;   
    }
  }
}


