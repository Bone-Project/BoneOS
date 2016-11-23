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
 **  @main_author : regality
 **
 **  @contributors:
 **   regality <regality> : start
 **
 **   @src : http://stackoverflow.com/a/5000217/5768335
 **/

#include <stddef.h>
#include <stdint.h>
#include <libc/string/string.h>

/*
 * @function sqrtk:
 *      Extremely Optimized
 *      float function using 
 *      newtons constant
 *      approximation
 *
 *         @param n:
 *              specified float
 *              to be square rooted.
 *
 *          @return float:
 *               Returns square root
 *               of specified float (@n)
 */

int sqrtk(int n)
{
   long i;
   float x2, y;
   const float threehalfs = 1.5F;

   x2 = n * 0.5F;
   y  = n;
   #pragma GCC diagnostic ignored "-Wstrict-aliasing"
      i = *(long*)&y;
      i  = 0x5f3759df - ( i >> 1 );
      y  = * ( float * ) &i;
   #pragma GCC diagnostic pop
   y  = y * ( threehalfs - ( x2 * y * y ) );
   y  = y * ( threehalfs - ( x2 * y * y ) );
   y  = y * ( threehalfs - ( x2 * y * y ) );

   return 1/y;
}
