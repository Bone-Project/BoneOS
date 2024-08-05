#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif
// real 16bit mode addressing
// BOOTBLOCK_START = BOOTBLOCK_SEGMENT<<4 + BOOTBLOCK_OFFSET
#define BOOTBLOCK_START 0x7c00
#define BOOTBLOCK_SEG 0x07c0
#define BOOTBLOCK_OFF 0x0000

// inital stack at 0xfff0
#define INTERRUPT_STACK_TOP     0xfff0
#define INTERRUPT_STACK_SEGMENT 0x0000
#define INTERRUPT_STACK_OFFSET  0xfff0

// where the kernel gets loaded (0x10000 64KB)
// remember SEG<<4 + OFF
#define KERNEL_START   0x10000
#define KERNEL_SEGMENT 0x1000
#define KERNEL_OFF  0x0000

// where kernel_size is stored (relative to kernel start addr above)
#define KERNEL_SIZE_OFF 20
