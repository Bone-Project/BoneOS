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
#include <sh/shell.h>
#include <stdlib/stdlib.h>

enum SLEEP_MODE
{
  SECONDS = (long) 1000,
  MINUTES = (long) 60000,
  HOURS   = (long) 3600000,
  DAYS 	  = (long) 86400000,
  YEARS   = (long) 31536000000
};

int main_sleep_opt_handler(char *cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   size_t num_len = strlen(opts[1].str);
   enum SLEEP_MODE MODE;
   if(opts[1].str[num_len-1] == 's') MODE = SECONDS;
   else if(opts[1].str[num_len-1] == 'm') MODE = MINUTES;
   else if(opts[1].str[num_len-1] == 'h') MODE = HOURS;
   else if(opts[1].str[num_len-1] == 'd') MODE = DAYS;
   else MODE=SECONDS;

   int __seconds_sleep = atoi(opts[1].str);
   printk(" \n");
   sleep(__seconds_sleep * MODE);
   
   return STATUS_OK;
}




