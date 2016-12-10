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
#include <math/common.h>
#include <string/string.h>

/*
 * @function sqrtk:
 *      Square root implementation
 *      using the Newton–Raphson method.
 *         @param x:
 *            specified float
 *            to be square rooted.
 *         @param iter:
 *            Number of itterations
 *            the more the more precice
 *            this sqrt() function.
 *
 *         @return float:
 *            Returns square root
 *            of specified float (@x)
 * 
 * @alternative {x86}: FSQRT x86 Instruction
 */

double sqrtk(double x, int iter)
{
  if(x<0) return NAN;
  if(x==0) return 0;
  double answer=1;
  for(int i=0; i<iter; i++)
    answer = answer - ( (answer*answer-x) / (2.0*answer));
  return answer;
}
