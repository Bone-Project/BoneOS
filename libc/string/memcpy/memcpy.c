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


/*
 * @function memcpy:
 *   Copies n characters from __src
 *   to __dest , starting index 0.
 *
 *        @param __src (void*):
 *           Specified Memory Area
 *           to copy from
 *
 *        @param __dest (void*):
 *           Specified Memory area
 *           to copy to.
 *
 *        @return (void*):
 *          Returns original __dest.
 *
 */

void *memcpy(void * __dest, const void * __src, size_t n)
{
   char* ___dest = __dest;
   const char* ___src = __src;
   while(n)
   {
       *___dest++=*___src++;
       n--;
   }
  return __dest;
}

