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
#include <uname/uname.h>
#include <uname/opts/main_uname.h>

struct cmd_opt_t* cmd_uname_opts[] =
{
    0
};

int cmd_uname_handler (char *cmd)
{
    main_uname_opt_handler (cmd);
    return STATUS_OK;
}

struct cmd_t cmd_uname =
{
  .name = "uname",
  .usage ="uname [option] [--help]",
  .help = "uname(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tuname\n"
                "SYNOPSIS : \n "
                "\tuname [option] [--help]\n"
                "DESCRIPTION : \n "
                "\tPrints out information about the OS.\n"
                "OPTIONS : \n "
                "\t Option Summary \n "
                "\t\t [-n] : prints the OS name\n "
                "\t\t [-a] : prints all the options\n "
                "\t\t [-r] : prints the current release\n "
                "\t\t [-p] : prints the current hardware platform\n",
  .cmd_opts =  cmd_uname_opts,
  .handler = &cmd_uname_handler,
  .invalid_use_msg = "Invalid use of uname command.\n"
                     "Type in uname --help for more help.\n",
  .privilege = USER
};
