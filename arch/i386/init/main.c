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
#include <drv/video/VGA/textmode/putch/putch.h>
#include <drv/pit/pit.h>
#include <drv/ps2/kbd/kbd.h>
#include <libc/math/math.h>
#include <libc/stdio/printck/printck.h>
#include <libc/unistd/unistd.h>
#include <libc/assertk.h>
#include <libc/stdio/scank/scank.h>
#include <drv/driver.h>


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
   init_all_drivers();
   sti();

   sprintk(str, "Value of Pi = %d" , 3);
   printk("\n%s" , str);
   //printk("\n%f" , 3.14);
   
   printk("%d" , powk(10,2));

   printck(0x5,0x2,"Yea whassup");
   printk("\n Back to Original");

   printk("{>>> %.2f <<<}", 2.33);

   // int* int1, int2;
   // char* str1;
   // char chr1;

   // scank("%d" , &int1);
   // scank("%s" , &str1);
   // scank("%d" , &int2);
   // scank("%c", &chr1);
   // printk("int1 : %d , str1 : %s , int2 : %d char %c", int1, str1, int2,chr1);

   int hex_1;
   int int_1;
   char chr_1;
   char str_1[256];

   scank("%s%c%x%d" , &str_1, &chr_1 , &hex_1, &int_1);

   printk("chr_1 : %c  hex_1 : %d str_1 : %s int_1 %d  " , chr_1,  hex_1 , str_1, int_1 );


   while(1)
      hlt();
}

