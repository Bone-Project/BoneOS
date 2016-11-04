#ifndef _DRV_PIT_H_
#define _DRV_PIT_H_

#define	I386_PIT_OCW_BINCOUNT_BINARY 0x0
#define I386_PIT_OCW_BINCOUNT_BCD 0x1

#define I386_PIT_RATE_GEN 0x4
#define I386_PIT_SQUARE_WAVE_GEN 0x3
#define I386_PIT_SCO_COUNTER_0 0x0
#define I386_PIT_SCO_COUNTER_1 0x2
#define I386_PIT_SCO_COUNTER_3 0x3

#define	I386_PIT_COUTNER_0 0x40
#define	I386_PIT_COUTNER_1 0x41
#define	I386_PIT_COUTNER_2 0x42
#define I386_PIT_COMMAND_REG 0x43




//Change this to OR's
#define COMMAND_FULL 0x36

extern void init_pit();

#endif /*_DRV_PIT_H_*/