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


#define SLEEP_MODE_SECONDS  1000
#define SLEEP_MODE_MINUTES  60000
#define SLEEP_MODE_HOURS    3600000
#define SLEEP_MODE_DAYS     86400000
#define SLEEP_MODE_YEARS    31536000000

static int current_sleep_mode=0;

int main_sleep_opt_handler(char *cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   size_t num_len = strlen(opts[1].str);
   
   if(opts[1].str[num_len-1] == 's') current_sleep_mode = SLEEP_MODE_SECONDS;
   else if(opts[1].str[num_len-1] == 'm') current_sleep_mode = SLEEP_MODE_MINUTES;
   else if(opts[1].str[num_len-1] == 'h') current_sleep_mode = SLEEP_MODE_HOURS;
   else if(opts[1].str[num_len-1] == 'd') current_sleep_mode = SLEEP_MODE_DAYS;
   else current_sleep_mode=SLEEP_MODE_SECONDS;

   int __seconds_sleep = atoi(opts[1].str);
   printk(" \n");
   sleep(__seconds_sleep * current_sleep_mode);
   
   return STATUS_OK;
}




