#ifndef _IO_H_
#define _IO_H_ 1

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>
  
 extern uint8_t inb(uint16_t port_num);
 extern void outb(uint16_t port_num,uint8_t data);
 
 extern uint16_t inw(uint16_t port_num);
 extern void outw(uint16_t port_num,uint16_t data);
 
 extern uint32_t ind(uint16_t port_num);
 extern void outd(uint16_t port_num,uint32_t data);

#endif /*_IO_H_*/

