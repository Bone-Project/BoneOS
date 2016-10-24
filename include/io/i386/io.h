#ifndef _IO_H_
#define _IO_H_ 1

#include <stddef.h>
#include <stdarg.h>
#include <stdint.h>

  // global inb8
  // global outb8
  // global inb16
  // global outb16
  // global inb32
  // global outb32
  
 extern uint8_t inb8(uint16_t port_num);
 extern void outb8(uint16_t port_num,uint8_t data);
 extern uint16_t inb16(uint16_t port_num);
 extern void outb16(uint16_t port_num,uint16_t data);
 extern uint32_t inb32(uint16_t port_num);
 extern void outb32(uint16_t port_num,uint32_t data);

#endif /*IO_H_*/