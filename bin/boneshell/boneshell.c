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
#include <unistd/unistd.h>
#include <boneshell/boneshell.h>
#include <string/string.h>
#include <sh/shell.h>
#include <sh/values.h>
#include <sh/utils.h>
#include <drv/video/VGA/vga.h>
#include <libc/stdio/scank/scank.h>
#include <drv/ps2/kbd/kbd.h>
#include <../platform/pc/drv/ps2/kbd/kbd.c>

extern volatile bool TAB_PREVIOUS_VALUE_SET;
extern volatile char* TAB_PREVIOUS_VALUE;
extern void key_handler_util(int key);

struct cmd_opt_t* cmd_boneshell_opts[] =
{
  0
};


int __found = 0;
volatile bool exit_set__shell = false;
volatile bool tab_multiple_opts = false;
volatile bool tab_one_opt = false;
bool executed_internally=false;

void removeSpaces(char* source)
{
  char* i = source;
  char* j = source;
  while(*j != 0)
  {
    *i = *j++;
    if(*i != ' ')
      i++;
  }
  *i = 0;
}


void loop_terminal()
{
  shell_instance_cnt+=1;
  printk("SHELL INSTANCE #%d\n",shell_instance_cnt);
  while(1)
  {
    start_shell:;
    int FG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg;
    int BG__ = video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg;
    if(video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg==0x7 && video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg==0x0)
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
    video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg = FG__;
    video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg = BG__;


    scank(true,true, "%s" , cmd_active.value);

    if(tab_multiple_opts==true)
    {
     tab_multiple_opts=false;
     goto start_shell;
    }
    else if(tab_one_opt == true)
    {
      tab_one_opt = false;
      strcpy (cmd_active.value, tab__);
      executed_internally = true;
      removeSpaces (cmd_active.value);
    }


    //removeSpaces(cmd_active.value);
    if(strcmp(cmd_active.value, "exit")==0)
    {
      shell_instance_cnt-=1;
      printk("EXITED SHELL INSTANCE #%d\n",shell_instance_cnt+1);
      goto end_shell;
    }

    for(int i=0; cmds[i]; i++)
    {
      if(termcmp(cmds[i]->name, cmd_active.value)==0)
      {
        if(executed_internally==true)
        {
          executed_internally=false;
          printk("EXECUTED INTERNALLY\n");
        }
        cmds[i]->handler(cmd_active.value);
        __found = 1;
      }
    }

    if(__found == 0 && cmd_active.value [0] != '\0')
    {
      printk("Invalid Command '%s' \n", cmd_active.value);
      printk("Try 'help' for more information.\n");
    }

    __found = 0;
    cmd_active_index++;
  }
 end_shell:;
}
int boneshell_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);

    if(strcmp(opts[1].str,"--help")==0)
        printk(cmd_boneshell.help);
    else if(num_opts==1)
       loop_terminal();
    else
        printk(cmd_boneshell.invalid_use_msg);

    return STATUS_OK;
}

struct cmd_t cmd_boneshell =
{
  .name = "boneshell",
  .usage = "boneshell [--help] ",
  .help = "boneshell(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n "
                "\tboneshell\n"
                "SYNOPSIS : \n "
                "\tboneshell [--help]\n"
                "DESCRIPTION : \n "
                "\tCreates another instance of a shell being \n "
                "\tthe child of the previous parent shell process.\n "
                "\tcommand exit used to stop this child shell process.\n "
                "\ttype exit --help for more on exit command\n ",
  .cmd_opts =  cmd_boneshell_opts,
  .handler = &boneshell_handler,
  .invalid_use_msg = "Invalid use of boneshell command.\n"
                     "Type in boneshell --help for more help.\n",
  .privilege = USER
};



