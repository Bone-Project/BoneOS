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
#include <stdarg.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <libc/stdio/stdio.h>

/*
 * @arr irq_routines :
 *    IRQ Routine Handlers
 */
int_routines irq_routines[16] = 
{
    0,0,0,0,0,0,0,0
   ,0,0,0,0,0,0,0,0
};

/*
 * @function init_irq:
 *    Initalizes IRQ 
 *    by remapping the pic
 *    and setting interrupt gates
 */
void init_irq()
{
    remap_pic_irq();
    idt_set_gate(32, int32, CS_SEGMENT, 0x8e);
    idt_set_gate(33, int33, CS_SEGMENT, 0x8e);
    idt_set_gate(34, int34, CS_SEGMENT, 0x8e);
    idt_set_gate(35, int35, CS_SEGMENT, 0x8e);
    idt_set_gate(36, int36, CS_SEGMENT, 0x8e);
    idt_set_gate(37, int37, CS_SEGMENT, 0x8e);
    idt_set_gate(38, int38, CS_SEGMENT, 0x8e);
    idt_set_gate(39, int39, CS_SEGMENT, 0x8e);
    idt_set_gate(40, int40, CS_SEGMENT, 0x8e);
    idt_set_gate(41, int41, CS_SEGMENT, 0x8e);
    idt_set_gate(42, int42, CS_SEGMENT, 0x8e);
    idt_set_gate(43, int43, CS_SEGMENT, 0x8e);
    idt_set_gate(44, int44, CS_SEGMENT, 0x8e);
    idt_set_gate(45, int45, CS_SEGMENT, 0x8e);
    idt_set_gate(46, int46, CS_SEGMENT, 0x8e);
    idt_set_gate(47, int47, CS_SEGMENT, 0x8e);
}

void install_irq_handler(int num,int_routines route)
{
    irq_routines[num] = route;
}

void uninstall_irq_handler(int num)
{
    irq_routines[num] = 0;
}






