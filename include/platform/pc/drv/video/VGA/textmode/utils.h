#ifndef  _DRV_VIDEO_VGA_TEXTMODE_80x25_UTILS_H_
#define  _DRV_VIDEO_VGA_TEXTMODE_80x25_UTILS_H_

#include <stddef.h>
#include <stdint.h>

extern uint8_t make_color(uint8_t fg, uint8_t bg);
extern uint16_t make_vgaentry(char c, uint8_t color);

#endif /*_DRV_VIDEO_VGA_TEXTMODE_80x25_UTILS_H_*/






