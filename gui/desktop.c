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
 #include <drv/video/video.h>
 #include <string/string.h>
 #include <stdlib.h>

 
 void init_desktop(uint8_t background)
 {
    if(strcmp(video_driver_mode, "GRAPHICS")!=0)
         return;
         
    
    for(uint32_t Y = 0; Y < 0+200; Y++)
        for(uint32_t X = 0; X < 0+320; X++)
            video_drivers[VGA_VIDEO_DRIVER_INDEX]->put_pixel(X,Y,background);
 }