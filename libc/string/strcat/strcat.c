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
 * @function strcat:
 *    Concatonates a specified src string, 
 *     to another specified dest string.
 *
 *        @param dest (char*):
 *           Specified string to 
 *           concatonate to.
 *
 *        @param src (char*):
 *           Specified string that
 *           will be concatonated to dest.
 *
 *        @return (char*):
 *           Returns the final 
 *           concatonated string (@dest)
 *
 */

#include <stddef.h>
#include <stdint.h>
#include <libc/string/strlen/strlen.h>
#include <libc/string/strcpy/strcpy.h>

char* strcat(char *dest, const char *src)
{
    strcpy(dest + strlen(dest), src);
    return dest;
}