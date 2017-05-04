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

void toolbar(uint8_t color);
 
void fillrect(uint32_t x, uint32_t y , uint32_t w, uint32_t h, uint8_t colorHex)
{
   for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            video_drivers[VGA_VIDEO_DRIVER_INDEX]->put_pixel(X, Y, colorHex);
}
 
 void init_desktop(uint8_t background, uint8_t toolbar_color)
 {
    if(strcmp(video_driver_mode, "GRAPHICS")!=0)
         return;
    fillrect(0,0,320,200,background);
    toolbar(toolbar_color);
 }
 
 void toolbar(/*ENUM TOOLBAR TYPE(TOP,BOT)*/uint8_t color)
 {
     fillrect(0,190,320,10,color);
 }