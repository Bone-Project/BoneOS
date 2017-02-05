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
 **  @main_author : Ashish Ahuja
 **
 **  @contributors:

 **     Ashish Ahuja<Fortunate-MAN>: start
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <stdlib/stdlib.h>
#include <string/string.h>
#include <stdint.h>
#include <ctype/ctype.h>
#include <sh/values.h>
#include <watch/watch.h>
#include <strcmp/strcmp.h>
#include <apps/sh/utils.h>
#include <libc/assertk.h>
#include <drv/pit/pit.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/driver.h>

int main_watch_opt_handler (char *cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd,opts);
    unsigned interval = 2 * 1000;
    char command [125];
    command [0] = '\0';
    int actual_command_index = 0;
    bool no_title = false;

    if (num_opts == 1)
    {
        printk (cmd_watch.invalid_use_msg);
        return STATUS_FAIL;
    }
    else if (num_opts > 1)
    {
        if (strcmp (opts [1].str, "--help") == 0)
        {
            printk (cmd_watch.help);
            return STATUS_OK;
        }
        else
        {
            for (unsigned i = 1; i < num_opts; i ++)
            {
                if (!strcmp (opts [i].str, "-n"))
                {
                    if (i == (num_opts - 1))
                    {
                        printk (cmd_watch.invalid_use_msg);
                        return STATUS_FAIL;
                    }
                    else
                    {
                        if (isalpha (opts [i + 1].str [0]))
                        {
                            printk (cmd_watch.invalid_use_msg);
                            return STATUS_FAIL;
                        }
                        interval = atoi (opts [i + 1].str);
                        interval *= 1000;
                        i ++;
                    }
                }
                else if (!strcmp (opts [i].str, "-t"))
                {
                    if (no_title == true)
                    {
                        printk (cmd_watch.invalid_use_msg);
                        return STATUS_FAIL;
                    }
                    no_title = true;
                }
                else
                {
                    if (strlen (command) == 0)
                    {
                        strcpy (command, opts [i].str);
                    }
                    else
                    {
                        command [strlen (command)] = ' ';
                        strcpy (command + (strlen (command)), opts [i].str);
                    }
                    if (!actual_command_index)
                    {
                        actual_command_index = i;
                    }
                }
            }

            for(int i=0; cmds[i]; i++)
            {
                if(termcmp(cmds[i]->name, opts [actual_command_index].str)==0)
                {
                    again:

                    cmds[CMD_CLEAR_INDEX]->handler ("clear");

                    if (no_title == false)
                    {
                        printk ("Every %ds: %s \n\n", interval / 1000, command);
                    }

                    cmds[i]->handler(command);
                    assertkm(device_initalized(PIT_DRIVER_INDEX) , "PIT NOT INITALIZED FOR SLEEP()");
                    int64_t expiry = pit_ticks + ((uint64_t)interval * IRQ_SEC_HIT) / 1000;

                    while (pit_ticks < expiry)
                    {
                        kbd_info.scancode = kbd_enc_read_input_buf();
                        if(kbd_info.scancode & 0x80);
                        else
                        {
                            kbd_info.key = key_press(kbd_info.scancode);
                            if (kbd_info.key == 'q')
                            {
                                cmds[CMD_CLEAR_INDEX]->handler ("clear");
                                return STATUS_OK;
                            }
                        }
                    }

                    goto again;
                }
            }

            printk (cmd_watch.invalid_use_msg);
            return STATUS_FAIL;
        }
    }

    return STATUS_FAIL;
}


