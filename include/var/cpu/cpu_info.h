#ifndef _VAR_CPU_CPUINFO_H_
#define _VAR_CPU_CPUINFO_H_

#include <cpu/cpuid.h>

typedef struct 
{
    char* companyName;
    char* vendorID;
    enum CPU_FEATURES_ECX ecx_features;
    enum CPU_FEATURES_EDX edx_features;
    uint32_t signature;
    char* proccecor_type;
}cpu_info_t;

extern cpu_info_t cpu_info;

extern int init_cpu_info();
extern void __debug_print_cpu_info();


#endif /*_VAR_CPU_CPUINFO_H_*/