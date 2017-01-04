#ifndef _ARCH_CPU_INTERRUPTS_ISR_H
#define _ARCH_CPU_INTERRUPTS_ISR_H

//Routine Handlers for Exceptions
extern void int0(void);
extern void int1(void);
extern void int2(void);
extern void int3(void);
extern void int4(void);
extern void int5(void);
extern void int6(void);
extern void int7(void);
extern void int8(void);
extern void int9(void);
extern void int10(void);
extern void int11(void);
extern void int12(void);
extern void int13(void);
extern void int14(void);
extern void int15(void);
extern void int16(void);
extern void int17(void);
extern void int18(void);
extern void int19(void);
extern void int20(void);
extern void int21(void);
extern void int22(void);
extern void int23(void);
extern void int24(void);
extern void int25(void);
extern void int26(void);
extern void int27(void);
extern void int28(void);
extern void int29(void);
extern void int30(void);
extern void int31(void);


// Exception Messages for ISR Handler
extern const char *exception_messages[32];

extern void init_isr();

#endif /*_ARCH_CPU_INTERRUPTS_ISR_H*/






