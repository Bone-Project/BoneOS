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
 * @function strchr:
 *    searches for the first occurrence of the 
 *    character c (an unsigned char) in the 
 *    string pointed to by the argument str.
 *
 *        @param str (char*):
 *           Specified Buffer to 
 *           search through for 
 *           occurence of char.
 *
 *        @param c (int):
 *           Specified character
 *           to look for.
 *
 *        @return (char*):
 *           Returns the string
 *           after the first 
 *           occurence of the
 *           character.   
 *
 */

char *strchr(const char *str, int c) 
{
    for (; *str; str++)
        if (*str == c) return (char*)++str;
    return (char*)0;
}
