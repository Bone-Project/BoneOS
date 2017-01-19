#ifndef _DRV_PC_SPKR_H_
#define _DRV_PC_SPKR_H_

extern int pcspkr_beep();
extern int pcspkr_init();
extern int pcspkr_uninit();

extern struct device_driver_t pcspkr_driver;

#endif /*_DRV_PC_SPKR_H_*/
