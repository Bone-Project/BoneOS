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
#include <string/string.h>
#include <str_t.h>


static char* months_str[12] =
{
    "Jan", "Feb" , "Mar", "Apr" , "May",
    "Jun", "Jul", "Aug" , "Sep", "Oct",
    "Nov", "Dec"
};

static char* dates_str[7] =
{
    "Mon", "Tue" , "Wed", "Thu" , "Fri",
    "Sat", "Sun"
};

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
    outb(CMOS_REGISTER_SELECT, CMOS_REGISTER_WEEKDAY);
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

static str_t month_to_text(uint8_t num)
{
    str_t month;

    if(num < 1 || num > 12)
        panik("INVALID MONTH");

    strcpy(month.str,months_str[num-1]);
    return month;
}

static str_t date_to_text(uint8_t num)
{
    str_t date;
    if(num < 1 || num > 7)
        panik("INVALID MONTH");

    strcpy(date.str,dates_str[num-2]);
    return date;
}

rtc_t rtc_get_time()
{
    rtc_t curr;
    rtc_t last; //Keep reading time until we get the same values twice

    memset(&last, 0xFF, sizeof(last));
    for (curr.year = 0; memcmp(&curr, &last, sizeof(curr)); last = curr)
    {
        curr.century = rtc_get_century();
        curr.year = rtc_get_year();
        curr.month = rtc_get_month();
        curr.day = rtc_get_day_month();
        curr.hour = rtc_get_hour();
        curr.minute = rtc_get_minute();
        curr.second = rtc_get_second();
        curr.weekday = rtc_get_weekday();
    }
    return curr;
}

void rtc_print_date()
{
    rtc_t current_time = rtc_get_time();
    str_t _month = month_to_text(current_time.month);
    str_t _weekday = date_to_text(current_time.weekday);
    printk("%s %s %x %x:%x:%x UTC %x%x\n",
            (_weekday.str),
            (_month.str),
            current_time.day,
            current_time.hour,
            current_time.minute,
            current_time.second,
            current_time.century,
            current_time.year);
}

void rtc_print_struct(rtc_t current_time)
{
    str_t _month = month_to_text(current_time.month);
    str_t _weekday = date_to_text(current_time.weekday);
    printk("%s %s %x %x:%x:%x UTC %x%x\n",
            (_month.str),
            (_weekday.str),
            current_time.day,
            current_time.hour,
            current_time.minute,
            current_time.second,
            current_time.century,
            current_time.year);
}
