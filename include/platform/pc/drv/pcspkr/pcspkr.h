#ifndef _DRV_PC_SPKR_H_
#define _DRV_PC_SPKR_H_

#define I86_PC_SPKR_STATUS_REG 0x61
#define I86_PC_SPKR_ENABLE 3

extern int pcspkr_beep(uint32_t beep);
extern int pcspkr_init();
extern int pcspkr_uninit();

extern void send_msg_counter_2 (uint8_t cmd);

extern struct device_driver_t pcspkr_driver;

extern void pc_speaker_silent();

#endif /*_DRV_PC_SPKR_H_*/
