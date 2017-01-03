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
#include <pwd/pwd.h>
#include <pwd/opts/main_pwd.h>

struct cmd_opt_t* cmd_pwd_opts[] =
{
    0
};

int cmd_pwd_handler (char *cmd)
{
    main_pwd_opt_handler (cmd);
    return STATUS_OK;
}

struct cmd_t cmd_pwd =
{
  .name = "pwd",
  .usage ="pwd [--help]",
  .help = "pwd(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tpwd\n"
                "SYNOPSIS : \n "
                "\tpwd [option] [--help]\n"
                "DESCRIPTION : \n "
                "\tPrints out the current working directory.\n",
  .cmd_opts =  cmd_pwd_opts,
  .handler = &cmd_pwd_handler,
  .invalid_use_msg = "Invalid use of pwd command.\n"
                     "Type in pwd --help for more help.\n",
  .privilege = USER
};
