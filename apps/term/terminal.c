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

#include <term/terminal.h>
#include <term/values.h>
#include <clear/clear.h>
#include <boneos_logo/boneos_logo.h>
#include <stdio/stdio.h>
#include <strcmp/strcmp.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>

extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 


struct typed_cmd cmd_active;

struct cmd_t *cmds[] = 
{
  &cmd_clear,
  &cmd_boneos_logo
  ,0
};

int termcmp(const char* cmd, const char* value)
{
  size_t num_opts_cmp = get_opt_count(value);
  str_t opts_cmp[num_opts_cmp];
  get_opt(value,opts_cmp);   
  if(strcmp(opts_cmp[0].str,cmd)==0)
    return 0;
  return 1;  
}

void terminal_scroll(int offset)
{
  /*Terminal Offset*/
  // ****
  // ****
  // Remove first row
  
}

int __found = 0;

void loop_terminal()
{
  while(1)
  {
    int FG__ = FG;
    int BG__ = BG;
    if(FG==0x7 && BG==0x0)
    {
      printck(2,0,"%s@boneos:",VAR_USER);
      printck(1,0,"%s",VAR_PWD);
      printck(0x0,0x7,"");
      printck(0x7,0x0," $ ");
    }
    else
    {
      printk("%s@boneos:",VAR_USER);
      printk("%s",VAR_PWD);
      printk(" $ ");
    }
    FG = FG__;
    BG = BG__;
    
    scank(true,true, "%s" , cmd_active.value);
    
    for(int i=0; cmds[i]; i++)
    {
      if(termcmp(cmds[i]->name, cmd_active.value)==0)
      {
        cmds[i]->handler(cmd_active.value);
        __found = 1;
      }
    }
    
    if(__found == 0)
      printk("Invalid Command\n");
      
    __found = 0;  
  }
}

void init_terminal()
{
  cmds[CMD_BONEOS_LOGO_INDEX]->handler("boneos_logo");
  loop_terminal();
}

