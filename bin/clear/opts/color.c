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

#include <stddef.h>
#include <stdint.h>
#include <misc/status_codes.h>
#include <term/terminal.h>
#include <unistd/unistd.h>
#include <stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/video/video.h>
#include <string/string.h>



extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK 

int cmd_clear_color_handler(char* cmd)
{
   size_t num_opts = get_opt_count(cmd);
   str_t opts[num_opts];
   get_opt(cmd,opts);
   
   int _FG = strtoi((char*)opts[2].str, 0, 16);
   int _BG = strtoi((char*)opts[3].str, 0, 16);
   
   FG = _FG;
   BG = _BG;
   
   video_drivers[VGA_VIDEO_DRIVER_INDEX]->clear();
        
   return STATUS_OK;
}

struct cmd_opt_t cmd_clear_opt_color = 
{
    .help =  "clear(1) \t\t\t\t BoneOS Terminal Manual \n"
                "NAME : \n"
                "\tclear --color\n"
                "SYNOPSIS : \n "
                "\tclear  [--color <fg-color> <bg-color>] [--color <--help>] [--color <--def>] \n"
                "DESCRIPTION : \n"
                "\tClears the terminal with accordance to th\n"
                "\tcolor with the --color command and providing it\n"
                "\tspecified foreground and background colors.\n"
                "OPTIONS : \n"
                "\t Option Summary \n"
                "\t\t[--color <fg-color> <bg-color>] : Clears terminal according to colors\n"
                "\t\t0=Black,1=Blue,2=Green,3=Aqua,4=Red,5=Purple,6=Yellow,7=White\n"
                "\t\t8=Gray,9=LightBlue,A=LightGreen,B=LightAqua,C=LightRed,D=LightPurple\n"
                "\t\tE=LightYellow,F=BrightWhite\n"
                "\t\t--def : Clears to default (BG : 0x7 , FG : 0x0)\n", 
        .cmd_opt_name = "--color" ,
        .handler = &cmd_clear_color_handler,
        .invalid_use_msg = "Invalid Use of --color option. Use command clear --color --help for instructions\n"
                           "on how to use the clear command\n"
};