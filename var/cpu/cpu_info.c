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
#include <var/cpu/cpu_info.h>
#include <misc/status_codes.h> 
#include <string/string.h>
#include <stdio/stdio.h>
 
cpu_info_t cpu_info;

static inline void find_comp(char* ID)
{
    if(strcmp(ID,"GenuineIntel")==0)
        cpu_info.companyName = "Intel";
    else if(strcmp(ID,"AMDisbetter!")==0)
        cpu_info.companyName = "K5-AMD";
    else if(strcmp(ID,"AuthenticAMD")==0)
        cpu_info.companyName = "AMD";
    else if(strcmp(ID,"CentaurHauls")==0)
        cpu_info.companyName = "Centaur";  
    else if(strcmp(ID,"CyrixInstead")==0)
        cpu_info.companyName = "Cyrix";  
    else if(strcmp(ID,"TransmetaCPU")==0)
        cpu_info.companyName = "Transmeta";  
    else if(strcmp(ID,"GenuineTMx86")==0)
        cpu_info.companyName = "Transmetax86";  
    else if(strcmp(ID,"Geode by NSC")==0)
        cpu_info.companyName = "National Semiconductor";  
    else if(strcmp(ID,"NexGenDriven")==0)
        cpu_info.companyName = "NexGen";  
    else if(strcmp(ID,"RiseRiseRise")==0)
        cpu_info.companyName = "Rise";  
    else if(strcmp(ID,"SiS SiS SiS ")==0)
        cpu_info.companyName = "SiS";  
    else if(strcmp(ID,"UMC UMC UMC ")==0)
        cpu_info.companyName = "UMC";  
    else if(strcmp(ID,"VIA VIA VIA ")==0)
        cpu_info.companyName = "VIA";
    else if(strcmp(ID,"Vortex86 SoC")==0)
        cpu_info.companyName = "Vortex86";
    else if(strcmp(ID,"KVMKVMKVM")==0)
        cpu_info.companyName = "KVM";
    else if(strcmp(ID,"Microsoft Hv")==0)
        cpu_info.companyName = "Vortex86";
    else if(strcmp(ID,"Vortex86 SoC")==0)
        cpu_info.companyName = "Vortex86";  
    else if(strcmp(ID,"VIA VIA VIA ")==0)
        cpu_info.companyName = "Via";
    else if(strcmp(ID,"VMwareVMware")==0)
        cpu_info.companyName = "VMWare";
    else if(strcmp(ID,"XenVMMXenVMM")==0)
        cpu_info.companyName="XenVMMX";
    else if(strcmp(ID,"Microsoft Hv")==0)
        cpu_info.companyName = "Microsoft Hypervisor";
    else if(strcmp(ID," lrpepyh vr")==0)
        cpu_info.companyName = "Parrelels";
    else
        cpu_info.companyName = "Unknown";
}

static void signature_proccessing(uint32_t sig)
{
    if(strcmp(cpu_info.companyName, "Intel")==0)
    {
        int bit_twelve = (sig >> 12) & 1;  
        int bit_thirteen = (sig >> 13) & 1;
        
        if(bit_twelve == 0 && bit_thirteen == 0)
            cpu_info.proccecor_type = "Original OEM Proccecor";
        else if(bit_twelve == 0 && bit_thirteen == 1)
            cpu_info.proccecor_type = "OverDrive Proccecor";
        else if(bit_twelve == 1 && bit_thirteen == 0)
            cpu_info.proccecor_type = "Dual Proccecor";
        else if(bit_twelve == 1 && bit_thirteen == 1)
            cpu_info.proccecor_type = "Intel Reserved.";
        else
            cpu_info.proccecor_type = "Unknown";
    }
}

int init_cpu_info()
{
    cpu_info.vendorID =(char*) cpu_id.vendorID;
    cpu_info.ecx_features = cpu_id.features_ecx;
    cpu_info.edx_features = cpu_id.features_edx;
    cpu_info.signature = cpu_id.signature;
    find_comp(cpu_info.vendorID);
    signature_proccessing(cpu_info.signature);

        
    return STATUS_OK;
}

void __debug_print_cpu_info()
{
    #ifdef DEBUG
     printk("CPU\n");
     printk("---\n");
     printk("COMPANY : %s\n", cpu_info.companyName);    
     printk("VENDOR_ID : %s\n", cpu_info.vendorID);
     printk("PROCCECOR TYPE : %s\n", cpu_info.proccecor_type);
   #endif     
}