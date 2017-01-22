
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
 **     Ashish Ahuja <Fortunate-MAN>
 **/

#include <io/io.h>
#include <misc/status_codes.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <libc/stdio/stdio.h>
#include <libc/stdlib/panik/panik.h>
#include <boneshell/boneshell.h>
#include <string/string.h>
#include <stdint.h>
#include <stddef.h>
#include <drv/ps2/kbd/kbd.h>
#include <stdbool.h>
#include <libc/assertk.h>
#include <libc/ctype/ctype.h>
#include <drv/ps2/kbd/scancodes.h>
#include <libc/stdio/scank/scank.h>
#include <misc/status_codes.h>
#include <ctype/ctype.h>
#include <drv/video/video.h>
#include <drv/driver.h>
#include <drv/video/VGA/vga.h>
#include <sh/shell.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/vga.h>
#include <drv/video/video.h>
#include <drv/video/VGA/textmode/utils.h>



volatile struct kbd_info_t kbd_info;
volatile int INDEX_CURSOR_POSITION=0;
volatile bool UP_KEY_ACTIVE=true;

volatile bool TAB_PREVIOUS_VALUE_SET = false;
volatile char* TAB_PREVIOUS_VALUE = 0;

char tab__ [1024];


//Is this getting emulated at a terminal
extern volatile bool TERMINAL_MODE;

//getchar();
extern volatile bool __get_char_set;
extern volatile char __get_char_chr;

//Keyboard Driver Handler
struct device_driver_t kbd_driver =
{
    .name = "8042 Keyboard PS/2 Driver",
    .init = &init_kbd,
    .uninit = &uninit_kbd,
    .version = "8042"
};


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
       ) {
            kbd_info.is_shift = false;
        }

    if ((int)(scancode) == 29) //Scancode of "Control" key
        kbd_info.is_ctrl = false;
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
    if (index_scank == (unsigned)virtual_index_scank)
    {
        buffer_scank[index_scank++] = key;
        buffer_scank[index_scank] = 0;
        virtual_index_scank ++;
    }
    else if ((unsigned)virtual_index_scank < index_scank)
    {
        if (virtual_cursor_pos > 1)
        {
            for (int i = 0; i < virtual_cursor_pos; i ++)
            {
                buffer_scank [index_scank - i] = buffer_scank [index_scank - (i + 1)];
            }
            buffer_scank [index_scank - virtual_cursor_pos] = key;
            buffer_scank [++index_scank] = 0;
        }
        else
        {
            buffer_scank [index_scank] = buffer_scank [index_scank - virtual_cursor_pos];
            buffer_scank [index_scank - virtual_cursor_pos] = key;
            buffer_scank [++index_scank] = 0;
        }
        virtual_index_scank ++;

        for (int i = 0; buffer_scank [i]; i ++)
        {
            printk ("\b");
        }
        printk ("%s", buffer_scank);

        video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
        (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column - virtual_cursor_pos
        ,__crsr_start,__crsr_end);
    }
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
    //First checking for shortcut commands
    if (kbd_info.is_ctrl == true)
    {
        if (key == 'l' || key == 'L')
        {
            cmds [CMD_CLEAR_INDEX]->handler ("clear");
            printk (" ");
            kbd_info.key = KBD_ENTER_PRESS_ID;
            key_handler();
            kbd_info.key = ' ';
            cmds [CMD_CLEAR_INDEX]->handler ("clear");
            return;
        }
        else if (key == 'h' || key == 'H')
        {
            key_handler_util_backspace();
            return;
        }
        else if (key == 'd' || key == 'D')
        {
            cmds [CMD_EXIT_INDEX]->handler ("exit");
            kbd_info.key = KBD_ENTER_PRESS_ID;
            key_handler();
            kbd_info.key = ' ';
            return;
        }
        else if (key == 'n' || key == 'N')
        {
            new_set__shell = true;
            kbd_info.key = KBD_ENTER_PRESS_ID;
            key_handler();
            kbd_info.key = ' ';
            return;
        }
        else if (key == 'a' || key == 'A')
        {
            virtual_index_scank = 0;
            virtual_cursor_pos = LENGTH_INPUT;
            video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
            (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column - virtual_cursor_pos
            ,__crsr_start,__crsr_end);
            return;
        }
        else if (key == 'c' || key == 'C')
        {
            return;
        }
    }

    if(isalpha(key)==0)
    {
        if(print_scank == true && active_scank == true)
        {
            inc_al();
            printk("%c", key);
            wait_until_enter(key);
        }

        else if(active_scank == true)
            wait_until_enter(key);
    }
    else
    {
        if(kbd_info.is_caps == false && print_scank == true && active_scank == true)
        {
            inc_al();
            if (kbd_info.is_shift == true) {
                printk("%c", toupper(key));
            }
            else if (kbd_info.is_shift == false) {
                printk ("%c", tolower (key));
            }
            wait_until_enter(key);
        }
        else if(kbd_info.is_caps == true && print_scank == true && active_scank == true)
        {
            inc_al();
            if(kbd_info.is_shift == true)
            {
                key = tolower (key);
            }
            else
            {
                key = toupper (key);
            }
            printk ("%c", key);
            wait_until_enter(key);
        }
        else if(active_scank == true)
            wait_until_enter(key);
    }
}

