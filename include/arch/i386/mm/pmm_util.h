

#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot/multiboot.h>

#ifndef _ARCH_MM_PMM_UTIL_H_
#define _ARCH_MM_PMM_UTIL_H_

#define HIGHER_KERNEL_ADDRESS_LOAD 0x0

typedef struct
{
    uint32_t available;
    uint32_t size;
} mem_size_t;

extern mem_size_t _mmngr_mem_size;

typedef struct 
{
  multiboot_info_t* multiboot_structure;
} multiboot_info_pmm_t;

extern int pmm_util_init(multiboot_info_t* multiboot_structure);

#ifdef DEBUG
   extern void __debug_print_memory_size();
#endif 

extern uint32_t mem_amt(multiboot_info_t* multiboot_structure, bool mmap_avail);

#endif
