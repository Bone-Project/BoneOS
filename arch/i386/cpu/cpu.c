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
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/isr.h>
#define KERNEL_CALL
  #include <cpu/interrupts/irq.h>
#undef KERNEL_CALL
#include <libc/string/string.h>

void init_cpu()
{
   init_gdt();
   init_idt();
   init_isr();
   init_irq();
}

