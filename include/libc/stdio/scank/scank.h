#ifndef  _LIBC_STDIO_SCANK_H_
#define _LIBC_STDIO_SCANK_H_

#include <stdbool.h>
#include <stdint.h>

extern int scank(bool print, const char *fmt, ...);
extern void vscank(bool print ,const char *fmt, va_list arg);

extern volatile uint32_t index_scank;
extern volatile bool active_scank;
extern volatile bool print_scank;
extern volatile char buffer_scank[4096];

#endif /*_LIBC_STDIO_SCANK_H_*/