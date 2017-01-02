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
 **  @main_author : Doug Gale
 **  
 **  @contributors:

 **     Doug Gale <doug65536> : start
 **/ 

#include <stddef.h>
#include "libc/string/memcmp/memcmp.h"

/*
 * @function memcmp:
 *   Compare two memory blocks. The memory is
 *   compared byte by byte as unsigned 8-bit
 *   values. The compare stops at the first
 *   difference.
 *
 *        @param lhs (void*):
 *           Left hand side memory block
 *
 *        @param rhs (void*):
 *           Right hand side memory block
 *
 *        @param count
 *           The number of bytes to compare
 *
 *        @return (void*):
 *          Return negative value if lhs < rhs
 *          Return zero if lhs == rhs
 *          Return positive value if lhs > rhs
 *          Returns zero if count is zero
 *
 */

int memcmp(void const *lhs, void const *rhs, size_t count)
{
	unsigned char const *lp = lhs;
	unsigned char const *rp = rhs;
	int cmp = 0;
	if (count) {
		do {
			cmp = *lp++ - *rp++;
		} while (cmp == 0 && --count);
	}
	return cmp;
}



