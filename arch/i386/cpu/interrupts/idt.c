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
#include <arch/cpu/i386/interrupts/idt.h>
#include <arch/cpu/i386/interrupts/interrupts.h>

/*
 * @IDT_SIZE : 256 Interrupt Descriptor tables
 */
#define IDT_SiZE 256

/*
 * @struct idt_ptr : 
 *   Pointer to the Interupt Descriptor Table.
 *      @limit : Limit Of IDT which is 256-1 , since 
 *               start from index 0.
 *      @base : 32 Bit Full Base Address of IDT.
 */
 typedef struct 
 {
    uint16_t limit;
    uint32_t base;
 }__attribute__((packed)) idt_ptr;



 idt_desc idt[IDT_SiZE];
 idt_ptr idp;

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