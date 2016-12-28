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

#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <unistd/unistd.h>
#include <string/string.h>
#include <sh/shell.h>
#include <sh/built-in/exit/exit.h>

extern volatile bool exit_set__shell;

struct cmd_opt_t* cmd_exit_opts[] = 
{
  0
};

int exit_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);
    
    if(num_opts==1) 
    {
        exit_set__shell=true;
        return STATUS_OK;
    }
    else if(strcmp(opts[1].str,"--help")==0)
        printk(cmd_exit.help);
    else    
        printk(cmd_exit.invalid_use_msg);
   
    return STATUS_OK;
}

struct cmd_t cmd_exit = 
{
  .name = "exit",
  .usage = "exit [--help] ",
  .help = "exit(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\texit\n"
                "SYNOPSIS : \n "
                "\texit [--help]\n"
                "DESCRIPTION : \n "
                "\tCommand to exit the current \n "
                "\tshell process\n",
  .cmd_opts =  cmd_exit_opts,
  .handler = &exit_handler,
  .invalid_use_msg = "Invalid use of exit command.\n"
                     "Type in exit --help for more help.\n",
  .privilege = USER
};