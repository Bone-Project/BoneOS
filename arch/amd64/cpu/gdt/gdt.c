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

#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <cpu/gdt/gdt.h>
#include <libc/string/string.h>


struct SegmentDescriptor gdt[] = {
    GDT_MAKE_EMPTY(),
    GDT_MAKE_CODESEG(0),
    GDT_MAKE_DATASEG(0),
    GDT_MAKE_CODESEG(3),
    GDT_MAKE_DATASEG(3)
};

/*
 * @function init_gdt:
 *     Function that installs
 *     the Global Descriptor Table
 *     into the CPU for use. Main
 *     called function
 *
 */

void init_gdt()
{
  gp.limit = (sizeof(gdt)-1);
  gp.base = (uintptr_t)gdt;
   __asm__ __volatile__ (" lgdt%z0 (%0)"
                                            :
                                            :  [gp]"r"(&gp)
                                            ); 
}

