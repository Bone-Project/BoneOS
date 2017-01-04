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

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <io/io.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/ps2/kbd/utils.h>

/*
 *  Keyboard Ctrl :    
 * Read status register
 * and read command to ctrl
 */
uint8_t kbd_ctrl_read_status_reg()
{
  return (inb(KBD_CTRL_STATS_REG));   
}

void kbd_ctrl_send_cmd(uint8_t cmd)
{
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb(KBD_CTRL_CMD_REG,cmd);
}

/*
 *  Keyboard Encoder :    
 * Read encoder input buffer
 * and send command to encoder
 */
uint8_t kbd_enc_read_input_buf()
{
    return (inb(KBD_ENC_INPUT_BUF_REG));    
}

//Send command to encoder
void kbd_enc_send_cmd(uint8_t cmd)
{
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb(KBD_ENC_CMD_REG,cmd);
}

//Basic Assurance Test(Self Test)
bool bat_test(void)
{
    kbd_ctrl_send_cmd(KBD_CTRL_CMD_SELF_TEST);
    
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_OUT_BUF) == 0);
    
    return (kbd_enc_read_input_buf () == 0x55) ? true : false;
}

//Set the LED Lights if true
bool led_light(bool scroll, bool num, bool caps)
{
  uint8_t data_final = 0x0;
  if(scroll) data_final |= KBD_SCROLL_LED_ON;
  if(num) data_final |= KBD_NUM_LED_ON;
  if(caps) data_final |= KBD_CAPS_LOCK_ON;

  kbd_info.led.num_lock = num;
  kbd_info.led.caps_lock = caps;
  kbd_info.led.scroll_lock = scroll;

  kbd_enc_send_cmd(KBD_ENCODER_CMD_SET_LED);
  kbd_enc_send_cmd(data_final);
  return true;
}





