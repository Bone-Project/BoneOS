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
#include <mm/page_frame.h>
#include <mm/pmm_util.h>
#include <stdint.h>
#include <stdlib/stdlib.h>
#include <string/string.h>

extern uint32_t _kernel_end;
uint32_t free_mem_start = 0;

static int **buddy;

static uint32_t buddy_size(){
	uint32_t res = NUMBER_OF_BUDDIES;
	for (size_t i = 0;i < NUMBER_OF_BUDDIES;i++){
		res += (_mmngr_mem_size.size >> (i + PAGE_SHIFT));
	}
	return res;
}



static void init_reigion(uint32_t base,uint32_t size){
	base = base;
	for (size_t i = 0;i < NUMBER_OF_BUDDIES;i++) {
		for (size_t j = 0;j < size;j++){

		}
	}
}

void init_page_frame(multiboot_info_t *multiboot){
	multiboot = multiboot;
	buddy = (int **) (&_kernel_end);
	memset(buddy,0,buddy_size());
	buddy[0] = (int *) (&_kernel_end + NUMBER_OF_BUDDIES * 4);
	for (size_t i = 1;i < NUMBER_OF_BUDDIES;i++){
		buddy[i] = (int *) (&_kernel_end + NUMBER_OF_BUDDIES * 4 + (_mmngr_mem_size.size >> (i + PAGE_SHIFT - 1)));
	}
	printk("0x%x\n",_mmngr_mem_size.size);

	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) (multiboot->mmap_addr);

  	while(mmap < (multiboot_memory_map_t*) (multiboot->mmap_addr + multiboot->mmap_length))
  	{
  	  	if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
  	  		init_reigion(mmap->addr,mmap->len);
  	  	printk("base: 0x%x ",mmap->addr);
  	  	printk("size: 0x%x ",mmap->len);
  	  	printk("type: 0x%x\n",mmap->type);
  	  	mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size));
  	}
}




