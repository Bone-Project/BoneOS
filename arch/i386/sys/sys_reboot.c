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

#include <stdint.h> 
#include <misc/status_codes.h>
#include <misc/asm_util.h>
#include <stddef.h>
#include <io/io.h>
#define KBD_PRE
#include <drv/ps2/kbd/kbd.h>
#undef KBD_PRE

int root_sys_reboot(void)
{
    uint8_t _status = 0x02;
    while (_status & 0x02)
        _status = inb(KBD_CTRL_STATS_REG);
    outb(KBD_CTRL_CMD_REG, KBD_ENCODER_CMD_SEND_SYSTEM_RESET);
    kbd_ctrl_send_cmd(KBD_CTRL_STATS_MASK_OUT_BUF);
    kbd_enc_send_cmd(KBD_ENCODER_CMD_SEND_SYSTEM_RESET);
  return STATUS_OK;
}
