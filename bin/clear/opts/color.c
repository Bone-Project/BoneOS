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
#include <term/terminal.h>


int cmd_clear_color_handler()
{
  
  return STATUS_OK;
}

struct cmd_opt_t cmd_clear_opt_color = 
{
    .help =  "clear(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n"
                "\tclear --color\n"
                "SYNOPSIS : \n "
                "\tclear  [--color <fg-color> <bg-color>] [--color <--help>] \n"
                "DESCRIPTION : \n"
                "\tClears the terminal with accordance to th\n"
                "\tcolor with the --color command and providing it\n"
                "\tspecified foregroud and background colors.\n"
                "OPTIONS : \n"
                "\t Option Summary \n"
                "<fg-color> : \n"
                "<bg-color> : \n", 
        .cmd_opt_name = "--color" ,
        .handler = &cmd_clear_color_handler
};
