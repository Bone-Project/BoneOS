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
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <string/string.h>
#include <stdlib/stdlib.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <help/opts/help_cmd_opt.h>
#include <help/opts/main_help.h>
#include <bin/boneshell/boneshell.h>

struct cmd_opt_t* cmd_help_opts[] =
{
    &cmd_help_opt_cmd
    ,0
};

int cmd_help_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    if (num_opts == 1)
    {
        printk("BoneOS Shell. Type in \"<cmd_name> --help\" for more help on that command\n");
        printk("or \"help -cmd <cmd_name>\"\n\n");
        printk("Commands\n");
        printk("--------\n");
        for (int i = 0; i < total_cmd; i += 2) {
            printk("%d : %s", i + 1, cmds[i]->name);

            if (i + 1 < total_cmd)
            {
                for (unsigned int o = 0;
                    o < video_driver_width / 2 - 5 - strlen(itoa(i)) - strlen(cmds[i]->name);
                    o ++)
                    printk(" ");
                printk("%d : %s\n", i + 2, cmds[i + 1]->name);
            }
            else
                printk ("\n");
        }
        return STATUS_OK;
    }

    main_help_opt_handler(cmd);

    return STATUS_OK;
}

struct cmd_t cmd_help =
{
    .name = "help",
    .usage ="help [-cmd <cmd_name>] [--help]",
    .help = "help(1) \t\t\t\t BoneOS Terminal Manual \n"
            "NAME : \n "
            "\thelp\n"
            "SYNOPSIS : \n "
            "\thelp [-cmd <cmd_name>] [--help]\n"
            "DESCRIPTION : \n "
            "\tLists out all commands if called with no options\n "
            "\tbut if called with -cmd option calls help handler\n "
            "\tfor that command.\n"
            "MORE HELP : \n "
            "\t[help -cmd --help] for help on -cmd option\n",
    .cmd_opts =  cmd_help_opts,
    .handler = &cmd_help_handler,
    .invalid_use_msg = "Invalid use of help command.\n"
            "Type in help --help for more help.\n",
    .privilege = USER
};
