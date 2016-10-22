#ifndef _LIBC_STDLIB_ITOA_H_
#define _LIBC_STDLIB_ITOA_H_

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

extern void __itoa(unsigned i,unsigned base,char* buf);
extern char *itoa(int val);

#endif /*_LIBC_STDLIB_ITOA_H_*/
