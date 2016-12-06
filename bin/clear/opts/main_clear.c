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
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <clear/clear.h>
#include <clear/opts/color.h>
#include <term/terminal.h>
#include <stdlib/stdlib.h>

int main_clear_opt_handler(char *cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(strcmp(opts[1].str, "--color")==0)
   {
     if(opts[3].str[0] == '\0' || opts[4].str[0] == '\0')
     {
       printk("Invalid Use of --color option. Use command clear --color --help for instructions\n");
       printk("on how to use the clear command\n");
     }
     else if(strcmp(opts[3].str, "--help"))
     {
        printk(cmd_clear_opt_color.help);
     }
     else 
     {
        int FG_ = atoi(opts[3].str);
        int BG_ = atoi(opts[4].str);
        printk("FG : %d , BG %d" , FG_, BG_);
     }
   }
    
     return STATUS_OK;
}
