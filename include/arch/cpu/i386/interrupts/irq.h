#ifndef _ARCH_CPU_INTERRUPTS_IRQ_H
#define _ARCH_CPU_INTERRUPTS_IRQ_H

extern int_routines irq_routines[16];

extern void remap_pic_irq();

#endif /*_ARCH_CPU_INTERRUPTS_IRQ_H*/