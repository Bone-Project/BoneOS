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
#include <mm/pmm_util.h>



double mem_amt(multiboot_info_t* multiboot_structure, memory_type_t mem, bool mmap)
{
    multiboot_memory_map_t* mmap = (multiboot_memory_map_t*) multiboot_structure->mmap_addr;
  
    double amt_mem=0;
          
  	while(mmap < (multiboot_memory_map_t*) (multiboot_structure->mmap_addr + multiboot_structure->mmap_length)) 
  	{
  	  mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
  	  if(mmap==true)
  	  {
  	     if(mmap->type == MULTIBOOT_MEMORY_AVAILABLE)
  	       amt_mem+=mmap->len;
  	  }
  	  else
  	      amt_mem+=mmap->len;

  	}
  	
    if(mem == KiB)
        return (amt_mem/(1024));
    else if (mem == MiB)
        return (amt_mem/(1024*1024));
    else if (mem == GiB)
        return (amt_mem/(1024*1024*1024));
    else 
        return (amt_mem);
        
        
}

void pmm_memory_print_debug(){}
