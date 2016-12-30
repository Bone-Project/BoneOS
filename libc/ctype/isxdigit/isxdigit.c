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

#include <ctype/ctype.h>

/*
 * @function isxdigit:
 *      Checks if specified character
 *      is a hexadecimal digit
 *
 *         @param c:
 *              Specified Character
 *
 *          @return int:
 *             Returns 1 if it is a hexadecimal digit
 *             0 otherwise
 */

int isxdigit(int c)
{
  return (isdigit(c) || (c >= 65 && c <= 70 ) ? 1 : 0);
}



