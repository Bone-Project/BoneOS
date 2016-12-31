#ifndef _ARCH_MM_PMM_H_
#define _ARCH_MM_PMM_H_

#include <stdint.h>
#include <stddef.h>
#include <boot/multiboot/multiboot.h>

extern uint32_t _mmngr_mem_size;

typedef struct 
{
  multiboot_info_t* multiboot_structure;
}multiboot_info_pmm_t;

extern int pmm_init(multiboot_info_t* multiboot_structure);


#endif /*_ARCH_MM_PMM_H_*/