#ifndef _ARCH_CPU_INTERRUPTS_IRQ_H
#define _ARCH_CPU_INTERRUPTS_IRQ_H

#ifndef KERNEL_CALL
extern int_routines irq_routines[16];
extern void install_irq_handler(int num,int_routines route);
extern void uninstall_irq_handler(int num);
#endif

extern void remap_pic_irq();
extern void init_irq();

/*All Interupt Request handlers*/
extern void int32(void);
extern void int33(void);
extern void int34(void);
extern void int35(void);
extern void int36(void);
extern void int37(void);
extern void int38(void);
extern void int39(void);
extern void int40(void);
extern void int41(void);
extern void int42(void);
extern void int43(void);
extern void int44(void);
extern void int45(void);
extern void int46(void);
extern void int47(void);

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



