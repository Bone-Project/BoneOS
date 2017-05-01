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
 
 
#include <stdbool.h>
// #include <graphics.h>

void setMode(int width, int height, int colorDepth)
{
    bool support = supports_mode(width,height,colorDepth);
}

bool supports_mode(int width, int height, int colorDepth)
{
    return(width==RES_1_WIDTH && height==RES_1_HEIGHT, colorDepth==RES_1_COLORDEPTH);
}