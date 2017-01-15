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
#include <stdlib/stdlib.h>
#include <stdlib/itoa/itoa.h>
#include <string/string.h>
#include <sh/values.h>
#include <uptime/uptime.h>
#include <sh/shell.h>

int main_uptime_opt_handler (char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);

    rtc_t curr = rtc_get_time();
    rtc_t time_since_start;
    time_since_start.second = 0;
    time_since_start.month = curr.month - start_time.month;
    time_since_start.day = curr.day - start_time.day;
    time_since_start.hour = curr.hour - start_time.hour;
    time_since_start.minute = (uint8_t)(curr.minute - start_time.minute);
    time_since_start.second =(uint8_t) (curr.second - start_time.second);
    if (num_opts == 1)
    {
        printk ("%x:%x", time_since_start.minute, time_since_start.second);
        return STATUS_OK;
    }
    else if (num_opts > 1)
    {
        if (strcmp (opts [1].str, "--help") == 0)
        {
            printk (cmd_uptime.help);
            return STATUS_OK;
        }
        else
        {
            printk (cmd_uptime.invalid_use_msg);
            return STATUS_OK;
        }
    }

    return STATUS_OK;
}


