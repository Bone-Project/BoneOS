/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **  
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/  

#include <stdint.h> 

uint8_t inb(uint16_t port_num)
{
    uint8_t result;
    __asm__ __volatile__ (
        "inb %w[port_num],%b[result]\n\t"
        : [result] "=a" (result) // ASM -> Variable
        : [port_num] "Nd" (port_num) // VARIABLE -> ASM
    );
    
    return result;
}

uint16_t inw(uint16_t port_num)
{
    uint16_t result;
    __asm__ __volatile__
    (
        "inw %w[port_num], %w[result]\n\t"
        : [result] "=a" (result)
        : [port_num] "Nd" (port_num)
    ); 
    
    return result;
}


uint32_t ind(uint16_t port_num)
{
    uint32_t result;
    __asm__ __volatile__
    (
        "inl %w[port_num], %[result]\n\t"
        : [result] "=a" (result)
        : [port_num] "Nd" (port_num)
    ); 
    
    return result;
}



void outb(uint16_t port_num,uint8_t data)
{
    __asm__ __volatile__ 
    (
        "outb %b[data],%w[port_num]\n\t"
        :
        : [data] "a" (data),
         [port_num] "Nd" (port_num)
    );
}

void outw(uint16_t port_num,uint16_t data)
{
    __asm__ __volatile__ 
    (
        "outw %w[data],%w[port_num]\n\t"
        :
        : [data] "a" (data),
         [port_num] "Nd" (port_num)
    );
}

void outd(uint16_t port_num,uint32_t data)
{
    __asm__ __volatile__ 
    (
        "outl %[data],%w[port_num]\n\t"
        :
        : [data] "a" (data),
         [port_num] "Nd" (port_num)
    );
}

