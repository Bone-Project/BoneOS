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

#include <io/io.h>
#include <misc/status_codes.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <libc/stdio/stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <drv/ps2/kbd/kbd.h>
#include <stdbool.h>
#include <libc/assertk.h>
#include <libc/ctype/ctype.h>
#include <drv/ps2/kbd/scancodes.h>
#include <libc/stdio/scank/scank.h>
#include <misc/status_codes.h>
#include <term/terminal.h>
#include <ctype/ctype.h>
#include <drv/video/video.h>
#include <drv/driver.h>
#include <drv/video/VGA/vga.h>
#include <drv/video/VGA/textmode/update_cursor.h>



volatile struct kbd_info_t kbd_info;
volatile int INDEX_CURSOR_POSITION=0;
volatile bool UP_KEY_ACTIVE=true;


//Is this getting emulated at a terminal
extern volatile bool TERMINAL_MODE;

//getchar();
extern volatile bool __get_char_set;
extern volatile char __get_char_chr;


/*
 * @function key_press:
 *     Nested Function under
 *     @kbd_handler , and called
 *     if Key is pressed.
 *
 *     @param scancode:
 *          Scancode in HEX Format.
 *     @return char:
 *          Returns character from that
 *          scancode in HEX Format.
 */
int key_press(uint8_t scancode)
{
    if(kbd_info.is_shift)
       return (kbd_layouts[kbd_info.current_kbd_layout_index]->scancode_shift[scancode]);
    else
       return (kbd_layouts[kbd_info.current_kbd_layout_index]->scancode_no_shift[scancode]);
}

/*
 * @function key_release:
 *     Nested Function under
 *     @kbd_handler , and called
 *     if Key is released.
 *
 *     @param scancode:
 *          Scancode in HEX Format.
 */
void key_release(uint8_t scancode)
{
  if (
      kbd_layouts[kbd_info.current_kbd_layout_index]->scancode_no_shift[scancode] == KBD_LEFT_SHIFT_PRESS_ID || 
      kbd_layouts[kbd_info.current_kbd_layout_index]->scancode_no_shift[scancode] == KBD_RIGHT_SHIFT_PRESS_ID
     )  
        kbd_info.is_shift = false;
}

/*
 * @function kbd_early_init:
 *      Stuff to initalize
 *      before installing
 *      the PS/2 Keyboard
 */
void kbd_early_init()
{
    kbd_info.tests.bat_test = bat_test();
    
    if(!kbd_info.tests.bat_test)
    {
        kbd_driver.status = STATUS_DRIVER_MALFUNCTION;
        printck(0x3,0x1,"BAT TEST FAILED");
    }
    else
        kbd_driver.status = STATUS_DRIVER_OK;


    led_light(false,false,false);
    kbd_info.is_shift = false;
    kbd_info.is_caps = false;

    active_scank = false;
    print_scank = false;

    kbd_info.current_kbd_layout_index = QWERTY_USA_INDEX;
}



/*
 * @utility wait_until_enter
 *      Utility for Scank , to
 *      wait and store string 
 *      until enter is pressed
 */
void wait_until_enter(char key)
{
    buffer_scank[index_scank++] = key;
    buffer_scank[index_scank] = 0;
}

/*
 * @utility inc_al
 *      INcrements Position
 *      and adds to length input.
 *      used for when character typed.
 */

static inline void inc_al()
{
    INDEX_CURSOR_POSITION++;
    LENGTH_INPUT++;
}


/*
 * @utility key_handler_util
 *      Utility used for default
 *      cases in @key_handler.
 *      used to print non 
 *      'extreme-special' characters.
 *      
 *          @param key(int):
 *              Character represented
 *              int for NON-DOS MODE
 *              , and use of special 
 *              characters.(#define)
 */
void key_handler_util(int key)
{
    if(isalpha(key)==0)
    {
      if(print_scank == true)
      {
          inc_al();
          printk("%c", key);
      } 

      if(active_scank == true && print_scank == true)
          wait_until_enter(key);
    }
    else
    {
      if(kbd_info.is_caps == false && print_scank == true)
      {
        inc_al();
        printk("%c", key);
      }
      else if(kbd_info.is_caps == true && print_scank == true)
      {
        inc_al();
        printk("%c", toupper(key)); 
      }
    
      if(active_scank == true && print_scank == true)
        wait_until_enter(key);
    }
}

