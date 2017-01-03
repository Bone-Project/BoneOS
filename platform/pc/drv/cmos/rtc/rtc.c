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
#include <drv/cmos/rtc/rtc.h>
#include <drv/cmos/cmos.h>
#include <apps/sh/values.h>
#include <io/io.h>
#include <stdint.h>
#include <stddef.h>
#include <stdlib/stdlib.h>

uint8_t rtc_get_second()
{
    outb(CMOS_REGISTER_SECONDS, CMOS_REGISTER_SECONDS);
    return inb(CMOS_REGiSTER_DATA);
}


uint8_t rtc_get_minute()
{
    outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_MINUTES);
    return inb (CMOS_REGiSTER_DATA);
}


uint8_t rtc_get_hour()
{
	outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_HOURS);
	return inb(CMOS_REGiSTER_DATA);
}

uint8_t rtc_get_weekday()
{
	outb(CMOS_REGISTER_SELECT,CMOS_REGISTER_WEEKDAY);
	return inb(CMOS_REGiSTER_DATA);
}


uint8_t rtc_get_day_month()
{
	outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_DAYMONTH);
	return inb(CMOS_REGiSTER_DATA);
}


uint8_t rtc_get_month()
{
	outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_MONTH);
	return inb(CMOS_REGiSTER_DATA);
}

static char* month_to_text(uint8_t num)
{
	char* month;
	if(num < 1 || num > 12)
		panik("NOT CORRECT MONTH");
	switch(num)
	{
		case 1:
			month = "Jan";
			break;	
	}
	
	return month;
}


uint8_t rtc_get_year()
{
	outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_YEAR);
	return inb(CMOS_REGiSTER_DATA);
}

uint8_t rtc_get_century()
{
	outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_CENTURY);
	return inb(CMOS_REGiSTER_DATA);
}




void rtc_print_time ()
{
    printk("Tue %s 3 %x:%x:%x UTC %x%x\n",  month_to_text(rtc_get_month()), rtc_get_hour(), rtc_get_minute(), rtc_get_second()  ,rtc_get_century(),rtc_get_year());
    //Tue Jan  3 03:24:37 UTC 2017
}
