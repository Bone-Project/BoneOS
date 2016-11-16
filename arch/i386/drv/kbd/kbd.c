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
#include <io/i386/io.h>
#include <libc/stdio/stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <drv/i386/kbd/kbd.h>
#include <stdbool.h>
#include <libc/assertk.h>

//Structure of Keyboard
//Information
struct 
{
    struct 
    {
        bool NUM_LOCK;
        bool CAPS_LOCK;
        bool SCROLL_LOCK;
    }LED;
    
    struct
    {
        bool SHIFT;
        bool ALT;
        bool CTRL;
    }SPEC_KEYS;
    
    struct
    {
        bool BAT_TEST;
    }TESTS;
    
    struct
    {
        struct
        {
            bool (*BAT_TEST)(void);
        }TESTS;
        
        struct
        {
            char (*KEY_PRESS)(uint8_t scancode);
            void (*KEY_RELEASE)(uint8_t scancode);
        }KEY_EV;
        
    }FUNCS;
    
    uint8_t KBD_ENC_IN_BUF;
    
}KBD_INFO;

const char QWERTY_EN[] = 
{
  0, 0,'1', '2','3','4','5','6','7','8','9','0',
  '-','+','\b','\t','q','w','e','r','t','y','u','i','o',
  'p','[',']','P'
};

/*
 *  Keyboard Ctrl :    
 * Read status register
 * and read command to ctrl
 */
uint8_t kbd_ctrl_read_status_reg()
{
  return (inb8(KBD_CTRL_STATS_REG));   
}

void kbd_ctrl_send_cmd(uint8_t cmd)
{
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb8(KBD_CTRL_CMD_REG,cmd);
}

/*
 *  Keyboard Encoder :    
 * Read encoder input buffer
 * and send command to encoder
 */
uint8_t kbd_enc_read_input_buf()
{
    return (inb8(KBD_ENC_INPUT_BUF_REG));    
}

void kbd_enc_send_cmd(uint8_t cmd)
{
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_IN_BUF) != 0);
    outb8(KBD_ENC_CMD_REG,cmd);
}

char key_press(uint8_t scancode)
{
    printk("%d " ,QWERTY_EN[scancode] );
    return (QWERTY_EN[scancode]);
}

void key_release(uint8_t scancode)
{
    //printk("RELEASE %d" , KBD_INFO.KBD_ENC_IN_BUF );
}

bool bat_test(void)
{
    kbd_ctrl_send_cmd(KBD_CTRL_CMD_SELF_TEST);
    
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_OUT_BUF) == 0);
    
    return (kbd_enc_read_input_buf () == 0x55) ? true : false;
}

void kbd_init_pointers()
{
    /*Initalize Function Pointers*/
    KBD_INFO.FUNCS.TESTS.BAT_TEST = &bat_test;
    KBD_INFO.TESTS.BAT_TEST = (*KBD_INFO.FUNCS.TESTS.BAT_TEST)();
    assertk(KBD_INFO.TESTS.BAT_TEST);
    KBD_INFO.FUNCS.KEY_EV.KEY_PRESS = &key_press;
    KBD_INFO.FUNCS.KEY_EV.KEY_RELEASE = &key_release;
    
}


void kbd_handler(int_regs *r)
{
  KBD_INFO.KBD_ENC_IN_BUF =kbd_enc_read_input_buf();
  if(KBD_INFO.KBD_ENC_IN_BUF & 0x80)
        (*KBD_INFO.FUNCS.KEY_EV.KEY_RELEASE)(KBD_INFO.KBD_ENC_IN_BUF);
    else
    {
        char key = (*KBD_INFO.FUNCS.KEY_EV.KEY_PRESS)(KBD_INFO.KBD_ENC_IN_BUF);
        printk("KEY : %c", key);
    }
}

void init_kbd()
{
  kbd_init_pointers();
  install_irq_handler(1,kbd_handler);	
}