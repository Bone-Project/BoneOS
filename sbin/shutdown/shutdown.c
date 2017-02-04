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

 **     Ashish Ahujs <Fortunate-MAN> : start
 **/

#include <misc/status_codes.h>
#include <sh/shell.h>
#include <drv/video/video.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <stdlib/stdlib.h>
#include <string/string.h>
#include <ctype/ctype.h>
#include <io/io.h>
#include <misc/asm_util.h>
#include <sys/sys_poweroff.h>
#include <sys/sys_reboot.h>
#include <shutdown/sbin_cmd_shutdown.h>
#include <reboot/sbin_cmd_reboot.h>
#include <libc/assertk.h>
#include <drv/driver.h>
#include <drv/ps2/kbd/kbd.h>
#include <drv/pit/pit.h>

struct cmd_opt_t* cmd_shutdown_opts[] =
{
    0
};

int cmd_shutdown_handler(char* cmd)
{
    size_t num_opts = get_opt_count(cmd);
    str_t opts[num_opts];
    get_opt(cmd, opts);
    int time = 0;

    if(num_opts == 1)
    {
        printk (cmd_shutdown.invalid_use_msg);
        return STATUS_OK;
    }
    else if(strcmp(opts[1].str, "--help") == 0)
    {
        printk (cmd_shutdown.help);
        return STATUS_OK;
    }
    else if (strcmp(opts[1].str, "-r") == 0)
    {
        if (num_opts == 2)
        {
            printk (cmd_shutdown.invalid_use_msg);
            return STATUS_OK;
        }

        if (!strcmp (opts [2].str, "now"))
        {
            time = 0;
        }
        else
        {
            //First checking if the string contains an alphabet
            for (int i = 0; i < (int)strlen (opts [2].str); i ++)
            {
                if (isalpha (opts [2].str [i]))
                {
                    printk (cmd_shutdown.invalid_use_msg);
                    return STATUS_OK;
                }
            }

            time = atoi (opts [2].str);
        }

        if (time)
        {
            printk ("This system is going to reboot in %d seconds! Press 'q' to cancel.\n\n", time);

            int to_sleep = time * 1000;

            assertkm(device_initalized(PIT_DRIVER_INDEX) , "PIT NOT INITALIZED FOR SLEEP()");
            int64_t expiry = pit_ticks + ((uint64_t)to_sleep * IRQ_SEC_HIT) / 1000;

            while (pit_ticks < expiry)
            {
                kbd_info.scancode = kbd_enc_read_input_buf();

                if (!(kbd_info.scancode & 0x80))
                {
                    kbd_info.key = key_press(kbd_info.scancode);

                    if (kbd_info.key == 'q')
                    {
                        printk ("Shutdown has been aborted!\n");
                        return STATUS_OK;
                    }
                }
            }

            cmds [CMD_REBOOT_INDEX]->handler ("reboot");
        }
        else if (time == 0)
        {
            cmds [CMD_REBOOT_INDEX]->handler ("reboot");
        }
    }
    else
    {
        printk(cmd_shutdown.invalid_use_msg);
    }

    return STATUS_OK;
}

struct cmd_t cmd_shutdown =
{
    .name = "shutdown",
    .usage ="shutdown [--help]",
    .help = "shutdown(1) \t\t\t\t BoneOS Terminal Manual \n"
            "NAME : \n "
            "\tshutdown\n"
            "SYNOPSIS : \n "
            "\tshutdown [--help]\n"
            "DESCRIPTION : \n "
            "\tShuts down the Operating System. Currently only working in Bochs and Qemu.\n",
    .cmd_opts = cmd_shutdown_opts,
    .handler = &cmd_shutdown_handler,
    .invalid_use_msg = "Invalid use of shutdown command.\n"
            "Type in shutdown --help for more help.\n",
    .privilege = ROOT
};

