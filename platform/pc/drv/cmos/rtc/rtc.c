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
    outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_SECONDS);
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

static const char* month_to_text(uint8_t num)
{
	const char* month;
	if(num < 1 || num > 12)
		panik("INVALID MONTH");
		
	const char* months_str[12] = 
	{ 
		"Jan", "Feb" , "Mar", "Apr" , "May",
		"Jun", "Jul", "Aug" , "Sep", "Oct",
		"Nov", "Dec"
	};
	
	month = months_str[num-1];
	return month;
}

static const char* date_to_text(uint8_t num)
{
	const char* date;
	if(num < 1 || num > 7)
		panik("INVALID MONTH");
		
	const char* dates_str[7] = 
	{ 
		"Mon", "Tue" , "Wen", "Thu" , "Fri",
		"Sat", "Sun"
	};
	
	date = dates_str[num-2];
	return date;
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

// static void add_0(uint8_t test)
// {
// 	char* test_str=0;
// 	for(int i=0; test_str[i]; i++)
// 		test_str[i]=0;
// 	sprintk(test_str,"%c", test);
// 	printk(test_str);
// }


void rtc_print_date_cmd ()
{
    printk("%s %s %x %x:%x:%x UTC %x%x\n", 
    								  date_to_text(rtc_get_day_month()),
    								  month_to_text(rtc_get_month()),
    								  rtc_get_day_month(),
    								  rtc_get_hour(),
    								  rtc_get_minute(),
    								  rtc_get_second() ,
    								  rtc_get_century(),
    								  rtc_get_year());
    //Tue Jan  3 16:06:48 UTC 2017
}
