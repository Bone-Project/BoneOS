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
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/interrupts.h>


idt_desc idt[IDT_SiZE];
idt_ptr idp;

/*
 * @function idt_set_gate :
 *     Set an Interrupt Gate
 *     in the Interrupt Descriptor
 *     table.
 *         @param num: Interrupt Number
 *         @param handler : Interrupt Handler
 *         @param sel : Segment Selector
 *         @param flags : Flags like DPL.
 */
void idt_set_gate(uint8_t num, int_handler handler, uint16_t sel,
              uint8_t flags) 
{
    idt[num].base_lo = (uintptr_t)handler >> 0 & 0xFFFF;
    idt[num].base_hi = (uintptr_t)handler >> 16 & 0xffff;
    idt[num].reserved = 0;
    idt[num].sel = sel;
    idt[num].flags = flags;
}

 /*
  * @function init_idt:
  *   Initalizes Interupt Descriptor Table.
  *   Sets limit and base, sets all 256 
  *   descriptors to 0.
  */
  
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

