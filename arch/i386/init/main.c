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
 **     Ashish Ahuja <Fortunate-MAN>
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
#include <mm/page_frame.h>
#include <mm/pmm_util.h>
#include <misc/status_codes.h>
#include <stdlib/stdlib.h>
#include <var/cpu/cpu_info.h>
#include <stdlib/stdlib.h>
#include <drv/pci/pci.h>

/*
 * Calling all Global C Objects
 * constructors , via attributes:
 *   @attribute __constructor__
 *   @attribute __deconstructor__
 */
typedef void (*constructor)();
extern constructor start_ctors;
extern constructor end_ctors;
extern uint32_t _kernel_end;
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


void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
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

    //free_mem_start = _kernel_end;

	//pmm_util_init(multiboot_structure);
    //init_page_frame(multiboot_structure);

    #ifdef DEBUG
      __debug_print_memory_size();
      __debug_print_cpu_info();
    #endif

    //init_terminal();
    printk("\n");
      print_pci_devices_enumeration_scheme();
      
    printk ("\n");

    while(1)
        hlt();
}