void key_handler_util_backspace()
{
    if(!((LENGTH_INPUT-1) < 0) && virtual_index_scank > 0)
    {
        if(active_scank == true)
        {
            if (index_scank > (unsigned)virtual_index_scank)
            {
                for (int i = virtual_index_scank; i < (int)index_scank; i ++)
                {
                    buffer_scank [i - 1] = buffer_scank [i];
                }
                buffer_scank [index_scank - 1] = 0;
            }
            else
            {
                buffer_scank [index_scank-1] = 0;
            }
            index_scank --;
            virtual_index_scank --;
        }

        if(print_scank == true)
        {
            if (virtual_index_scank < 0)
            {
                return;
            }
            else if ((unsigned)virtual_index_scank + 1 < index_scank)
            {
                int temp = LENGTH_INPUT;
                while (temp > 0) {printk ("\b"); temp --;}
                printk ("%s", buffer_scank);
                video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
                (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column - virtual_cursor_pos
                ,__crsr_start,__crsr_end);
            }
            else
            {
                printk ("\b");
            }
        }

        INDEX_CURSOR_POSITION-=1;
        LENGTH_INPUT-=1;
    }
}


bool tab_util(volatile char* buf_scan, volatile char* _cmd)
{
    for(int i=0; buf_scan[i]; i++)
        if(buf_scan[i] != _cmd[i])
            return false;

    return true;
}

void key_handler_util_tab()
{
    int index_tab=0;
    int num_cmds=0;
    for(int i=0; cmds[i]; i++)
    {
        if(tab_util(buffer_scank, cmds[i]->name) == true)
        {
            num_cmds++;
            for(int j=0; cmds[i]->name[j]; j++)
            {
                tab__[index_tab] = cmds[i]->name[j];
                index_tab++;
            }
            for(int rep=0; rep<4; rep++)tab__[index_tab++] = ' ';
        }
    }
    tab__[index_tab] = 0;
    if(num_cmds==1)
    {
        printk ("\n");
        for(int i = 0; tab__[i]; i ++) {
            printk("%c", tab__[i]);
            cmd_active.value [i] = tab__ [i];
        }
        tab_one_opt=true;
        return;
    }

    if (num_cmds > 1) {
        tab_multiple_opts=true;
        printk ("\n");
        for(int i=0; tab__[i]; i++)
            printk("%c", tab__[i]);
    }
    else {
        tab_zero_opt = true;
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
                kbd_info.is_caps = !kbd_info.is_caps;
                break;
        case KBD_LEFT_KEY_ID:
                if ((LENGTH_INPUT - virtual_cursor_pos) > 0)
                {
                    virtual_cursor_pos ++;
                    video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
                    (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column - virtual_cursor_pos
                    ,__crsr_start,__crsr_end);
                    virtual_index_scank --;
                }
                break;
        case KBD_RIGHT_KEY_ID:
                if ((LENGTH_INPUT - virtual_cursor_pos) >= 0 && virtual_cursor_pos > 0)
                {
                    virtual_cursor_pos --;
                    video_drivers[VGA_VIDEO_DRIVER_INDEX]->update_cursor
                    (video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_row,video_drivers[VGA_VIDEO_DRIVER_INDEX]->video_column - virtual_cursor_pos
                    ,__crsr_start,__crsr_end);
                    virtual_index_scank ++;
                }
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
        case KBD_CONTROL_PRESS_ID:
            kbd_info.is_ctrl = true;
            break;
        case KBD_ENTER_PRESS_ID:
                kbd_info.is_enter = true;
                active_scank = false;
                buffer_scank[index_scank] = 0;

                if(print_scank == true)
                    printk("\n");

                UP_KEY_ACTIVE = true; //Reset Up Key
                break;
        case '\b':
                key_handler_util_backspace();
                break;
        case '\t':
                if(TERMINAL_MODE==false)
                {
                    printk("\t");
                    LENGTH_INPUT+=4;
                    INDEX_CURSOR_POSITION+=4;
                }
                else
                {
                    key_handler_util_tab();
                    active_scank = false;
                    buffer_scank[index_scank] = 0;

                    if(print_scank == true && tab_zero_opt == false)
                        printk("\n");

                    UP_KEY_ACTIVE = true; //Reset Up Key
                    TAB_PREVIOUS_VALUE_SET = true;
                    TAB_PREVIOUS_VALUE = buffer_scank;
                }
                break;
        case '\n':
                if(print_scank == true)
                    printk("\n");

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
    kbd_info.scancode = kbd_enc_read_input_buf();

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
