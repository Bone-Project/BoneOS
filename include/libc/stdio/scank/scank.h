#ifndef  _LIBC_STDIO_SCANK_H_
#define _LIBC_STDIO_SCANK_H_

#include <stdbool.h>
#include <stdint.h>

extern int scank(bool backspace_count,bool print, const char *fmt, ...);
extern void vscank(bool backspace_count,bool print ,const char *fmt, va_list arg);

extern volatile uint32_t index_scank;
extern volatile bool active_scank;
extern volatile bool print_scank;
extern volatile char buffer_scank[4096];
extern volatile int __backspace_count;
extern volatile bool __backspace_count_active;
#endif /*_LIBC_STDIO_SCANK_H_*/


