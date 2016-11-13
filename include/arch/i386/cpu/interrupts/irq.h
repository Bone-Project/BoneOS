#ifndef _ARCH_CPU_INTERRUPTS_IRQ_H
#define _ARCH_CPU_INTERRUPTS_IRQ_H

#ifndef KERNEL_CALL
extern int_routines irq_routines[16];
extern void install_irq_handler(int num,int_routines route);
#endif

extern void remap_pic_irq();
extern void init_irq();

/*
 * IRQ #'s
 */
#define IRQ_NUM_PIT 0
#define IRQ_NUM_KBD 1
#define IRQ_NUM_CASCADE 2
#define IRQ_NUM_COM_0 3
#define IRQ_NUM_COM_1 4
#define IRQ_NUM_LPT_2 5
#define IRQ_NUM_FLOPPY_DISK 6
#define IRQ_NUM_LPT1 7
#define IRQ_NUM_CMOS 8

#define IRQ_NUM_PS2_MOUSE 12
#define IRQ_NUM_FPU 13
#define IRQ_NUM_PRIMARY_ATA 14
#define IRQ_NUM_SECONDARY_ATA 15

#endif /*_ARCH_CPU_INTERRUPTS_IRQ_H*/