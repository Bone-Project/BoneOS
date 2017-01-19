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

#include <stddef.h>
#include <stdint.h>
#include <misc/status_codes.h>
#include <sh/shell.h>
#include <unistd/unistd.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <string/string.h>

int cmd_beep_count_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);

   printk("Handling BEEP COUNT OPTION");

   return STATUS_OK;
}

struct cmd_opt_t cmd_beep_opt_count =
{
    .help =  "boneos_logo(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tboneos_logo -color\n "
                "SYNOPSIS : \n "
                "\tboneos_logo [--help]  [-color <fg-color> <bg-color>] [-color --def]\n \t[-color <--help>]\n"
                "DESCRIPTION : \n "
                "\tDraws the BoneOS Logo with accordance to the\n "
                "\tcolor with the -color command and providing it\n "
                "\tspecified foreground and background colors.\n "
                "OPTIONS : \n "
                "\t Option Summary \n "
                "\t\t[-color <fg-color> <bg-color>] : Draws the BoneOS logo.\n "
                "\t\t 0 = Black \t 8 = Gray\n "
                "\t\t 1 = Blue  \t 9 = Light Blue\n "
                "\t\t 2 = Green \t A = Light Green\n "
                "\t\t 3 = Aqua  \t B = Light Aqua\n "
                "\t\t 4 = Red   \t C = Light Red\n "
                "\t\t 5 = Purple\t D = Light Purple\n "
                "\t\t 6 = Yellow\t E = Light Yellow\n "
                "\t\t 7 = White \t F = Bright White\n "
                "\t\t--def : Clears to default (BG : 0x7 , FG : 0x0)\n ",
        .cmd_opt_name = "-color" ,
        .handler = &cmd_beep_count_handler,
        .invalid_use_msg = "Invalid Use of -color option. Use command boneos_logo -color --help for\n"
                           "instructions on how to use the clear command\n"
};
