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

/*
 * @function strlen:
 *    Gets the size of the 
 *    buffer specified
 *
 *        @param str (char*):
 *           Specified Buffer to
 *           find the length
 *           of
 *
 *        @return (char*):
 *           Returns the length
 *           of the specified buffer.
 */

#include <stddef.h>

size_t strlen(const char* str)
{
    size_t len=0;
    while(*str++)len++;
    return len;    
}
