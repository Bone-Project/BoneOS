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
 **  @main_author : Muhammad Rifqi Priyo Susanto
 **  
 **  @contributors:

 **     Muhammad Rifqi Priyo Susanto <srifqi> : start
 **/  
 
#include <stdint.h>
#include <drv/rtc/rtc.h>
#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <time/time.h>

int main_time_opt_handler()
{
   printk("%x:%x:%x UTC.\n", rtc_get_hour(), rtc_get_minute(), rtc_get_second());
    
   return STATUS_OK;
}



