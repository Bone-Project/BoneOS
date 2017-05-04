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
 
#include <gui/vga/widget.h>
#include <drv/video/video.h>
#include <string/string.h>
 
void fillrect(uint32_t x, uint32_t y , uint32_t w, uint32_t h, uint8_t colorHex)
{
  if(strcmp(video_driver_mode, "GRAPHICS")!=0)
         return;
   for(uint32_t Y = y; Y < y+h; Y++)
     for(uint32_t X = x; X < x+w; X++)
        video_drivers[VGA_VIDEO_DRIVER_INDEX]->put_pixel(X, Y, colorHex);
}

widget_vga_t* createWidget(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint8_t color)
{
  widget_vga_t* widget = 0;
  
  widget->x  = x;
  widget->y  = y;
  widget->w  = w;
  widget->h  = h;
  widget->color = color;
  
  fillrect(x,y,w,h,color);
 
 
  return widget;
}