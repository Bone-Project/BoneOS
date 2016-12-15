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

#include <misc/status_codes.h>
#include <drv/video/VGA/textmode/update_cursor.h>
#include <drv/video/VGA/textmode/cursor.h>
#include <io/io.h>
#include <stddef.h>
#include <stdint.h>

volatile uint8_t __crsr_start = 15;
volatile uint8_t __crsr_end = 15;

int update_cursor_textmode(int row, int col, uint8_t crsr_start, uint8_t crsr_end)
{
    uint16_t position = (row*80)+col;
    
    outb(CURSOR_REGISTER_SELECT,UPDATE_CURSOR_REGISTER_LOW);
    outb(CURSOR_DATA_SEND, UPDATE_CURSOR_POS_LOW(position));
    
    outb(CURSOR_REGISTER_SELECT,UPDATE_CURSOR_REGISTER_HIGH);
    outb(CURSOR_DATA_SEND,UPDATE_CURSOR_POS_HIGH(position));
    
    outw(CRTC_PORT, (crsr_start << 8) | 0x0A);
    outw(CRTC_PORT, (crsr_end << 8)   | 0x0B);
    
    __crsr_start = crsr_start;
    __crsr_end   = crsr_end;
    
    return STATUS_OK;
}

