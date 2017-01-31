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

 **     Amanuel Bogale<amanuel2>: start
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <beep/beep.h>
#include <beep/opts/main_beep.h>

struct cmd_opt_t* cmd_beep_opts[] =
{
    0
};

int cmd_beep_handler (char *cmd)
{
    main_beep_opt_handler (cmd);
    return STATUS_OK;
}

struct cmd_t cmd_beep =
{
  .name = "beep",
  .usage ="beep [-n milliseconds] [-f freq] [--help]",
  .help = "beep(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tbeep\n"
                "SYNOPSIS : \n "
                "\tbeep [-n milliseconds] [-f freq] [-S] [--help]\n"
                "DESCRIPTION : \n "
                "\tBeeps via the PC Speaker. if used without\n"
                "\t-n option, defaults to beep forever. If freq not\n"
                "\tset with -f then default if of 1000 htz.\n",
  .cmd_opts =  cmd_beep_opts,
  .handler = &cmd_beep_handler,
  .invalid_use_msg = "Invalid use of beep command.\n"
                     "Type in beep --help for more help.\n",
  .privilege = USER
};