void key_handler_util_backspace()
{
  if(!((LENGTH_INPUT-1) < 0))
  {
    if(active_scank)
      buffer_scank[index_scank--] = 0;
    if(print_scank == true) printk("\b");   
      INDEX_CURSOR_POSITION-=1;
      LENGTH_INPUT-=1;
  }
}

/*
 * @function key_handler:
 *      Handles key events. 
 *      called by primary
 *      keyborad handler 
 *      @kbd_handler.
 *      
 */
void key_handler()
{
   switch(kbd_info.key)
   {
       //Is shift pressed
       case KBD_LEFT_SHIFT_PRESS_ID:
       case KBD_RIGHT_SHIFT_PRESS_ID:
            kbd_info.is_shift = true;
            break;
       case KBD_CAPS_PRESS_ID:
            break;
       case KBD_UP_KEY_ID:
            if(TERMINAL_MODE == true && UP_KEY_ACTIVE == true)
            {
               UP_KEY_ACTIVE = false;
               int LENGTH_INPUT_STORE = LENGTH_INPUT;
               for (int i=0; i<LENGTH_INPUT_STORE; i++)
                   key_handler_util_backspace();
               for(int i=0; cmd_active.value[i]; i++)
               {
                 if(active_scank == true && print_scank == true)
                 {
                    wait_until_enter(cmd_active.value[i]);
                    LENGTH_INPUT++;
                 }
               }
              printk("%s" , cmd_active.value);
            }
            break;   
        case KBD_ENTER_PRESS_ID:
            kbd_info.is_enter = true;
            active_scank = false;
            buffer_scank[index_scank] = 0;
            if(print_scank == true) printk("\n");
            UP_KEY_ACTIVE = true; //Reset Up Key
            break;
        case '\b':
           key_handler_util_backspace();
         break;
        case '\t':
            printk("\t");
            LENGTH_INPUT+=4;
            INDEX_CURSOR_POSITION+=4;
            break;
        case '\n':
            if(print_scank == true) printk("\n");
            break;
       default:
         if(isalpha(kbd_info.key)!=0)
             key_handler_util(kbd_info.key);
         else if(isdigit(kbd_info.key)!=0)
             key_handler_util(kbd_info.key);
         else if(((int)kbd_info.key) >= 32 && ((int)kbd_info.key) <=47)
             key_handler_util(kbd_info.key);
         else if(((int)kbd_info.key) >= 58 && ((int)kbd_info.key) <=64)
             key_handler_util(kbd_info.key);   
         else if(((int)kbd_info.key) >= 91 && ((int)kbd_info.key) <=96)
             key_handler_util(kbd_info.key);
         else if(((int)kbd_info.key) >= 123 && ((int)kbd_info.key) <=126)
             key_handler_util(kbd_info.key);    
         break;
   }
}


/*
 * @function kbd_handler:
 *      Primary Keyboard Handler
 *      called by the IRQ Handler.
 *      
 *      @param int_regs *r:
 *          Info about Registers
 *          during IRQ Request
 */
void kbd_handler(int_regs *r)
{
  if(r){};
  kbd_info.scancode =kbd_enc_read_input_buf();
  if(kbd_info.scancode & 0x80)
        key_release(kbd_info.scancode & ~0x80);
    else
    {
        kbd_info.key = key_press(kbd_info.scancode);
        __get_char_chr = kbd_info.key;
        __get_char_set = true;
        key_handler();
    }
}

/*
 * @function init_kbd:
 *      Initalize the Keyboard
 *      PS/2 Driver
 *            
 *      @return {STATUS}:
 *          returns STATUS_OK 
 *          if sucessfully exited.
 */
int init_kbd()
{
  kbd_driver.initalized = true;
  kbd_early_init();
  install_irq_handler(IRQ_NUM_KBD,kbd_handler);	
  return STATUS_OK;
}

/*
 * @function uninit_kbd:
 *      Uninitalize the Keyboard
 *      PS/2 Driver
 *            
 *      @return {STATUS}:
 *          returns STATUS_OK 
 *          if sucessfully exited.
 */
int uninit_kbd()
{
  kbd_driver.initalized = false;
  uninstall_irq_handler(IRQ_NUM_KBD);
  return STATUS_OK;
}



