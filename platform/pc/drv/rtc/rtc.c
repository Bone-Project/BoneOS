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
 **  @main_author : Ashish Ahuja
 **
 **  @contributors:

 **     Ashish Ahuja<Fortunate-MAN>: start
 **/

#include <cpu/interrupts/interrupts.h>
#include <misc/status_codes.h>
#include <cpu/interrupts/irq.h>
#include <libc/unistd/sleep/sleep.h>
#include <libc/stdlib/stdlib.h>
#include <stdio/stdio.h>
#include <drv/driver.h>
#include <drv/rtc/rtc.h>
#include <apps/sh/values.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>

uint8_t rtc_get_year()
{
	outb(CLOCK_CTL_ADDR, 0x09);
	return inb(CLOCK_DATA_ADDR);
}

uint8_t rtc_get_month()
{
	outb(CLOCK_CTL_ADDR, 0x08);
	return inb(CLOCK_DATA_ADDR);
}

uint8_t rtc_get_day()
{
	outb(CLOCK_CTL_ADDR, 0x07);
	return inb(CLOCK_DATA_ADDR);
}

uint8_t rtc_get_hour()
{
	outb(CLOCK_CTL_ADDR, 0x04);
	return inb(CLOCK_DATA_ADDR);
}

uint8_t rtc_get_minute ()
{
    outb(CLOCK_CTL_ADDR, 0x02);
    return inb (CLOCK_DATA_ADDR);
}

uint8_t rtc_get_second()
{
    outb(CLOCK_CTL_ADDR, 0x00);
    return inb(CLOCK_DATA_ADDR);
}

void rtc_print_time ()
{
    printk("20%x, %x. %x. %x:%x:%x\n",
			rtc_get_year(), rtc_get_month(), rtc_get_day(),
			rtc_get_hour(), rtc_get_minute(), rtc_get_second());
}
