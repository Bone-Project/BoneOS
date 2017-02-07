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
 **     Ashish Ahuja <Fortunate-MAN>
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <echo/echo.h>
#include <echo/opts/main_echo.h>



struct cmd_opt_t* cmd_echo_opts[] =
{
    0
};

int cmd_echo_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   if(num_opts == 1)
   {
     printk(cmd_echo.invalid_use_msg);
     return STATUS_FAIL;
   }

   return main_echo_opt_handler(cmd);
}


struct cmd_t cmd_echo =
{
  .name = "echo",
  .usage ="echo [value] [--help]",
  .help = "echo(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\techo\n"
                "SYNOPSIS : \n "
                "\techo [value] [--help]\n"
                "DESCRIPTION : \n "
                "\tPrints out the VALUE listed by option\n",
  .cmd_opts =  cmd_echo_opts,
  .handler = &cmd_echo_handler,
  .invalid_use_msg = "Invalid use of echo command.\n"
                     "Type in echo --help for more help.\n",
  .privilege = USER
};









