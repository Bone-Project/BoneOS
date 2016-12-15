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
#include <term/terminal.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <reboot/reboot.h>
#include <string/string.h>
#include <io/io.h>
#include <misc/asm_util.h>
#include <sys/shutdown.h>
#include <shutdown/shutdown.h>



struct cmd_opt_t* cmd_shutdown_opts[] = 
{
    0
};

int cmd_shutdown_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(num_opts == 1)
     printk("SHUT DOWN STILL ON WORK\n");
   else if(strcmp(opts[2].str, "--help")==0)
      printk(cmd_shutdown.help);
   else 
        printk(cmd_shutdown.invalid_use_msg);
   
   return STATUS_OK;
}


struct cmd_t cmd_shutdown = 
{
  .name = "shutdown",
  .usage ="shutdown",
  .help = "shutdown(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n"
                "\tshutdown\n"
                "SYNOPSIS : \n "
                "\tshutdown\n"
                "DESCRIPTION : \n"
                "\tShut downs the Operating System.\n",
  .cmd_opts =  cmd_shutdown_opts,
  .handler = &cmd_shutdown_handler,    
  .invalid_use_msg = "Invalid use of shutdown command.\n"
                     "Type in shutdown --help for more help.\n",
  .privilege = ROOT
};





