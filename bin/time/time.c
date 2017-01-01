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

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <time/time.h>
#include <time/opts/main_time.h>



struct cmd_opt_t* cmd_time_opts[] = 
{
    0
};

int cmd_time_handler(char* cmd)
{
   main_time_opt_handler(cmd);    
    
   return STATUS_OK;
}


struct cmd_t cmd_time = 
{
  .name = "time",
  .usage ="time [--help]",
  .help = "time(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\ttime\n"
                "SYNOPSIS : \n "
                "\ttime [--help]\n"
                "DESCRIPTION : \n "
                "\tPrints out time from in format hour minutes second\n",
  .cmd_opts =  cmd_time_opts,
  .handler = &cmd_time_handler, /*
  .invalid_use_msg = "Invalid use of time command.\n"
                     "Type in time --help for more help.\n", */
  .privilege = USER
};







