#ifndef _SCREEN_PUTCH_H_
#define _SCREEN_PUTCH_H_

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

extern void putch(char c);
extern void cls();

extern size_t terminal_column;
extern size_t terminal_row;
extern uint8_t FG; // Foreground - White
extern uint8_t BG; // Background - BLACK  

#endif /*_SCREEN_PUTCH_H_*/