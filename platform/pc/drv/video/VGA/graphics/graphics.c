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
 
#include <io/io.h> 
#include <stdbool.h>
#include <stdio/stdio.h>
#include <drv/video/VGA/graphics/graphics.h>

void setMode(int width, int height, int colorDepth)
{
    bool support = supports_mode(width,height,colorDepth);
    if(support==false)
    {
    	printck(8,0,"NOT SUPPORTED RESOLUTION.");
    	return;
    }
}

void writeRegister(uint8_t * register_res)
{
	//  misc
	outb(0x3c2,*(register_++));


	 // sequencer
    for(uint8_t i = 0; i < 5; i++)
    {
        outb(0x3c4,i);
        outb(0x3c5,*(register_++));
    }

    // cathode ray tube controller
    outb(0x3d4,0x03);
    outb(0x3d5,crtcDataPort.in(0x3d5) | 0x80);
    outb(0x3d4,0x11);
    outb(0x3d5,crtcDataPort.in(0x3d5) & ~0x80);

    register_[0x03] = register_[0x03] | 0x80;
    register_[0x11] = register_[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++)
    {
        outb(0x3d4,i);
        outb(0x3d5,*(register_++));
    }

    // graphics controller
    for(uint8_t i = 0; i < 9; i++)
    {
        outb(0x3ce,i);
        outb(0x3cf,*(register_++));
    }

    // attribute controller
    for(uint8_t i = 0; i < 21; i++)
    {
        attributeControllerResetPort.in(0x3da);
        outb(0x3c0,i);
        attributeControllerWritePort.out(*(register_++),0x3c0);
    }

    attributeControllerResetPort.in(0x3da);
    attributeControllerIndexPort.out(0x20,0x3c0);

}


bool supports_mode(int width, int height, int colorDepth)
{
    return(width==RES_1_WIDTH && height==RES_1_HEIGHT, colorDepth==RES_1_COLORDEPTH);
}