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
 **  @main_author : Ashish Ahuja
 **
 **  @contributors:

 **     Ashish Ahuja<Fortunate-MAN>: start
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <uptime/uptime.h>
#include <uptime/opts/main_uptime.h>

struct cmd_opt_t* cmd_uptime_opts[] =
{
    0
};

int cmd_uptime_handler (char *cmd)
{
    main_uptime_opt_handler (cmd);
    return STATUS_OK;
}

struct cmd_t cmd_uptime =
{
  .name = "uptime",
  .usage ="uptime [--help]",
  .help = "uptime(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tuptime\n"
                "SYNOPSIS : \n "
                "\tuptime [option] [--help]\n"
                "DESCRIPTION : \n "
                "\tTells how long the system has been running.\n",
  .cmd_opts =  cmd_uptime_opts,
  .handler = &cmd_uptime_handler,
  .invalid_use_msg = "Invalid use of uptime command.\n"
                     "Type in uptime --help for more help.\n",
  .privilege = USER
};


