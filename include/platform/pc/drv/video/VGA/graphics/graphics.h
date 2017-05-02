#ifndef  _VGA_VIDEO_GRAPHICS
#define _VGA_VIDEO_GRAPHICS

#include <misc/rgb.h>
    
    #define RES_1_WIDTH 320
    #define RES_1_HEIGHT 200
    #define RES_1_COLORDEPTH 8

	extern void setMode(int width, int height, int colorDepth,uint8_t background);
	extern void vgaGrapicsPutPixel(int32_t x, int32_t y, uint8_t colorIndex);
	extern void clearVgaGraphics();

#endif