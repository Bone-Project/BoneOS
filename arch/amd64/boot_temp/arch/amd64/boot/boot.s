.code16
.text
.global _start
_start:
	ljmp $BOOTBLOCK_SEG,$stage1_start
	
stage1_start:
#  .space 90 # BIOS PARAM BLOCK (when not using linker)
	.include "stage1.s"
stage1_end:

stage2_start:
	#.include "stage2."
stage2_end:

# real 16bit mode addressing
# BOOTBLOCK_START = BOOTBLOCK_SEGMENT<<4 + BOOTBLOCK_OFFSET
.equ BOOTBLOCK_START, 0x7c00
.equ BOOTBLOCK_SEG, 0x07c0
.equ BOOTBLOCK_OFF, 0x0000

# initial stack at 0xfff0
.equ INTERRUPT_STACK_TOP, 0xfff0
.equ INTERRUPT_STACK_SEGMENT, 0x0000
.equ INTERRUPT_STACK_OFFSET, 0xfff0

# where the kernel gets loaded (0x10000 64KB)
# remember SEG<<4 + OFF
.equ KERNEL_START, 0x10000
.equ KERNEL_SEGMENT, 0x1000
.equ KERNEL_OFF, 0x0000

# where kernel_size is stored (relative to kernel start addr above)
.equ KERNEL_SIZE_OFF, 20

.org 510  
.word 0xaa55    
// stage2_start:
//   # .org 512 # second sector
//   .include "stage2.s"
//   .align 512, 0 # align by sector, going to next
// stage2_end:
//
// stage3_start:
//   # .org 4096 # 9th sector (4KB offset)
//   .include "stage3.s"
//   .align 512, 0
// stage3_end:
