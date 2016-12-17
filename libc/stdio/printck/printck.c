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

#include <GlobalDefintions.h>
#include <libc/stdio/printk/printk.h>
#include <libc/stdio/printck/printck.h>
#include <drv/video/video.h>
#include <libc/stdlib/itoa/itoa.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>


/*
 * @function printck:
 *     Prints a string on
 *     on the string with
 *     format specifiers
 *     along with colors.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @param fg,bg:
*              Foreground and Background
*              of text.
 *        @var_arg ...:
 *            formatting conversion
 *            utility.
 */


void printck(uint8_t fg, uint8_t bg, const char* fmt,  ...)
{
  va_list arg;
  va_start(arg, fmt);
  vprintck(fg,bg,fmt,arg);
  va_end(arg);
}

/*
 * @function vprintck:
 *     @printck but with
 *      `va_list` variadic
 *      argument  param
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *        @param fg,bg:
*              Foreground and Background
*              of text.
 *        @va_list arg:
 *            formatting conversion
 *            utility.
 */

void vprintck(uint8_t fg, uint8_t bg, const char* fmt,  va_list arg)
{
    FG = fg;
    BG = bg;
    vprintk(fmt, arg);
    // FG = 0x7;
    // BG = 0x0;
}


