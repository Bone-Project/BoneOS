#ifndef _DRV_CMOS_RTC_H_
#define _DRV_CMOS_RTC_H_

#include <stdint.h>

extern uint8_t rtc_get_second();
extern uint8_t rtc_get_minute();
extern uint8_t rtc_get_hour();
extern uint8_t rtc_get_weekday();
extern uint8_t rtc_get_day_month();
extern uint8_t rtc_get_month();
extern uint8_t rtc_get_year();
extern uint8_t rtc_get_century();


extern void rtc_print_date_cmd ();

#endif // _DRV_CMOS_RTC_H_
