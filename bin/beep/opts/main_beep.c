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

 **     Amanuel Bogale<amanuel2>: start
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <string/string.h>
#include <sh/values.h>
#include <beep/beep.h>
#include <beep/opts/main_beep_count.h>
#include <drv/pcspkr/pcspkr.h>
#include <string/string.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>

int main_beep_opt_handler (char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);

  if(strcmp(opts[1].str, "-n")==0)
    cmd_beep_opt_count.handler(cmd);
  else if(strcmp(opts[1].str, "-f")==0)
  {
    int freq_set = strtoi((char*)opts[2].str, 0, 16);
    pcspkr_beep(freq_set);
  }
  else if(strcmp(opts[1].str, "--help")==0)
    printk(cmd_beep.help);
  else
    pcspkr_beep(9000);

  return STATUS_OK;
}
