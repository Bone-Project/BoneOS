#ifndef  ARCH_DRV_VIDEO_H_
#define ARCH_DRV_VIDEO_H_

#include <drv/video/rgb.h>
#include <stddef.h>
#include <stdint.h>

typedef void(*putch_t)(char c);
typedef void(*put_pixel_t)(int32_t x, int32_t y,  rgb_t rgb);

#define VIDEO_DRIVER_ACTIVE VGA
#define VIDEO_DRIVER_RES_W_ACTIVE 80
#define VIDEO_DRIVER_RES_H_ACTIVE 25
#define VGA_VIDEO_DRIVER_INDEX 0

#if VIDEO_DRIVER_ACTIVE == VGA
  #include <drv/video/VGA/vga.h>
#endif


/*
 * @struct video_driver:
 *      Prototype for a video
 *      driver. used as a basis
 *      for what video driver the
 *      current running OS Is 
 *      running
 */

struct video_driver
{
  enum
  {
    GRAPHICS_MODE, 
    TEXT_MODE 
  }mode;

  int(*init)(void);
  int(*uninit)(void);
  void(*putch)(char c);
  void(*put_pixel)(int32_t x, int32_t y,  rgb_t rgb);

  struct
  {
    int w;
    int h;
  }res;
  uint16_t status;
  const char* name;
};

extern struct video_driver *video_drivers[];

#endif /*ARCH_DRV_VIDEO_H_*/