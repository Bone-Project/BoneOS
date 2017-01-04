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
 
#include <stdint.h>
#include <stddef.h>
#include <strlen/strlen.h>

/*
 * @function strcmp:
 *    Compares the string pointed to,
 *    by s1 to the string pointed to by s2.
 *
 *        @param s1 (const char*):
 *           First Specified
 *           string to compare
 *
 *        @param c (int):
 *           Second Specified 
 *           string to compare
 *
 *        @return (char*):
 *           returns 0 if equal
 *           1 if not
 *
 */

int strcmp(const char* s1, const char* s2)
{
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}





