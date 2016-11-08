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
 **     Doug Gale <doug65536> : update to printk
 **/  

#include <stddef.h>
#include <stdint.h>


/*
 * @function powk:
 *      With specified base
 *      and exponent, finds
 *      the power of both.
 *    
 *         @param x:
 *                specified base
 *         @param y:
 *                 specified exponent
 *
 *          @return int:
 *                  Returns the power of
 *                  the base and exponent.
 */

int powk(int x, uint32_t y)
{
    if( y == 0)
        return 1;
    else if (y%2 == 0)
        return powk(x, y/2)*powk(x, y/2);
    else
        return x*powk(x, y/2)*powk(x, y/2);
 
}