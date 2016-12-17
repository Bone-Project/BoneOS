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

#include <stdint.h> 
#include <misc/status_codes.h>
#include <misc/asm_util.h>
#include <stddef.h>
#include <io/io.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>

int root_sys_poweroff(void)
{
   printck(0x4,0x0,"SHUTTING DOWN\n");
   sleep(2000); //2000 milliseconds timeout
   __asm__ __volatile__ ("outw %1, %0" 
                         :
                         : "dN" ((uint16_t)0xB004), "a" ((uint16_t)0x2000) //VAR->ASM
                        );
   return STATUS_OK;
}
