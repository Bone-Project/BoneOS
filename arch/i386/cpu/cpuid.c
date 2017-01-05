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

#include <cpu/cpuid.h>


/**
 * the highest function cpuid supports
 */
static uint32_t cpuid_highest_function;

cpuid_t cpu_id;

/*
 * cpuid for more dependent purpose
 */
static inline void _cpuid(uint32_t a,uint32_t out[3]){
	__asm__ __volatile__ ("cpuid\n\t" 
	                      : "=b"(out[0]), "=c"(out[1]), "=d"(out[2])
	                      :	"a"(a) 
	                     
	);
}


/**
 * checks if the cpuid instruction is available
 * returns true if available
 */
static bool has_cpuid_ins(){
	int res;
	__asm__ __volatile__ (".intel_syntax\n\t"
	                      "pushfd\n\t"
	                      "pushfd\n\t"
	                      "xor dword ptr [%%esp],0x200000\n\t"
	                      "popfd\n\t"
	                      "pushfd\n\t"
	                      "pop %%eax\n\t"
	                      "xor %%eax,[%%esp]\n\t"
	                      "popfd\n\t"
	                      "and %%eax,0x200000\n\t"
	                      ".att_syntax"
	                      :"=a"(res));
	return res;
}

/**
 * stores the highest supported function parameter and vendorID
 */
void init_cpuid(){
	if (!has_cpuid_ins()){ /* return if cpuid is not supported */
		return;
	}
	__asm__ __volatile__ (".intel_syntax\n\t"
						  "xor %%eax,%%eax\n\t"
						  "cpuid\n\t"
						  ".att_syntax\n\t"
						  :"=a"(cpuid_highest_function),"=b"(cpu_id.vendorID[0]),"=d"(cpu_id.vendorID[1]),"=c"(cpu_id.vendorID[2])
						  );
						  
	__asm__ __volatile__ (".intel_syntax\n\t"
	                      "mov %%eax,1\n\t"
	                      "cpuid\n\t"
	                      ".att_syntax\n\t"
	                      :"=a"(cpu_id.signature),"=d"(cpu_id.features_edx),"=c"(cpu_id.features_ecx));
}


bool cpu_has_feature_edx(enum CPU_FEATURES_EDX f){
	return cpu_id.features_edx & ((uint32_t) f);
}
bool cpu_has_feature_ecx(enum CPU_FEATURES_ECX f){
	return cpu_id.features_ecx & ((uint32_t) f);
}


