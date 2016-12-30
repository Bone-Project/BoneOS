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
  if(y==0) return 1;
  int answer=1;
    for(uint32_t i=0; i<y; i++)
      answer = answer * x;
  return answer;    
}




