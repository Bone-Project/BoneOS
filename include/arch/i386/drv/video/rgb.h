#ifndef  _ARCH_DRV_VIDEO_RGB_H_
#define _ARCH_DRV_VIDEO_RGB_H_

#include <stddef.h>
#include <stdint.h>

typedef union
{
  uint8_t color_index;
  uint32_t rgba;
  struct
  {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
  }rgb;
}rgb_t;

#endif /*_ARCH_DRV_VIDEO_RGB_H_*/