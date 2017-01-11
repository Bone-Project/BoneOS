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
#include <drv/cmos/rtc/rtc.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <date/opts/main_date.h>
#include <date/date.h>

struct cmd_opt_t* cmd_date_opts[] =
{
    0
};

int cmd_date_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   if(num_opts >= 1)
   {
        main_date_opt_handler (cmd);
        return STATUS_OK;
   }
   return STATUS_OK;
}


struct cmd_t cmd_date =
{
  .name = "date",
  .usage ="date [--help]",
  .help = "date(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tdate\n"
                "SYNOPSIS : \n "
                "\tdate [--help]\n"
                "DESCRIPTION : \n "
                "\tPrints out the Date with specific format\n",
  .cmd_opts =  cmd_date_opts,
  .handler = &cmd_date_handler,
  .invalid_use_msg = "Invalid use of date command.\n"
                     "Type in date --help for more help.\n",
  .privilege = USER
};









