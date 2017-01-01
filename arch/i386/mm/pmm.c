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

static bool pmm_initalized = false;
static multiboot_info_pmm_t mb_info;


uint32_t _mmngr_mem_size = 0;

int pmm_init(multiboot_info_t* multiboot_structure)
{
  pmm_initalized=true;
  mb_info.multiboot_structure = multiboot_structure;
  /*
   * 0xC0100000  -  0xFFFFFFFF
   * NO.  ADDRESS  LENGTH  SIZE  TYPE
   */

  //mb_info.multiboot_structure->mmap_addr += 0xD0000000;
  multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) mb_info.multiboot_structure->mmap_addr ;
  printk("********RAM INFO*********\n");
  printk("No.\t\tADDRESS\t\tLENGTH\t\t\t\tTYPE\t\tSIZE\n");
  for(
      size_t i=0 ;
      i<mb_info.multiboot_structure->mmap_length/(sizeof(multiboot_memory_map_t));
      i++)
  {
              uintptr_t addr = ((uintptr_t)mmap[i].addr);
              uintptr_t length=((uintptr_t)mmap[i].len);
              //uintptr_t size=((uintptr_t)mmap[i].size);
              uintptr_t type=((uintptr_t)mmap[i].type);

               printk("#%d" , i);
               printk("\t\t0x%x",addr);
               printk("\t\t%x"  ,length);
               printk("\t\t\t\t\t\t%d\n"  ,type);
               //printk("\t\t\t\t\t\t\t\t%d\n"  ,type);
               _mmngr_mem_size+=length;
          }
          printk("**************************\n");


          printk("%d MB Of Usable RAM" , _mmngr_mem_size/(1024*1024));


  return STATUS_OK;
}

void pmm_memory_print_debug(){}