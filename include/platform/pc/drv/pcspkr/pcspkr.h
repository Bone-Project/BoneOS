#ifndef _DRV_PC_SPKR_H_
#define _DRV_PC_SPKR_H_

extern int pcspkr_beep();
extern int pcspkr_init();
extern int pcspkr_uninit();

extern void send_msg_counter_2 (uint8_t cmd);

extern struct device_driver_t pcspkr_driver;

#endif /*_DRV_PC_SPKR_H_*/
