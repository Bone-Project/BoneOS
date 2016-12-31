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


#include <sh/values.h>
#include <clear/clear.h>
#include <boneos_logo/boneos_logo.h>
#include <stdio/stdio.h>
#include <strcmp/strcmp.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <sh/shell.h>
#include <stdbool.h>
#include <help/help.h>
#include <pwd/pwd.h>
#include <sleep/sleep.h>
#include <echo/echo.h>
#include <string/string.h>
#include <cursor/cursor.h>
#include <reboot/sbin_cmd_reboot.h>
#include <poweroff/sbin_cmd_poweroff.h>
#include <boneshell/boneshell.h>
#include <assertk.h>
#include <drv/driver.h>
#include <sh/built-in/exit/exit.h>



volatile bool TERMINAL_MODE = false;
volatile uint32_t cmd_active_index=0;


volatile uint32_t shell_instance_cnt = 0;

volatile struct typed_cmd cmd_active;



struct cmd_t *cmds[] =
{
  &cmd_clear,
  &cmd_boneos_logo,
  &cmd_help,
  &cmd_sleep,
  &cmd_echo,
  &cmd_cursor,
  &cmd_reboot,
  &cmd_poweroff,
  &cmd_boneshell,
  &cmd_exit,
  &cmd_pwd
  ,0
};

void init_terminal()
{
  assertkm(device_initalized(KBD_DRIVER_INDEX) , "Keyboard not intalized for starting shell!");
  TERMINAL_MODE=true;
  cmds[CMD_BONEOS_LOGO_INDEX]->handler("boneos_logo");
  cmds[CMD_BONESHELL_INDEX]->handler("boneshell");
  TERMINAL_MODE=false;
}





