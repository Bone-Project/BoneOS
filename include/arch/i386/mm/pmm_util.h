#ifndef _ARCH_MM_PMM_UTIL_H_
#define _ARCH_MM_PMM_UTIL_H_

#include <stdint.h>
#include <stddef.h>

typedef enum 
{
    B,
    KiB,
    MiB,
    GiB
}memory_type_t;

extern double mem_amt(multiboot_info_t* multiboot_structure, memory_type_t mem, bool mmap_avail);


#endif /*_ARCH_MM_PMM_UTIL_H_*/

