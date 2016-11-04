#ifndef _ARCH_CPU_INTERRUPTS_IRQ_H
#define _ARCH_CPU_INTERRUPTS_IRQ_H

#ifndef KERNEL_CALL
extern int_routines irq_routines[16];
extern void install_irq_handler(int num,int_routines route);
#endif

extern void remap_pic_irq();
extern void init_irq();

#endif /*_ARCH_CPU_INTERRUPTS_IRQ_H*/