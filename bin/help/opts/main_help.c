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
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <help/help.h>
#include <help/opts/help_cmd_opt.h>

int main_help_opt_handler(char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);

    if(strcmp(opts[1].str,"-cmd")==0)
    {
        if(strcmp(opts[2].str,"--help")==0)
            printk(cmd_help_opt_cmd.help);
        else
            return cmd_help_opt_cmd.handler(cmd);
    }
    else if(strcmp(opts[1].str , "--help")==0)
    {
        printk(cmd_help.help);
    }
    else
    {
        printk(cmd_help.invalid_use_msg);
        return STATUS_FAIL;
    }

    return STATUS_OK;
}


