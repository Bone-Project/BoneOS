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

 **		Amanuel Bogale <amanuel2> : start
 **/   
  
#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <include/GlobalDefintions.h>
#include <include/libc/stdio/stdio.h>
#include <include/misc/asm_util.h>
#include <boot/i386/multiboot/multiboot.h>
#include <include/arch/cpu/i386/gdt/gdt.h>
#include <include/arch/cpu/i386/interrupts/idt.h>
#include <include/arch/cpu/i386/interrupts/isr.h>
#define KERNEL_CALL
#include <include/arch/cpu/i386/interrupts/irq.h>
#undef KERNEL_CALL
#include <include/libc/string/string.h>
#include <include/screen/i386/VGA/textmode/putch/putch.h>
#include <include/drv/i386/pit/pit.h>




/*
 * Calling all Global C Objects
 * constructors , via attributes:
 *   @attribute __constructor__
 *   @attribute __deconstructor__
 */
typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern void callConstructors()
{
    for(constructor* i = &start_ctors;i != &end_ctors; i++)
        (*i)();
}


int volatile trick1 = 5;
int volatile trick2 = 0;
int volatile trick3 = 0;

void crash_me()
{
    trick3 = trick1 / trick2;
}


/*
 * @function kernelMain:
 *      Main function of the kernel,
 *      the function the GRUB bootloader
 *      calls when Loading the kernel.
 *
 */
void kernelMain(multiboot_info_t* multiboot_structure,uint32_t magicnumber)
{
    cls();
   init_gdt();
   init_idt();
   init_isr();
   init_irq();

   sti();
   init_pit();
   printk("Hallo");
   hlt();
}

