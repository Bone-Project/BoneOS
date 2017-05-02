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
#include <drv/video/VGA/graphics/resolutions.h>

void writeRegister(uint8_t * register_res);

bool supports_mode(int width, int height, int colorDepth)
{
    return(width==RES_1_WIDTH && height==RES_1_HEIGHT && colorDepth==RES_1_COLORDEPTH);
}

uint8_t* getFrameBufferSeg()
{
    outb(0x3ce,0x06);
    uint8_t segmentNumber = inb(0x3cf) & (3<<2);
    switch(segmentNumber)
    {
        default:
        case 0<<2: return (uint8_t*)0x00000;
        case 1<<2: return (uint8_t*)0xA0000;
        case 2<<2: return (uint8_t*)0xB0000;
        case 3<<2: return (uint8_t*)0xB8000;
    }
}

void vgaGrapicsPutPixel(int32_t x, int32_t y, uint8_t colorIndex)
{
    if(x < 0 || RES_1_WIDTH <= x
    || y < 0 || RES_1_HEIGHT<= y)
        return;

    uint8_t* pixelAddress = getFrameBufferSeg() + RES_1_WIDTH*y + x;
    *pixelAddress = colorIndex;
}

void fillRectangle(uint32_t x, uint32_t y , uint32_t w, uint32_t h, uint8_t colorHex)
{
   for(uint32_t Y = y; Y < y+h; Y++)
        for(uint32_t X = x; X < x+w; X++)
            vgaGrapicsPutPixel(X, Y, colorHex);
}

void setMode(int width, int height, int colorDepth, uint8_t background)
{
    bool support = supports_mode(width,height,colorDepth);
    if(support==false)
    {
    	printck(8,0,"NOT SUPPORTED RESOLUTION.");
    	return;
    }
    
    if(width==RES_1_WIDTH && height==RES_1_HEIGHT && colorDepth==RES_1_COLORDEPTH)
        writeRegister(g_320x200x256);
        
    fillRectangle(0,0,RES_1_WIDTH,RES_1_HEIGHT,background);
}

void clearVgaGraphics()
{
    fillRectangle(0,0,RES_1_WIDTH,RES_1_HEIGHT,0x0);
}


void writeRegister(uint8_t * register_res)
{
	//  misc
	outb(0x3c2,*(register_res++));


	 // sequencer
    for(uint8_t i = 0; i < 5; i++)
    {
        outb(0x3c4,i);
        outb(0x3c5,*(register_res++));
    }

    // cathode ray tube controller
    outb(0x3d4,0x03);
    outb(0x3d5,inb(0x3d5) | 0x80);
    outb(0x3d4,0x11);
    outb(0x3d5,inb(0x3d5) & ~0x80);

    register_res[0x03] = register_res[0x03] | 0x80;
    register_res[0x11] = register_res[0x11] & ~0x80;

    for(uint8_t i = 0; i < 25; i++)
    {
        outb(0x3d4,i);
        outb(0x3d5,*(register_res++));
    }

    // graphics controller
    for(uint8_t i = 0; i < 9; i++)
    {
        outb(0x3ce,i);
        outb(0x3cf,*(register_res++));
    }

    // attribute controller
    for(uint8_t i = 0; i < 21; i++)
    {
        inb(0x3da);
        outb(0x3c0,i);
        outb(0x3c0,*(register_res++));
    }

    inb(0x3da);
    outb(0x3c0,0x20);

}


