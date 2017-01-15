#ifndef _DRV_CMOS_RTC_H_
#define _DRV_CMOS_RTC_H_

#include <stdint.h>

typedef struct uint8_rtc
{
    uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
	uint8_t weekday;
	uint8_t century;
}rtc_t;

extern uint8_t rtc_get_second();
extern uint8_t rtc_get_minute();
extern uint8_t rtc_get_hour();
extern uint8_t rtc_get_weekday();
extern uint8_t rtc_get_day_month();
extern uint8_t rtc_get_month();
extern uint8_t rtc_get_year();
extern uint8_t rtc_get_century();

extern rtc_t rtc_get_time();
extern void rtc_print_date ();
void rtc_print_struct (rtc_t current_time);

#endif // _DRV_CMOS_RTC_H_


