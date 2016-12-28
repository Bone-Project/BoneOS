#ifndef _ARCH_CPU_INTERRUPTS_PIC_H_
#define _ARCH_CPU_INTERRUPTS_PIC_H_

/*
 * PIC UTILITIES
 */

//MASTER PIC ADRESSES
#define I386_MASTER_REG_COMMAND		0x20 // command register
#define I386_MASTER_REG_STATUS		0x20 // status register
#define I386_MASTER_REG_DATA		0x21 // data register
#define I386_MASTER_REG_IMR			0x21 // interrupt mask register
 
//SLAVE PIC ADRESSES
#define I386_SLAVE_REG_COMMAND		0xA0 //command register			
#define I386_SLAVE_REG_STATUS		0xA0 //status register
#define I386_SLAVE_REG_DATA			0xA1 //data register
#define I386_SLAVE_REG_IMR			0xA1 //interrupt mask register


/*
 * PIC Commands
 */
#define PIC_EOI 0x20 //EOI || End of Interrupt



/*
 * Initialization Control Word 4 bit masks
 */
#define I386_PIC_ICW4_MASK_UPM		0x1	//00000001	// 80x86 Mode
#define I386_PIC_ICW4_MASK_AEOI		0x2	//00000010	// Automatic EOI
#define I386_PIC_ICW4_MASK_MS		0x4	//00000100	// Selects buffer type
#define I386_PIC_ICW4_MASK_BUF		0x8	//00001000	// Buffered mode
#define I386_PIC_ICW4_MASK_SFNM		0x10//00010000	// Special fully-nested mode

/*
 * Initialization Control Word's Command Bits
 */
//ICW1 Defintions
#define i386_PIC_ICW1_IVT_ALWAYS_0               0x0
#define i386_PIC_ICW1_INITALIZED                 0x10
#define i386_PIC_ICW1_LEVEL_TRIGGERED            0x8
#define i386_PIC_ICW1_EDGE_TRIGGERED             0x0
#define i386_PIC_ICW1_CALL_ADDRESS_4             0x4
#define i386_PIC_ICW1_CALL_ADDRESS_8             0x0
#define i386_PIC_ICW1_ONE_PIC                    0x2
#define i386_PIC_ICW1_CASCADE_PIC                0x0
#define I386_PIC_ICW1_EXPECT_ICW4                0x1

#define ICW1 i386_PIC_ICW1_IVT_ALWAYS_0     |\
             i386_PIC_ICW1_IVT_ALWAYS_0     |\
             i386_PIC_ICW1_IVT_ALWAYS_0     |\
             i386_PIC_ICW1_INITALIZED       |\
             i386_PIC_ICW1_EDGE_TRIGGERED   |\
             i386_PIC_ICW1_CASCADE_PIC      |\
             i386_PIC_ICW1_CALL_ADDRESS_8   |\
             i386_PIC_ICW1_CASCADE_PIC      |\
             I386_PIC_ICW1_EXPECT_ICW4

//ICW2
#define IRQ_START 0x20 //32 || IRQ 0
#define IRQ_END     0x28 //47 || IRQ LAST        

//ICW3
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR0 0x1
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR1 0x2
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR2 0x4
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR3 0x8
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR4 0x10
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR5 0x20
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR6 0x40
#define I386_PIC_ICW2_IRQLINE_PRIMARY_IR7 0x80

#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR0 0x0
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR1 0x1
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR2 0x2
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR3 0x3
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR4 0x4
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR5 0x5
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR6 0x6
#define I386_PIC_ICW2_IRQLINE_SECONDARY_IR7 0x7                          

//NULL OUT REGS
#define PIC_NULL 0x0                  


#endif /*_ARCH_CPU_INTERRUPTS_PIC_H_*/



