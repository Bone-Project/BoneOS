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
#include <drv/video/VGA/vga.h>
#include <strcmp/strcmp.h>
#include <drv/video/video.h>


struct typed_cmd cmd_active;


void logo()
{
    printk("*********** ********** *      * *******      **********  *********\n");
    printk("*         * *        * * *    * *            *        *  *\n");
    printk("*         * *        * *  *   * *            *        *  *\n");
    printk("*   ******* *        * *   *  * *******      *        *  *********\n");
    printk("*         * *        * *    * * *            *        *          *\n");
    printk("*         * *        * *     ** *            *        *          *\n");
    printk("*********** ********** *      * *******      **********  *********\n");
}

struct cmd_t *cmds[] = 
{
  &cmd_clear,
  &cmd_boneos_logo
  ,0
};

int termcmp(const char* cmd, const char* value)
{
  for(int i=0; value[i]; i++)
    if(value[i] != cmd[i])
      return 1;
  return 0;    
}


void loop_terminal()
{
  while(1)
  {
    printk("%s %s $ " , VAR_USER, VAR_PWD);
    scank(true, "%s" , cmd_active.value);
        
    for(int i=0; cmds[i]; i++)
      if(termcmp(cmds[i]->name, cmd_active.value)==0)
        cmds[i]->handler(cmd_active.value);    
  }
}

void init_terminal()
{
  cmds[CMD_BONEOS_LOGO_INDEX]->handler("boneos_logo");
  printck(0x5,0x3,"BoneOS Terminal\n");
  loop_terminal();
}

