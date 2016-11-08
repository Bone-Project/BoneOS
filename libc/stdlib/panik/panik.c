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
 **		Amanuel Bogale <amanuel2> : start
 **/

#include <include/libc/stdio/printk/printk.h> 
#include <include/misc/asm_util.h>
 
 
 /*
 * @function panik:
 *        Prints an error message
 *        then clears and halts interrupts.
 *    
 *        @param fmt:
 *            orignial string with
 *            no formatting.
 *         @var_arg ...:
 *            formatting conversion
 *            utility.
 */

void panik(const char *fmt, ...)
{
    va_list args;
    va_start(args,fmt);
    vprintk(fmt,args);
    
    cli();
    hlt();
}