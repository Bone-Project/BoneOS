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

int cmd_cls_color_handler()
{
  return STATUS_OK;
}

struct cmd_opt_t cmd_cls_opt_color = 
{
    .help = "cls 1) \t BoneOS Terminal Manual \n "
                "NAME : \n"
                "\tcls --color\n"
                "SYNOPSIS : \n "
                "\tcls  [--color <fg-color> <bg-color>] [--color <--help>] "
                "DESCRIPTON : \n "
                "\tClears the terminal with accordance to the "
                "\tspecified foregroud and background colors. " ,      

        .cmd_opt_name = "--color" ,
        .handler = &cmd_cls_color_handler
};
