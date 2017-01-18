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
#include <sh/values.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <date/date.h>
#include <drv/cmos/rtc/rtc.h>

int main_date_opt_handler (char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);

    if (!strcmp (opts [1].str, "--help"))
    {
        printk (cmd_date.help);
        return STATUS_OK;
    }
    else if (num_opts == 1)
    {
        rtc_print_date();
        return STATUS_OK;
    }
    else
    {
        printk (cmd_date.invalid_use_msg);
        return STATUS_OK;
    }
}
