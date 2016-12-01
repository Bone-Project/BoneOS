#ifndef _DRV_PIT_H_
#define _DRV_PIT_H_

#include <stdbool.h>

/*
 * Operation Control Words 
 * Commands Available for 
 * the PIT.
 */
//START
#define I386_PIT_OCW_BINCOUNT_BINARY 0x0 //0
#define I386_PIT_OCW_BINCOUNT_BCD    0x1 //1

#define I386_PIT_OCW_MODE_TERMINALCOUNT  0x0 //0000 
#define I386_PIT_OCW_MODE_ONESHOT        0x2 //0010
#define I386_PIT_OCW_MODE_RATEGEN        0x4 //0100
#define I386_PIT_OCW_MODE_SQUAREWAVEGEN  0x6 //0110
#define I386_PIT_OCW_MODE_SOFTWARETRIG   0x8 //1000

#define I386_PIT_OCW_RL_LATCH   0       //000000    
#define I386_PIT_OCW_RL_LSBONLY 0x10    //010000
#define I386_PIT_OCW_RL_MSBONLY 0x20    //100000
#define I386_PIT_OCW_RL_DATA    0x30    //110000

#define I386_PIT_OCW_SCO_COUNTER_0 0x0  //00000000
#define I386_PIT_OCW_SCO_COUNTER_1 0x40 //01000000
#define I386_PIT_OCW_SCO_COUNTER_2 0x80 //10000000
//END


/*
 * PIT Counter
 * internal registers
 * port addresses
 */
#define I386_PIT_COUNTER_0_REG    0x40
#define I386_PIT_COUNTER_1_REG    0x41
#define I386_PIT_COUNTER_2_REG    0x42
#define I386_PIT_CONTROL_WORD_REG 0x43


#define IRQ_SEC_HIT 19

extern volatile uint32_t pit_ticks;
extern volatile bool initalized_pit;
extern volatile bool status_pit;

extern int init_pit();
extern int uninit_pit();

#endif /*_DRV_PIT_H_*/