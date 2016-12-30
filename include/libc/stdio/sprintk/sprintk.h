#ifndef _LIBC_STDIO_SPRINTK_H_
#define _LIBC_STDIO_SPRINTK_H_ 

extern void vsprintk(const char* fmt, char* buffer, va_list arg);
extern void sprintk(char *buffer, const char *fmt, ...);

#endif /*_LIBC_STDIO_SPRINTK_H_*/




