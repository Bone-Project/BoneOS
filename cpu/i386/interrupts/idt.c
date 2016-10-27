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

#include <libc/string/string.h>
#include <cpu/i386/interrupts/idt.h>

#define IDT_SiZE 256

struct idt_desc
{
   uint16_t base_lo;
   uint16_t sel; // Kernel segment goes here.
   uint8_t  reserved;
   uint8_t flags; 
   uint16_t base_hi;
}__attribute__((packed));

struct idt_ptr
{
   uint16_t limit;
   uint32_t base;
}__attribute__((packed));


struct idt_desc idt[IDT_SiZE];
struct idt_ptr idp;

void init_idt()
{
	idp.limit = (sizeof(idt))-1;
	idp.base = (uint32_t) &idt;

	memset(&idt,0,sizeof(idt));

	__asm__ __volatile__(
							"lidt %0"
			 				:
			 				:"m"(idp)
		 				);
}