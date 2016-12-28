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
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sleep/sleep.h>
#include <sleep/opts/main_sleep.h>
#include <string/string.h>
#include <ctype/ctype.h>

struct cmd_opt_t* cmd_sleep_opts[] = 
{
  0
};

int cmd_sleep_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(strcmp(opts[1].str,"--help")==0)
   {
     printk(cmd_sleep.help);
     return STATUS_OK;
   }
   
   if(strcmp(opts[1].str,"")==0)
   {
       printk("sleep: missing operand\n");
       printk("Try 'sleep --help' for more information.\n");
   }
   
   for(int i=0; opts[1].str[i]; i++)
   {
        if(isdigit(opts[1].str[i])==0)
        {
            printk("sleep: invalid time interval %s\nTry 'sleep --help' for more information.\n", opts[1].str);
            return STATUS_OK;
        }
   }        
   
   main_sleep_opt_handler(cmd);
   
   return STATUS_OK;
}

struct cmd_t cmd_sleep = 
{
  .name = "sleep",
  .usage ="sleep [<ms>] [--help]",
  .help = "sleep(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tsleep\n"
                "SYNOPSIS : \n "
                "\tsleep [<ms>] [--help]\n"
                "DESCRIPTION : \n "
                "\tSleeps for the number of milliseconds specified.\n",   
  .cmd_opts =  cmd_sleep_opts,
  .handler = &cmd_sleep_handler,    
  .invalid_use_msg = "Invalid use of sleep command.\n"
                     "Type in sleep --help for more help.\n",
  .privilege = USER
};



