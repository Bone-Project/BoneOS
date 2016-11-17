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

char key;

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
    bool is_shift;
    bool is_caps;
    
}KBD_INFO;

const char QWERTY_EN_NOSHIFT[] = 
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',     /* Tab */
  'q', 'w', 'e', 'r', /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,      /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0x2F,    /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',      /* 49 */
  'm', ',', '.', '/',   0x2F,        /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

const char QWERTY_EN_SHIFT[] = 
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', /* 9 */
  '(', ')', '_', '+', '\b', /* Backspace */
  '\t',     /* Tab */
  'q', 'w', 'e', 'r', /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,      /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0x2F,    /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',      /* 49 */
  'm', ',', '.', '/',   0x2F,        /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
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
    if(KBD_INFO.is_shift == true)
       return (QWERTY_EN_SHIFT[scancode]);
    else  
      return (QWERTY_EN_NOSHIFT[scancode]);
}

void key_release(uint8_t scancode)
{
    //printk("RELEASE %d" , KBD_INFO.KBD_ENC_IN_BUF );
   if(KBD_INFO.KBD_ENC_IN_BUF == 182 ||  KBD_INFO.KBD_ENC_IN_BUF == 170)
          KBD_INFO.is_shift = false;
}

bool bat_test(void)
{
    kbd_ctrl_send_cmd(KBD_CTRL_CMD_SELF_TEST);
    
    while( (kbd_ctrl_read_status_reg() & KBD_CTRL_STATS_MASK_OUT_BUF) == 0);
    
    return (kbd_enc_read_input_buf () == 0x55) ? true : false;
}

bool led_light(bool scroll, bool num, bool caps)
{
  uint8_t data_final = 0x0;
  if(scroll) data_final |= KBD_SCROLL_LED_ON;
  if(num) data_final |= KBD_NUM_LED_ON;
  if(caps) data_final |= KBD_CAPS_LOCK_ON;

  kbd_enc_send_cmd(KBD_ENCODER_CMD_SET_LED);
  kbd_enc_send_cmd(data_final);
  return true;
}

void kbd_init_pointers()
{
    /*Initalize Function Pointers*/
    KBD_INFO.FUNCS.TESTS.BAT_TEST = &bat_test;
    KBD_INFO.TESTS.BAT_TEST = (*KBD_INFO.FUNCS.TESTS.BAT_TEST)();
    assertk(KBD_INFO.TESTS.BAT_TEST);
    KBD_INFO.FUNCS.KEY_EV.KEY_PRESS = &key_press;
    KBD_INFO.FUNCS.KEY_EV.KEY_RELEASE = &key_release;

    led_light(true,true,true);
    KBD_INFO.is_shift = false;
    KBD_INFO.is_caps = false;
}

void key_handler()
{
   switch(key)
   {
    case 0x2F:
      printk("SHIFT");
      KBD_INFO.is_shift = true;
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
  KBD_INFO.KBD_ENC_IN_BUF =kbd_enc_read_input_buf();
  if(KBD_INFO.KBD_ENC_IN_BUF & 0x80)
        (*KBD_INFO.FUNCS.KEY_EV.KEY_RELEASE)(KBD_INFO.KBD_ENC_IN_BUF);
    else
    {
        key = (*KBD_INFO.FUNCS.KEY_EV.KEY_PRESS)(KBD_INFO.KBD_ENC_IN_BUF);
        key_handler();
    }
}

void init_kbd()
{
  kbd_init_pointers();
  install_irq_handler(1,kbd_handler);	
}