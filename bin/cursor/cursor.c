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
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <cursor/cursor.h>
#include <cursor/opts/main_cursor.h>

struct cmd_opt_t* cmd_cursor_opts[] = 
{
    0
};

int cmd_cursor_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   if(num_opts < 1)
      printk(cmd_cursor.invalid_use_msg);
      
   main_cursor_opt_handler(cmd); 
   return STATUS_OK;
}


struct cmd_t cmd_cursor = 
{
  .name = "cursor",
  .usage ="cursor [-t <CRSR_START> <CRSR_END>] [-t block] [-t def]",
  .help = "cursor(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n"
                "\tcursor\n"
                "SYNOPSIS : \n "
                "\tcursor [-t <CRSR_START> <CRSR_END>]\n"
                "DESCRIPTION : \n"
                "\tOptions to change cursor attributes.\n",
                "OPTIONS : \n"
                "\t Option Summary \n"
                "\t\t [-t <CRSR_START> <CRSR_END>] : cursor now changes to custom type.\n"
                "\t\t [-t block] : cursor is changed to a block cursor (CRSR_START : 0, CRSR_END : 20)\n"
                "\t\t [-t def] : cursor changes to default underline.  (CRSR_START : 15, CRSR_END : 15)\n", 
  .cmd_opts =  cmd_cursor_opts,
  .handler = &cmd_cursor_handler,    
  .invalid_use_msg = "Invalid use of cursor command.\n"
                     "Type in cursor --help for more help.\n"
};






