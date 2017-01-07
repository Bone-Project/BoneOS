
#ifndef _MM_BITMAP_H_
#define _MM_BITMAP_H_ 1

#include <mm/pmm.h>
#include <boot/multiboot/multiboot.h>


extern int init_bitmap_alloc(multiboot_info_t* multiboot_structure);
extern int _bitmap_find_first_free_bit();

extern allocation_scheme_t bitmap_pmm_allocation;

#endif /*_MM_BITMAP_H_*/