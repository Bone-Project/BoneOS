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

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <libc/stdio/stdio.h>
#include <drv/pit/pit.h>
#include <libc/unistd/sleep/sleep.h>
#include <drv/driver.h>
#include <cpu/interrupts/interrupts.h>
#include <cpu/interrupts/irq.h>
#include <libc/assertk.h>
#include <misc/asm_util.h>

div_t div_64_32(int64_t numerator, int32_t denominator)
{
    div_t result;
    result.quot = (int32_t)numerator;
    result.rem = (int32_t)(numerator >> 32);
    __asm__ (
        "divl %[den]\n\t"
        : "+a" (result.quot), "+d" (result.rem)
        : [den] "rm" (denominator)
    );
    return result;
}


void sleep(uint32_t ms)
{
  int64_t expiry = pit_ticks + (ms * IRQ_SEC_HIT) / 1000;
  while (pit_ticks < expiry) hlt();
}

