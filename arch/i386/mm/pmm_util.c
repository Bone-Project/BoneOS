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
#include <mm/pmm_util.h>
#include <stdlib/stdlib.h>

static multiboot_info_pmm_t mb_info;

mem_size_t _mmngr_mem_size = {0,0};

int pmm_util_init(multiboot_info_t* multiboot_structure)
{
  mb_info.multiboot_structure = multiboot_structure;

  mb_info.multiboot_structure->mmap_addr += HIGHER_KERNEL_ADDRESS_LOAD; //Higher half

  _mmngr_mem_size.size = mem_amt(mb_info.multiboot_structure,false);
  _mmngr_mem_size.available = mem_amt(mb_info.multiboot_structure,true);

  return STATUS_OK;
}

void __debug_print_memory_size()
{
  #ifdef DEBUG
    printk("MEMORY SIZE\n");
    printk("-----------\n");
    printk("GiB : %.7f\n",((double) _mmngr_mem_size.available)/1024/1024/1024);
    printk("MiB : %.7f\n",((double) _mmngr_mem_size.available)/1024/1024);
    printk("KiB : %.7f\n",((double) _mmngr_mem_size.available)/1024);
    printk("B   : %.7f\n",((double) _mmngr_mem_size.available));
  #endif
}


int mem_amt(multiboot_info_t* multiboot_structure, bool mmap_avail)
{
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) multiboot_structure->mmap_addr;
  
    int amt_mem=0;
          
  	while(mmap < (multiboot_memory_map_t*) (multiboot_structure->mmap_addr + multiboot_structure->mmap_length)) 
  	{
  	  if(mmap_avail==true)
  	  {
  	     if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
  	       amt_mem+=mmap->len;
  	  }
  	  else
  	      amt_mem+=mmap->len;
	  mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
  	}
  	
    return amt_mem;
}

