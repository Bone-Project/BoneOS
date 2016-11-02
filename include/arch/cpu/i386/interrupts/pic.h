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
#define ICW1 0x11


#endif /*_ARCH_CPU_INTERRUPTS_PIC_H_*/