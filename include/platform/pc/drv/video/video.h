#ifndef  ARCH_DRV_VIDEO_H_
#define ARCH_DRV_VIDEO_H_

#include <drv/video/VGA/vga.h>
#include <misc/rgb.h>
#include <stddef.h>
#include <stdint.h>

extern size_t video_driver_width;
extern size_t video_driver_height; 
extern char*  video_driver_name;
extern char*  video_driver_mode;

#define VIDEO_DRIVER_ACTIVE VGA
#define VIDEO_DRIVER_RES_W_ACTIVE 80
#define VIDEO_DRIVER_RES_H_ACTIVE 25
#define VGA_VIDEO_DRIVER_INDEX 0




typedef void(*clear_t)(void);
typedef void(*putch_t)(char c);
typedef void(*scroll_t)(int offset);
typedef int(*update_cursor_t)(int row,int col, uint8_t crsr_start,
                              uint8_t crsr_end);
typedef void(*put_pixel_t)(int32_t x, int32_t y,  rgb_t rgb);


/*
 * @struct video_driver:
 *      Prototype for a video
 *      driver. used as a basis
 *      for what video driver the
 *      current running OS Is 
 *      running
 */

struct video_driver_t
{
  enum
  {
    GRAPHICS_MODE, 
    TEXT_MODE 
  }mode;

  uint8_t fg;
  uint8_t bg;

  int(*init)(void);
  int(*uninit)(void);
  update_cursor_t update_cursor;
  clear_t clear;
  putch_t putch;
  put_pixel_t put_pixel;
  scroll_t scroll;

  struct
  {
    int w;
    int h;
  }res;
  uint16_t status;
  const char* name;
};

extern struct video_driver_t *video_drivers[];

#endif /*ARCH_DRV_VIDEO_H_*/


