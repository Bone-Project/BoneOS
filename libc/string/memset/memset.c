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
#include <libc/string/memset/memset.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>

/*
 * @function memset:
 *   Sets dst's first n   
 *   bytes to c (char|int)
 *
 *        @param dst (void*):
 *           Specified Buffer to
 *           change
 *        @param c (int):
 *           Specified type to
 *           change to
 *         @parm n (size_t):
 *            Specified Number
 *            of bytes to change
 *            the buffer
 *
 *         @return (void*):
 *            Returns the new 
 *            changed buffer ,
 *            while actually 
 *            changing the value.        
 *
 */

void *memset(void *dst, int c, size_t n)
{
   char* d = dst;   
   while(n--)
    *d++=(char)c;
   return dst;    
}



