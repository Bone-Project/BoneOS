#ifndef _ARCH_MM_PMM_H_
#define _ARCH_MM_PMM_H_

#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot/multiboot.h>

#define HIGHER_KERNEL_ADDRESS_LOAD 0x0

#define PAGE_SIZES 4096 /*4KB PSE*/

#define _PMM_MNGR_BLOCKS_PER_BYTE 8
#define _PMM_MNGR_BLOCK_SIZE PAGE_SIZES /*4KB PAGES*/

/*Allocation Schemes Indexes*/
#define _BITMAP_PAGE_FRAME_ALLOCATION_SCHEME 0

typedef struct
{
    double GiB;
    double MiB;
    double KiB;
    double B;
}mem_size_t;

extern mem_size_t _mmngr_mem_size;

typedef struct 
{
  multiboot_info_t* multiboot_structure;
}multiboot_info_pmm_t;

extern int pmm_init(multiboot_info_t* multiboot_structure);

#ifdef DEBUG
   extern void __debug_print_memory_size();
#endif   

typedef struct
{
   int  (*init)(multiboot_info_t* multiboot_structure);
   int (*allocate_block_ff)(); //ff -> first free @return first free bit
}allocation_scheme_t;


#endif /*_ARCH_MM_PMM_H_*/

