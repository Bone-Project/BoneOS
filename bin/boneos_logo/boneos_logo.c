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
#include <unistd/unistd.h>
#include <boneos_logo/opts/main_boneos_logo.h>
#include <boneos_logo/opts/boneos_logo_color.h>

struct cmd_opt_t* cmd_boneos_logo_opts[] = 
{
  &cmd_boneos_logo_opt_color
  ,0
};

int boneos_logo_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    if(num_opts == 1)
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
    
    
    main_boneos_opt_handler(cmd);
    
    return STATUS_OK;
}

struct cmd_t cmd_boneos_logo = 
{
  .name = "boneos_logo",
  .usage = "boneos_logo [--help]  [-color <fg-color> <bg-color>] [-color --def] [-color <--help>] ",
  .help = "boneos_logo(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tboneos_logo\n"
                "SYNOPSIS : \n "
                "\tboneos_logo [--help]  [-color <fg-color> <bg-color>] [-color --def] [-color <--help>]\n"
                "DESCRIPTION : \n "
                "\tCommand that draws the BoneOS logo\n "
                "\tonto terminal. use the -color command\n "
                "\tto have a specific Foreground and Background Color\n"
                "MORE HELP : \n "
                "\t[boneos_logo -color--help] for help on -color option\n",   
  .cmd_opts =  cmd_boneos_logo_opts,
  .handler = &boneos_logo_handler,
  .invalid_use_msg = "Invalid use of boneos_logo command.\n"
                     "Type in boneos_logo --help for more help.\n",
  .privilege = USER
};

