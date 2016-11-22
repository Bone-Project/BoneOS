#ifndef  _LIBC_STDIO_SCANK_H_
#define _LIBC_STDIO_SCANK_H_

#include <stdbool.h>
#include <stdint.h>

extern int scank(const char *fmt, ...);
extern void vscank(const char *fmt, va_list arg);

extern volatile uint32_t index_scank;
extern volatile bool active_scank;
extern volatile char buffer_scank[4096];

#endif /*_LIBC_STDIO_SCANK_H_*/