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

/*DEBUG Defined by -DDEBUG Flag*/
#ifndef DEBUG
    #error "THIS OPERATING SYSTEM IS NOT UP FOR PRODUCTION."
#endif

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>
#include <libc/stdio/stdio.h>
#include <misc/asm_util.h>
#include <boot/multiboot/multiboot.h>
#include <cpu/cpu.h>
#include <libc/string/string.h>
#include <drv/pit/pit.h>
#include <drv/ps2/kbd/kbd.h>
#include <libc/math/math.h>
#include <libc/stdio/printck/printck.h>
#include <libc/stdio/printk/printk.h>
#include <libc/unistd/unistd.h>
#include <libc/assertk.h>
#include <libc/stdio/scank/scank.h>
#include <drv/driver.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <mm/pmm.h>
#include <misc/status_codes.h>
#include <stdlib/stdlib.h>
#include <var/cpu/cpu_info.h>

/*
 * Calling all Global C Objects
 * constructors , via attributes:
 *   @attribute __constructor__
 *   @attribute __deconstructor__
 */
typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern void callConstructors(void)
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

static inline void kernel_init_early()
{
    //getchar(); //Start out getchar();
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
   if(multiboot_structure && magicnumber){};
   init_cpu();
   setup_driver_handler();
   sti();
   kernel_init_early();


   video_drivers[VGA_VIDEO_DRIVER_INDEX]->clear();

   //init_terminal();
   if(pmm_init(multiboot_structure)!=STATUS_OK)
        panik("PHYSICAL MEMORY NOT INITALIZED CORRECTLY");
        
   __debug_print_memory_size();
    printk("\n");
    __debug_print_cpu_info();
    
    //init_terminal();
   
   while(1)
      hlt();
}







