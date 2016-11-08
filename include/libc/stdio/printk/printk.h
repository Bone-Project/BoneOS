#ifndef  _LIBC_STDIO_PRINTK_H_
#define _LIBC_STDIO_PRINTK_H_

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

extern void printk(const char* fmt, ...);
extern void vprintk(const char* fmt, va_list arg);

#endif /*_LIBC_STDIO_PRINTK_H_*/