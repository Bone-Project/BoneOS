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
#include <drv/ps2/kbd/kbd.h>
#undef KBD_PRE
#include <stdbool.h>
#include <libc/assertk.h>
#include <libc/ctype/toupper/toupper.h>
#include <cpu/interrupts/irq.h>
#include <drv/ps2/kbd/scancodes.h>


struct _kbd_info kbd_info;

char key_press(uint8_t scancode)
{
  // printk("PRESS : %d\n" , scancode);
    if(kbd_info.is_shift == true)
       return (kbd_layouts[QWERTY_EN_INDEX]->scancode_shift[scancode]);
    else
       return (kbd_layouts[QWERTY_EN_INDEX]->scancode_no_shift[scancode]);
}

void key_release(uint8_t scancode)
{
  //printk("RELEASE : %d\n" , scancode);
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

    kbd_info.until_enter.active = false;
}

void wait_until_enter(char key)
{
  if(kbd_info.until_enter.active==true)
  {
    kbd_info.until_enter.buffer[kbd_info.until_enter.index++] = key;
  }
}

void key_handler()
{
   switch(kbd_info.key)
   {
    case KBD_QWERTY_LEFT_SHIFT_PRESS:
    case KBD_QWERTY_RIGHT_SHIFT_PRESS:
      kbd_info.is_shift = true;
      break; 
    case KBD_QWERTY_CAPS_PRESS:
       led_light(false,false,true);
        if(kbd_info.is_caps == true)
          kbd_info.is_caps = false;
        else
           kbd_info.is_caps = true;
      // (kbd_info.is_caps == true) ? false : true;
      break;  
      case KBD_QWERTY_ENTER_PRESS:
        kbd_info.is_enter = true;
        kbd_info.until_enter.active = false;
        /*CLEAR STRING TODO*/
        printk("\n");
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
         if(kbd_info.is_caps == false)
            printk("%c", kbd_info.key);
         else
            printk("%c", toupper(kbd_info.key)); 

          if(kbd_info.until_enter.active == true)
              wait_until_enter(kbd_info.key);
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
        kbd_info.key = (*kbd_info.routines.key_ev.key_press)(kbd_info.kbd_enc_info);
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