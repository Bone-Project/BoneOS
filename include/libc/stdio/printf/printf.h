#ifndef _LIBC_STDIO_PRINTF_H_
#define _LIBC_STDIO_PRINTF_H_

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

extern void vprintf(const char* fmt, va_list arg);
extern void printf(const char* fmt, ...);

#endif /*_LIBC_STDIO_PRINTF_H_*/
