
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

#define __cpuid(in, a, b, c, d) \
         __asm__("cpuid\n\t" \
                 :"=a" (a), "=b" (b), "=c" (c), "=d" (d) \
                 : "a" (in)); 


/**
 * the highest function cpuid supports
 */
//static uint32_t cpuid_highest_function;

cpuid_t cpu_id;


/**
 * stores the highest supported function parameter and vendorID
 */
void init_cpuid(){
  if (!has_cpuid_ins()){ /* return if cpuid is not supported */
    return;
  }
  int res;
  __cpuid(CPUID_GETVENDORSTRING,res,cpu_id.vendorID[0],cpu_id.vendorID[2],cpu_id.vendorID[1]);
  __cpuid(CPUID_GETFEATURES,cpu_id.signature,res,cpu_id.features_ecx,cpu_id.features_edx);
}

bool cpu_has_feature(void* cpu_has, cpu_features_t feat)
{
  if(feat==ECX_CPU_FEATURE)
    return ( cpu_has_feature_ecx(*(enum CPU_FEATURES_ECX *)(cpu_has) ) );
  else
    return ( cpu_has_feature_edx(*(enum CPU_FEATURES_EDX *)(cpu_has) ) ); 
}


bool cpu_has_feature_edx(enum CPU_FEATURES_EDX f){
  return cpu_id.features_edx & ((uint32_t) f);
}
bool cpu_has_feature_ecx(enum CPU_FEATURES_ECX f){
  return cpu_id.features_ecx & ((uint32_t) f);
}


