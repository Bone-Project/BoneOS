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

 **   Amanuel Bogale <amanuel2> : start
 **/

#include <misc/status_codes.h>
#include <boot/multiboot/multiboot.h>
#include <stdio/stdio.h>
#include <stdbool.h>
#include <mm/pmm.h>
#include <mm/bitmap.h>
#include <mm/pmm_util.h>
#include <stdlib/stdlib.h>

static bool pmm_initalized = false;
static multiboot_info_pmm_t mb_info;


 allocation_scheme_t *alloc_schemes[] =
 {
   &bitmap_pmm_allocation
 };

mem_size_t _mmngr_mem_size = {0,0,0,0};

int pmm_init(multiboot_info_t* multiboot_structure)
{
  pmm_initalized=true;
  mb_info.multiboot_structure = multiboot_structure;

  mb_info.multiboot_structure->mmap_addr += HIGHER_KERNEL_ADDRESS_LOAD; //Higher half

  _mmngr_mem_size.MiB = mem_amt(mb_info.multiboot_structure,MiB,false);
  _mmngr_mem_size.GiB = mem_amt(mb_info.multiboot_structure,GiB,false);
  _mmngr_mem_size.KiB = mem_amt(mb_info.multiboot_structure,KiB,false);
  _mmngr_mem_size.B   = mem_amt(mb_info.multiboot_structure,B,false);

  if(alloc_schemes[_BITMAP_PAGE_FRAME_ALLOCATION_SCHEME]->init(multiboot_structure))
      panik("Error Initalizing bitmap allocation system");

  return STATUS_OK;
}

void __debug_print_memory_size()
{
  #ifdef DEBUG
    printk("MEMORY SIZE\n");
    printk("-----------\n");
    printk("GiB : %.7f\n",_mmngr_mem_size.GiB);
    printk("MiB : %.7f\n",_mmngr_mem_size.MiB);
    printk("KiB : %.7f\n",_mmngr_mem_size.KiB);
    printk("B   : %.7f\n",_mmngr_mem_size.B);
  #endif
}

