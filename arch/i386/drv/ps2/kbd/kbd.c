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

#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <io/io.h>
#include <libc/stdio/stdio.h>
#include <stdint.h>
#include <stddef.h>
#define KBD_PRE
#include <drv/kbd/kbd.h>
#undef KBD_PRE
#include <stdbool.h>
#include <libc/assertk.h>
#include <cpu/interrupts/irq.h>
#include <drv/kbd/scancodes.h>


struct _kbd_info kbd_info;
char key;

char key_press(uint8_t scancode)
{
    if(kbd_info.is_shift == true)
       return (kbd_layouts[QWERTY_EN_INDEX]->scancode_shift[scancode]);
    else
       return (kbd_layouts[QWERTY_EN_INDEX]->scancode_no_shift[scancode]);
}

void key_release(uint8_t scancode)
{
   if(kbd_info.kbd_enc_info == KBD_QWERTY_LEFT_SHIFT_RELEASE ||
      kbd_info.kbd_enc_info == KBD_QWERTY_RIGHT_SHIFT_RELEASE)
          kbd_info.is_shift = false;
}

void kbd_init_pointers()
{
    /*Initalize Function Pointers*/
    kbd_info.routines.tests.bat_test = &bat_test;
    kbd_info.tests.bat_test = (*kbd_info.routines.tests.bat_test)();
    assertk(kbd_info.tests.bat_test);
    kbd_info.routines.key_ev.key_press = &key_press;
    kbd_info.routines.key_ev.key_release = &key_release;

    led_light(false,false,false);
    kbd_info.is_shift = false;
    kbd_info.is_caps = false;
}

void key_handler()
{
   switch(key)
   {
    case KBD_QWERTY_LEFT_SHIFT_PRESS:
    case KBD_QWERTY_RIGHT_SHIFT_PRESS:
      kbd_info.is_shift = true;
      break;
    case '\t':
         printk("\t");
         break;
     case '\b':
         printk("\b");
         break;
    case '\n' :
         printk("\n");
         break;
    default:
         printk("%c", key);
         break;
   }
}

void kbd_handler(int_regs *r)
{
  kbd_info.kbd_enc_info =kbd_enc_read_input_buf();
  if(kbd_info.kbd_enc_info & 0x80)
        (*kbd_info.routines.key_ev.key_release)(kbd_info.kbd_enc_info);
    else
    {
        key = (*kbd_info.routines.key_ev.key_press)(kbd_info.kbd_enc_info);
        key_handler();
    }
}

void init_kbd()
{
  kbd_init_pointers();
  install_irq_handler(IRQ_NUM_KBD,kbd_handler);	
}

void uninit_kbd()
{
  uninstall_irq_handler(IRQ_NUM_KBD);
}