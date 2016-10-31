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

/*
 * @IDT_SIZE : 256 Interrupt Descriptor tables
 */
#define IDT_SiZE 256

/*
 * @struct idt_desc:
 *   Descriptor For an Interupt
 *   out of 256 interupts. 
 *      @base_lo : low 32 bit base addres for routine entry
 *      @sel : segment selector offset (0x8=CS)
 *      @reserved : Always 0.
 *      @flags :  Low 5 bits are 01110. Bits 5 and 6 
 *                is the DPL and bit 7 is the Present bit.
 *      @base_hi : High 32 bit base address for routine entry.
 */

 struct idt_desc
 {
    uint16_t base_lo;
    uint16_t sel; // Kernel segment goes here.
    uint8_t  reserved;
    uint8_t flags; 
    uint16_t base_hi;
 }__attribute__((packed));

/*
 * @struct idt_ptr : 
 *   Pointer to the Interupt Descriptor Table.
 *      @limit : Limit Of IDT which is 256-1 , since 
 *               start from index 0.
 *      @base : 32 Bit Full Base Address of IDT.
 */
 struct idt_ptr
 {
    uint16_t limit;
    uint32_t base;
 }__attribute__((packed));


 struct idt_desc idt[IDT_SiZE];
 struct idt_ptr idp;

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