#ifndef  _LIBC_STDIO_PRINTCK_H_
#define _LIBC_STDIO_PRINTCK_H_


extern void vprintck(uint8_t fg, uint8_t bg, const char* fmt,  va_list arg);
extern void printck(uint8_t fg, uint8_t bg, const char* fmt,  ...);

#endif /*_LIBC_STDIO_PRINTCK_H_*/


