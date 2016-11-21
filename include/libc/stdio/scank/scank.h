#ifndef  _LIBC_STDIO_SCANK_H_
#define _LIBC_STDIO_SCANK_H_

#include <stdbool.h>
#include <stdint.h>

extern int scank(const char *fmt, ...);

extern volatile uint32_t index_scank;
extern volatile bool active_scank;
extern volatile char buffer_scank[];

#endif /*_LIBC_STDIO_SCANK_H_*/