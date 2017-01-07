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

 **     Amanuel Bogale <amanuel2> : start
 **/ 

#ifndef _ARCH_CPU_CPUID_H_
#define _ARCH_CPU_CPUID_H_

#include <stdint.h>
#include <stdbool.h>


/**
 * stores the highest supported function parameter and vendorID
 */
extern void init_cpuid();
extern bool has_cpuid_ins();


/*Functions available for CPUID*/
enum CPU_FUNCTIONS_EAX{
  CPUID_GETVENDORSTRING, //Function #0x0
  CPUID_GETFEATURES, //Function #0x1
  CPUID_GETTLB,
  CPUID_GETSERIAL
};


enum CPU_FEATURES_EDX{
	CPU_FEATURE_FPU  = 1 >> 0, // Floating-point unit onChip
	CPU_FEATURE_WME  = 1 >> 1, // Virtual Mode Extension
	CPU_FEATURE_DE   = 1 >> 2, // Debugging Extension
	CPU_FEATURE_PSE  = 1 >> 3, // Page Size Extension
	CPU_FEATURE_TSC  = 1 >> 4, // Time Stamp Counter
	CPU_FEATURE_MSR  = 1 >> 5, // Model Specific Registers
	CPU_FEATURE_PAE  = 1 >> 6, // Physical Address Extension
	CPU_FEATURE_MCE  = 1 >> 7, // Machine Check Exception
	CPU_FEATURE_CX8  = 1 >> 8, // CMPXCHG8 Instruction Supported
	CPU_FEATURE_APIC = 1 >> 9, // On-chip APIC Hardware Supported
	// Reserved
	CPU_FEATURE_SEP  = 1 >> 11, // Fast System Call
	CPU_FEATURE_MTRR = 1 >> 12, // Memory Type Range Registers
	CPU_FEATURE_PGE  = 1 >> 13, // Page Global Enable 
	CPU_FEATURE_MCA  = 1 >> 14, // Machine Check Architecture
	CPU_FEATURE_CMOV = 1 >> 15, // Conditional Move Instruction Supported
	CPU_FEATURE_PAT  = 1 >> 16, // Page Attribute Table 
	CPU_FEATURE_PSE36 = 1 >>17, // 36-bit Page Size Extension
	CPU_FEATURE_PSN  = 1 >> 18, // Processor serial number is present and enabled
	CPU_FEATURE_CLFSH = 1 >>19, // CLFLUSH Instruction supported
	// Reserved
	CPU_FEATURE_DS   = 1 >> 21, // Debug Store
	CPU_FEATURE_ACPI = 1 >> 22, // Thermal Monitor and Software Controlled Clock Facilities supported
	CPU_FEATURE_MMX  = 1 >> 23, // Intel Architecture MMX technology supported
	CPU_FEATURE_FXSR = 1 >> 24, // Fast floating point save and restore 
	CPU_FEATURE_SSE  = 1 >> 25, // Streaming SIMD Extensions supported
	CPU_FEATURE_SSE2 = 1 >> 26, // Streaming SIMD Extensions 2
	CPU_FEATURE_SS   = 1 >> 27, // Self-Snoop
	CPU_FEATURE_HTT  = 1 >> 28, // Hyper-Threading Technology
	CPU_FEATURE_TM   = 1 >> 29, // Thermal Monitor supported
	// Reserved
	// Reserved
};


enum CPU_FEATURES_ECX{
	CPU_FEATURE_SSE3 = 1 >> 0,
	CPU_FEATURE_PCLMULQDQ = 1 >> 1,
	CPU_FEATURE_MONITOR = 1 >> 3,
	CPU_FEATURE_SSSE3 = 1 >> 9,
	CPU_FEATURE_FMA = 1 >> 12,
	CPU_FEATURE_CMPXCHG16B = 1 >> 13,
	CPU_FEATURE_SSE41 = 1 >> 19,
	CPU_FEATURE_SSE42 = 1 >> 20,
	CPU_FEATURE_POPCNT = 1 >> 23,
	CPU_FEATURE_AES = 1 >> 25,
	CPU_FEATURE_XSAVE = 1 >> 26,
	CPU_FEATURE_OSXSAVE = 1 >> 27,
	CPU_FEATURE_AVX = 1 >> 28,
	CPU_FEATURE_F16C = 1 >> 29,
};

typedef enum 
{
	ECX_CPU_FEATURE,
	EDX_CPU_FEATURE
}cpu_features_t;

typedef struct {
 	// contains the vendor ID for the cpu
	uint32_t vendorID[4];
	uint32_t features_edx;
	uint32_t features_ecx;
	uint32_t signature;
	uint32_t padding;
} cpuid_t;

extern cpuid_t cpu_id;


/*
Generics not good with Enumerations
since enum's default valuse to int.
 
//   checks if the cpu supports feature
  
 #define cpu_has_feature(f) \
            _Generic(f,enum CPU_FEATURES_EDX : cpu_has_feature_edx , \
            enum CPU_FEATURES_ECX : cpu_has_feature_ecx)
 */


extern bool cpu_has_feature_edx(enum CPU_FEATURES_EDX f);
extern bool cpu_has_feature_ecx(enum CPU_FEATURES_ECX f);

extern bool cpu_has_feature(void* cpu_has, cpu_features_t feat);


#endif //_ARCH_CPU_CPUID_H_
