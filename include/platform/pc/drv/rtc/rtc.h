#ifndef _DRV_RTC_H_
#define _DRV_RTC_H_

typedef struct uint8_rtc
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} rtc_t;
extern rtc_t rtc_get();
extern void rtc_print_time ();

#endif // _DRV_RTC_H_
