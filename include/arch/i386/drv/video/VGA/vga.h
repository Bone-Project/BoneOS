#ifndef  DRV_VIDEO_VGA_H_
#define DRV_VIDEO_VGA_H_

#include <drv/video/video.h>

#define VIDEO_MODE TEXTMODE

#if VIDEO_MODE == TEXTMODE
extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK  
#endif

extern int uninit_vga_driver();
extern int init_vga_driver();
extern struct video_driver vga_driver;

#endif /*VIDEO_DRIVER_MODE*/