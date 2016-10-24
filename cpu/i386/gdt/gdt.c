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

#include <cpu/gdt/i386/gdt.h>

/*
 * @struct SegmentDescriptor:
 *     Descriptor to each segments
 *     such as the code segments,
 *     data segments and NULL segments
 *
 */

struct SegmentDescriptor{ 
    uint16_t limit_low; 
    uint16_t base_low; 
    uint8_t base_middle; 
    uint8_t access;
    uint8_t flags_limit_high; 
    uint8_t base_high;
};

/*
 * @struct gdt_ptr
 *     The GDT Pointer that
 *     gets loaded as the final  
 *     result. Contains limit
 *     of GDT , and the base  
 *     address of GDT
 */

struct gdt_ptr
{
    uint16_t limit;
    uintptr_t base;
}__attribute__((packed)) gp;

extern void gdt_load(struct gdt_ptr gp);

#define GDT_MAKE_SEGMENT_DESCRIPTOR(base, \
            limit, \
            present, \
            privilege, \
            executable, \
            downward, \
            rw, \
            granularity, \
            is32) \
{ \
    ((limit) & 0xFFFF), \
    ((base) & 0xFFFF), \
    (((base) >> 16) & 0xFF), \
    ( \
        ((present) ? 1 << 7 : 0) | \
        (((privilege) & 0x03) << 5) | \
        (1 << 4) | \
        ((executable) ? 1 << 3 : 0) | \
        ((downward) ? 1 << 2 : 0) | \
        ((rw) ? 1 << 1 : 0) \
    ), \
    ( \
        ((granularity) ? 1 << 7 : 0) | \
        ((is32) ? 1 << 6 : 0) | \
        (((limit) >> 16) & 0x0F) \
    ), \
    (((base) >> 24) & 0xFF) \
}

#define GDT_MAKE_EMPTY() \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0, 0, 0, 0, 0, 0, 0, 0)

#define GDT_MAKE_CODESEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 1, 0, 1, 1, 1)

#define GDT_MAKE_DATASEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 0, 0, 1, 1, 1)


struct SegmentDescriptor gdt[] = {
    GDT_MAKE_EMPTY(),
    GDT_MAKE_CODESEG(0),
    GDT_MAKE_DATASEG(0),
    GDT_MAKE_CODESEG(3),
    GDT_MAKE_DATASEG(3)
};

/*
 * @function install_gdt:
 *     Function that installs
 *     the Global Descriptor Table
 *     into the CPU for use. Main
 *     called function
 *
 */

void install_gdt()
{
   gp.limit = (sizeof(struct SegmentDescriptor) * 3) - 1;
   gp.base = (uintptr_t)&gdt;
   gdt_load(gp);
}
