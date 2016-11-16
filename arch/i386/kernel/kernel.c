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
#include <GlobalDefintions.h>
#include <libc/stdio/stdio.h>
#include <misc/asm_util.h>
#include <boot/multiboot/multiboot.h>
#include <cpu/gdt/gdt.h>
#include <cpu/interrupts/idt.h>
#include <cpu/interrupts/isr.h>
#define KERNEL_CALL
#include <cpu/interrupts/irq.h>
#undef KERNEL_CALL
#include <libc/string/string.h>
#include <drv/i386/video/VGA/textmode/putch/putch.h>
#include <drv/i386/pit/pit.h>
#include <drv/i386/kbd/kbd.h>
#include <libc/math/math.h>
#include <libc/stdio/printck/printck.h>
#include <libc/unistd/unistd.h>
#include <libc/assertk.h>




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
   char str[80];
   init_gdt();
   init_idt();
   init_isr();
   init_irq();
   init_pit();
   init_kbd(); 
   sti();

    sprintk(str, "Value of Pi = %d" , 3);
   printk("\n%s" , str);
   //printk("\n%f" , 3.14);
   
   printk("%d" , powk(10,2));

   printck(0x5,0x2,"Yea whassup");
   printk("\n Back to Original");

   printk("{>>> %.2f <<<}", 2.33);

   // sleep(3);
   assertk(1==0);
   while(1)
    hlt();
}

