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
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <term/terminal.h>
#include <stdlib/stdlib.h>
#include <cursor/cursor.h>
#include <drv/video/video.h>


int main_cursor_opt_handler(char *cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   if(strcmp(opts[1].str,"--help")==0)
     printk(cmd_cursor.help); 
   else if(strcmp(opts[1].str,"-t")==0)
   {
      if(strcmp(opts[2].str,"def")==0)
         video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor(terminal_row,terminal_column,15,15);
      else if(strcmp(opts[2].str,"block")==0)   
         video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor(terminal_row,terminal_column,0,20);
      else if((strcmp(opts[2].str,"")!=0) || (strcmp(opts[3].str,"")!=0))
      {
         printk("%s , %s", opts[2].str, opts[3].str);
         int _CRSR_START = atoi(opts[2].str);
         int _CRSR_END = atoi(opts[3].str);
         video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor(terminal_row,terminal_column,_CRSR_START,_CRSR_END);
      }
      else
         printk(cmd_cursor.invalid_use_msg);
   }
   else
     printk(cmd_cursor.invalid_use_msg);
     
  return STATUS_OK;
}

