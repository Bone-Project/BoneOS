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
#include <watch/watch.h>
#include <watch/opts/main_watch.h>

struct cmd_opt_t* cmd_watch_opts[] =
{
    0
};

int cmd_watch_handler (char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1)
    {
        printk (cmd_watch.invalid_use_msg);
        return STATUS_FAIL;
    }
    return main_watch_opt_handler (cmd);
}

struct cmd_t cmd_watch =
{
  .name = "watch",
  .usage ="watch [--help]",
  .help = "watch(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\twatch\n"
                "SYNOPSIS : \n "
                "\twatch [option] [command]\n"
                "DESCRIPTION : \n "
                "\tPrints out the current user.\n"
                "OPTIONS : \n "
                "[-n <seconds>] Sets the interval to the number of seconds specified.\n",
  .cmd_opts =  cmd_watch_opts,
  .handler = &cmd_watch_handler,
  .invalid_use_msg = "Invalid use of watch command.\n"
                     "Type in watch --help for more help.\n",
  .privilege = USER
};


