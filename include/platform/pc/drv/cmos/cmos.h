#ifndef _DRV_CMOS_H_
#define _DRV_CMOS_H_

#define CMOS_REGISTER_SECONDS  0x00
#define CMOS_REGISTER_MINUTES  0x02
#define CMOS_REGISTER_HOURS    0x04
#define CMOS_REGISTER_WEEKDAY  0x06 //Tuesday
#define CMOS_REGISTER_DAYMONTH 0x07 //Tuessday the -->> 23 <<--
#define CMOS_REGISTER_MONTH    0x08 
#define CMOS_REGISTER_YEAR     0x09
#define CMOS_REGISTER_CENTURY  0x32 //Maybe Available.. start supporting since 1990's...

#define CMOS_REGISTER_SELECT   0x70
#define CMOS_REGiSTER_DATA     0x71

#endif // _DRV_CMOS_H_
