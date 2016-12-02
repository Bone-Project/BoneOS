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

#include <stdio/stdio.h>
#include <misc/status_codes.h>
#include <term/terminal.h>

struct cmd_opt_t* cmd_boneos_logo_opts[] = 
{
  0
};

int boneos_logo_handler(char* cmd)
{
    printk("*********** ********** *      * *******      **********  *********\n");
    printk("*         * *        * * *    * *            *        *  *\n");
    printk("*         * *        * *  *   * *            *        *  *\n");
    printk("*   ******* *        * *   *  * *******      *        *  *********\n");
    printk("*         * *        * *    * * *            *        *          *\n");
    printk("*         * *        * *     ** *            *        *          *\n");
    printk("*********** ********** *      * *******      **********  *********\n");
    
    return STATUS_OK;
}

struct cmd_t cmd_boneos_logo = 
{
  .name = "boneos_logo",
  .usage = "boneos_logo [--help]  [--color <fg-color> <bg-color>]   [--color <--help>] ",
  .help = "boneos_logo(1) \t BoneOS Terminal Manual \n "
                "NAME : \n"
                "\boneos_logo\n"
                "SYNOPSIS : \n "
                "\boneos_logo [--help]  [--color <fg-color> <bg-color>] [--color <--help>] "
                "DESCRIPTION : \n "
                "\tCommand that draws the BoneOS logo "
                "\tonto terminal. use the --color command "
                "\tto have a specific Foreground and Background Color" ,   
  .cmd_opts =  cmd_boneos_logo_opts,
  .handler = &boneos_logo_handler                     
};
