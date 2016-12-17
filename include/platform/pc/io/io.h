#ifndef _IO_H_
#define _IO_H_ 1

#include <stddef.h>
#include <stdint.h>
  
/*
 * Input & Output Functions
 * to ports.
 *   .prefix = b : {BYTE} , (8 Bit Operation)
 *   .prefix = w : {WORD} ,  (16 Bit Operation)
 *   .prefix = d : {DOUBLE_WORD} , Byte (32 Bit Operation) //Not l since d means 64bit in x86_64 , reduce confusion
 */
extern uint8_t inb(uint16_t port_num);
extern void outb(uint16_t port_num,uint8_t data);
 
extern uint16_t inw(uint16_t port_num);
extern void outw(uint16_t port_num,uint16_t data);
 
extern uint32_t ind(uint16_t port_num);
extern void outd(uint16_t port_num,uint32_t data);

#endif /*_IO_H_*/


