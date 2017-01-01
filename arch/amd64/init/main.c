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
  
#include <stdint.h>
#include <stddef.h>
#include <misc/asm_util.h>
#include <cpu/cpu.h>
#include <drv/driver.h>

/*
 * Calling all Global C Objects
 * constructors , via attributes:
 *   @attribute __constructor__
 *   @attribute __deconstructor__
 */
typedef void (*constructor)(void);
extern constructor start_ctors;
extern constructor end_ctors;
extern void callConstructors(void)
{
    for(constructor* i = &start_ctors;i != &end_ctors; i++)
        (*i)();
}

static inline void kernel_init_early(void)
{

}

/*
 * @function kernelMain:
 *      Main function of the kernel,
 *      the function the GRUB bootloader
 *      calls when Loading the kernel.
 *
 */
void kernelMain(uint32_t multiboot,uint32_t magicnumber)
{
   if(multiboot && magicnumber){};
   init_cpu();
   setup_driver_handler();
   sti();
   kernel_init_early();
   while(1)
        hlt();
}


