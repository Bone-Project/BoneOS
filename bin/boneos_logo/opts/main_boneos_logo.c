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

#include <misc/status_codes.h>
#include <string/string.h>
#include <unistd/unistd.h>
#include <stdio/stdio.h>
#include <clear/clear.h>
#include <sh/shell.h>
#include <stdlib/stdlib.h>
#include <drv/video/video.h>
#include <boneos_logo/opts/boneos_logo_color.h>
#include <boneos_logo/boneos_logo.h>

int main_boneos_opt_handler(char *cmd)
{
  size_t num_opts = get_opt_count(cmd);
  str_t opts[num_opts];
  get_opt(cmd,opts);

   if(strcmp(opts[1].str, "-color")==0)
   {
     if(strcmp(opts[2].str, "--help")==0)
     {
        printk(cmd_boneos_logo_opt_color.help);
     }
     else if(strcmp(opts[2].str, "--def")==0)
     {
        video_drivers[VGA_VIDEO_DRIVER_INDEX]->fg = 0x7;
        video_drivers[VGA_VIDEO_DRIVER_INDEX]->bg = 0x0;
        printk   (
                "      myooooohhyso++//////////++osyhhoooooym\n"
                "    myoooooooo//////////////////////ooooooooy\n"
                "  myooooooooo////////////////////////oooooooooym\n"
                " yoooooooooo+////////////////////////+ooooooooooy\n"
                "soooooooooo+//////////////////////////+oooooooooos\n"
                "hooooooooo+////////////////////////////+oooooooooh\n"
                " doooooooo////####//////////////####////ooooooood\n"
                "  dsooooo////######////////////######////ooooosd\n"
                "   msooo+/////####////:----:////####/////+ooosm\n"
                "     ysd////////////:-......-:////////////dsy\n"
                "        +//////////:..........://////////+\n"
                "        y/////////-..-:####:-..-/////////y\n"
                "         /(....)/:-...########...-://(...)\n"
                "        /      /:.....########.....:/     /   \n"
                "       |       /......-####-....../       |  \n"
                "      |        |..................|        |\n"
                "     |         //..................//       | \n"
                "      |                                    | \n"
                "       |      .######++++++++#######.      |\n"
                "       (______)                     (______)\n");
     }
     else if(opts[2].str[0] == '\0' || opts[3].str[0] == '\0')
     {
       printk(cmd_boneos_logo_opt_color.invalid_use_msg);
       return STATUS_FAIL;
     }
     else
     {
        cmd_boneos_logo_opt_color.handler(cmd);
     }
   }
   else if(strcmp(opts[1].str, "--help")==0)
   {
       printk(cmd_boneos_logo.help);
   }
   else
   {
     printk(cmd_boneos_logo.invalid_use_msg);
     return STATUS_FAIL;
   }
  return STATUS_OK;
}






