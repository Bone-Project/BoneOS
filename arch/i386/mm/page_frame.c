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

static int *bitmap;

static void set_page(uint32_t bit,int value){
	if (value == 1)
		bitmap[bit / 32] |= (1 << (bit % 32));
	else
		bitmap[bit / 32] &= ~(1 << (bit % 32));
}

static uint8_t get_page(uint32_t bit){
	return (uint8_t) (bitmap[bit / 32] & (1 << (bit % 32)));
}

static void init_reigion(uint32_t base,uint32_t size){
	for (uint32_t page = (base >> PAGE_SHIFT);page <= ((base + size) >> PAGE_SHIFT);page++){
		set_page(page,PAGE_FREE);	
	}
}

static void deinit_reigion(uint32_t base,uint32_t size){
	for (uint32_t page = (base >> PAGE_SHIFT);page <= (base + size) >> PAGE_SHIFT;page++){
		set_page(page,PAGE_USED);
	}
}

static uint32_t find_free_pages(size_t num){
	size_t free_pages_found = 0;
	uint32_t tmp_free = 0;
	bool free_founded = false;
	for (uint32_t page = 0;page < (_mmngr_mem_size.size >> PAGE_SHIFT) / 32;page++){
		if ((free_founded) && (get_page(page) == PAGE_FREE)){
			free_pages_found++;
			if (free_pages_found == num)
				return tmp_free;
		}
		else if (get_page(page) == PAGE_FREE){
			tmp_free = page;
			free_founded = true;
		}
	}
	return (uint32_t) -1;
}

void *allocate_pages(size_t num) {
	uint32_t first = find_free_pages(num);
	for (size_t i = 0;i < num;i++)
		set_page((uint32_t) (first + i), PAGE_USED);
	return (void *) (first << PAGE_SHIFT);
}

void free_pages(void *first, size_t num) {
	for (size_t i = 0;i < num;i++)
		set_page((uint32_t) (((uint32_t) first >> PAGE_SHIFT) + i), PAGE_FREE);
}

int init_page_frame(multiboot_info_t *multiboot){
	multiboot = multiboot;
	bitmap = (int *) (&_kernel_end);
	memset(bitmap,PAGE_USED * 0xFF, (size_t) ((_mmngr_mem_size.size >> PAGE_SHIFT) / 32));
	
	printk("0x%x\n",_mmngr_mem_size.size);
	
	multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) (multiboot->mmap_addr);
          
  	while(mmap < (multiboot_memory_map_t*) (multiboot->mmap_addr + multiboot->mmap_length))
  	{
  	  	if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
  	  		init_reigion((uint32_t) mmap->addr, (uint32_t) mmap->len);
  	  	printk("base: 0x%x ",mmap->addr);
  	  	printk("size: 0x%x ",mmap->len);
  	  	printk("type: 0x%x\n",mmap->type);
  	  	mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size));
  	}
  	deinit_reigion(0,0x10000);
  	deinit_reigion(0x100000 + HIGHER_KERNEL_ADDRESS_LOAD,((uint32_t )&_kernel_end) - 0x100000 + HIGHER_KERNEL_ADDRESS_LOAD);

  	printk("first free: 0x%x\n",find_free_pages(1));
	return STATUS_OK;
}




