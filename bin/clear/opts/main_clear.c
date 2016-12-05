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
 
 #include <misc/status_codes.h>
 #include <unistd/unistd.h>
 #include <stdio/stdio.h>
 #include <string/string.h>
 
 int main_clear_opt_handler(str_t opts[])
 {
     if(strcmp(opts[2].str,"--color")==0)
     {
         if(opts[3].str == 0 || opts[4].str == 0)
                printk("INVALID USE OF --color Option\n");
         else
         {
             printk("EXECUTING\n");
         }
     }
     return STATUS_OK;
 }