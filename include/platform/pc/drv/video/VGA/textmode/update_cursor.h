#ifndef _DRV_VIDEO_VGA_TEXTMODE_UPDATE_CURSOR_H_
#define _DRV_VIDEO_VGA_TEXTMODE_UPDATE_CURSOR_H_

#include <stddef.h>
#include <stdint.h>

#define UPDATE_CURSOR_REGISTER_LOW 0x0F
#define UPDATE_CURSOR_REGISTER_HIGH 0x0E

#define UPDATE_CURSOR_POS_LOW(POS) \
        (POS & 0xFF)

#define UPDATE_CURSOR_POS_HIGH(POS) \
        ( (POS>>8) & 0xFF)

extern volatile uint8_t __crsr_start;
extern volatile uint8_t __crsr_end;

extern int update_cursor_textmode(int row, int col, uint8_t crc_start, uint8_t crc_end);

#endif /*_DRV_VIDEO_VGA_TEXTMODE_UPDATE_CURSOR_H_*/




