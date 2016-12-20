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

#include <misc/status_codes.h>
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
#include <libc/stdio/scank/scank.h>
#include <misc/status_codes.h>
#include <term/terminal.h>
#include <ctype/ctype.h>
#include <drv/video/video.h>
#include <drv/driver.h>
#include <drv/video/VGA/vga.h>
#include <drv/video/VGA/textmode/update_cursor.h>



volatile struct kbd_info_t kbd_info;
volatile int LENGTH_INPUT=0;
volatile int INDEX_CURSOR_POSITION=0;

extern volatile bool TERMINAL_MODE;


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
    {
        printk("***SHIFT***");
       return (kbd_layouts[kbd_info.current_kbd_layout]->scancode_shift[scancode]);
    }
    else
    {
        printk("NO SHIFT");
       return (kbd_layouts[kbd_info.current_kbd_layout]->scancode_no_shift[scancode]);
    }
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
  if (kbd_layouts[kbd_info.current_kbd_layout]->scancode_no_shift[scancode] == KBD_QWERTY_USA_LEFT_SHIFT_PRESS || 
    kbd_layouts[kbd_info.current_kbd_layout]->scancode_no_shift[scancode] == KBD_QWERTY_USA_RIGHT_SHIFT_PRESS)  
    {
        //printk("SHIFT RELEASE");
        kbd_info.is_shift = false;
    }
}

/*
 * @function kbd_init_pointers:
 *      Stuff to initalize
 *      before installing
 *      the PS/2 Keyboard
 */
void kbd_init_pointers()
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

    kbd_info.current_kbd_layout = QWERTY_USA_INDEX;
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
  kbd_info.kbd_enc_info =kbd_enc_read_input_buf();
  if(kbd_info.kbd_enc_info & 0x80)
        key_release(kbd_info.kbd_enc_info & ~0x80);
    else
    {
        printk("SCANCODE %c",key_press(kbd_info.kbd_enc_info));
        //kbd_info.key = (*kbd_info.routines.key_ev.key_press)(kbd_info.kbd_enc_info);
        //kbd_info.key = key_press(kbd_info.kbd_enc_info);
        
        //printk("CHARACTER = %cEND\n",kbd_info.key);
        //key_handler();
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
  kbd_init_pointers();
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


