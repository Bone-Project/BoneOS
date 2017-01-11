
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

// |  | -> |  |


#include <mm/bitmap.h>
#include <misc/status_codes.h>
#include <stdbool.h>
#include <string/string.h>
#include <mm/pmm_util.h>
#include <stdio/stdio.h>

static uint32_t _bitmap_used_blocks = 0;
static uint32_t _bitmap_max_blocks  = 0; /*TODO : CHANGE THIS TO RELIABLE*/
static uint32_t *_bitmap_blocks=0;

allocation_scheme_t bitmap_pmm_allocation = 
{
  .init = init_bitmap_alloc,
  .allocate_block_ff = _bitmap_find_first_free_bit
};

//Block -> 4KB OF Data
//4Bytes holy 32 Blocks or 4KiB * 32 or 128 MiB
//[0] Corresponds to first #0->#32 Blocks. [1] corresponds to Blocks #32->#64.

static inline void _bitmap_set_block_bit(int bit)
{
  _bitmap_blocks[bit/32] |= 1 << (bit % 32);
  _bitmap_used_blocks+=1;
}

static inline void _bitmap_clear_block_bit(int bit)
{
  _bitmap_blocks[bit/32] &= ~(1<<(bit%32));
  _bitmap_used_blocks-=1;
}
static inline bool _bitmap_test_block_bit(int bit)
{
  return ((_bitmap_blocks[bit/32]>>(bit%32)) & 1 );
}

int _bitmap_find_first_free_bit()
{
  for(uint32_t i=0; i<_bitmap_max_blocks; i++)
    if(_bitmap_test_block_bit(i)==false) //Notset
      return i;
  return -1;  
}

//Initalize a region in memory
//|  | -> | 1 |
bool init_region(uint32_t base_adress, size_t size)
{

  return STATUS_OK;
}

int init_bitmap_alloc(multiboot_info_t* multiboot_structure)
{
  _bitmap_max_blocks = (mem_amt(multiboot_structure,KiB,true))/_PMM_MNGR_BLOCK_SIZE /*Get each 4096KB's ;)*/;
  
  memset(_bitmap_blocks,0xFFFFFFFF,_bitmap_max_blocks);
  
  _bitmap_set_block_bit(0); //First block set to return NULL Block pointers

  printk("MAX_BLOCKS : %d\n",_bitmap_max_blocks);
  return STATUS_OK;
}