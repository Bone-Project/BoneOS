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
#include <cls/cls.h>
#include <stdio/stdio.h>
#include <drv/video/VGA/textmode/80x25/cls.h>

// struct cmd *commands[] = 
// {
//   &cmd_cls
//   ,0
// };

struct typed_cmd cmd_active;

void logo()
{
    cls_vga_80_x_25();
    printk("*********** ********** *      * *******      **********  *********\n");
    printk("*         * *        * * *    * *            *        *  *\n");
    printk("*         * *        * *  *   * *            *        *  *\n");
    printk("*   ******* *        * *   *  * *******      *        *  *********\n");
    printk("*         * *        * *    * * *            *        *          *\n");
    printk("*         * *        * *     ** *            *        *          *\n");
    printk("*********** ********** *      * *******      **********  *********\n");
}


void loop_terminal()
{
  while(1)
  {
        printk("%s %s $ " , VAR_USER, VAR_PWD);
        scank(true, "%s" , cmd_active.value);
        printk("TYPED : %s \n" , cmd_active.value);
  }
}

void init_terminal()
{
  logo();
  printck(0x5,0x3,"BoneOS Terminal\n");
  loop_terminal();
}

