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
#include <help/help.h>
#include <sleep/sleep.h>
#include <stdbool.h>
#include <echo/echo.h>
#include <string/string.h>
#include <cursor/cursor.h>
#include <reboot/reboot.h>

extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 

volatile bool TERMINAL_MODE = false;

volatile struct typed_cmd cmd_active;


struct cmd_t *cmds[] = 
{
  &cmd_clear,
  &cmd_boneos_logo,
  &cmd_help,
  &cmd_sleep,
  &cmd_echo,
  &cmd_cursor,
  &cmd_reboot
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

static bool is_contain_equal(char* s)
{
  while(*s)
    if(*s++ == '=')
        return true;
  return false;    
}

static str_t term_assignment_return_variable(str_t s)
{
  int counter = 0;
  str_t __return;
  for(int i=0; i<200;i++) __return.str[i]=0;
  
  while(s.str[counter] != '=') {
    __return.str[counter]+=s.str[counter];
    counter++;
  }
  return __return;
}

static str_t term_assignment_return_value(str_t s)
{
  int counter=0;
  int self_index=0;
  str_t __return;
  for(int i=0; i<200;i++) __return.str[i]=0;
  
  while(s.str[counter++] != '=');
 // counter+=1;
  for(; s.str[counter]; counter++)
  {
     __return.str[self_index++]+=s.str[counter];
  }
  
  return __return;
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
    

      if(is_contain_equal(cmd_active.value)==true)
      {
        str_t temp_str;
        strcpy(temp_str.str,cmd_active.value);
        
        char* key = term_assignment_return_variable(temp_str).str;
        char* val = term_assignment_return_value(temp_str).str;
        
        strcpy(__values.pairs[__values.index].val,val);
        strcpy(__values.pairs[__values.index].key,key);
        __found=1;
        __values.index++;
      }

    for(int i=0; cmds[i]; i++)
    {

      if(termcmp(cmds[i]->name, cmd_active.value)==0)
      {
        cmds[i]->handler(cmd_active.value);
        __found = 1;
      }
    }
    
    if(__found == 0)
    {
      printk("Invalid Command '%s' \n", cmd_active.value);
       printk("Try 'help' for more information.\n");
    }
      
    __found = 0;  
  }
}

void init_terminal()
{
  TERMINAL_MODE=true;
  __values.index=0;
  cmds[CMD_BONEOS_LOGO_INDEX]->handler("boneos_logo");
  loop_terminal();
}


