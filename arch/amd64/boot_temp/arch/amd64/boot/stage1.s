stage1_start_code:
	sti
	cld	

	# setup segs as usual, done when going to differnt modes...
	sti				# disable interrupts
	cld				# clear the direction flag
	mov	%cs, %ax		# set all segments to code
	mov	%ax, %ds
	mov	%ax, %es
	mov	$INTERRUPT_STACK_SEGMENT, %ax     # set up the stack
	mov	%ax, %ss
	mov	$INTERRUPT_STACK_OFFSET, %sp # also prevents overwritten bootloader code..

	# saveee
    mov %dl, (BOOT_DRIVE) # save the C: or / drive

	// Get partition status
	// Offset 	Size 	Description
	// 0x00 	1 byte 	Boot indicator bit flag: 0 = no, 0x80 = bootable (or "active")
	// 0x01 	1 byte 	Starting head
	// 0x02 	6 bits 	Starting sector (Bits 6-7 are the upper two bits for the Starting Cylinder field.)
	// 0x03 	10 bits 	Starting Cylinder
	// 0x04 	1 byte 	System ID
	// 0x05 	1 byte 	Ending Head
	// 0x06 	6 bits 	Ending Sector (Bits 6-7 are the upper two bits for the ending cylinder field)
	// 0x07 	10 bits 	Ending Cylinder
	// 0x08 	4 bytes 	Relative Sector (to start of partition -- also equals the partition's starting LBA value)
	// 0x0C 	4 bytes 	Total Sectors in partition 

	mov partition_stat, %di
	mov $12, %cx
	rep movsb





advance:
    // 0x42(ext) way but can't get it working as of yet...
    // movb BOOT_DRIVE, %dl
    // call mydisk_load

    call _read_disk

	// GO to stage 2
    mov $KERNEL_SEG, %ax
    mov %ax, %ds # data seg
    ljmp $KERNEL_SEG, $KERNEL_OFF # code seg



#### INCLUDES FOR BOOT SECTION
// .include "a20.s"
// .include "print32.s"
.include "print16.s"
// .include "disk.s"
.include "disk_leg.s"
// .include "e820.s"
.include "gdt_pm.s"
// .include "iso9960.s"
// stage2_id: .asciz "/BOOT/STAGET.BIN;1" # iso996 path
######## Data for boot section
// .equ KERNEL_OFFSET, 0x1000
// .equ FREE_SPACE, 0x9000
.set KERNEL_SEG, 0x1000
.set KERNEL_OFF,  0x0
.set KERNEL_SIZE_OFF, 20
.set SECTOR_SIZE, 512
enter_prot_msg: .asciz "entering protected mode...\n"
pmode_msg: .asciz "Now in 32-bit protected mode!"
BOOT_DRIVE:  .byte 0
mmap_ent:    .long 0
partition_stat: .byte 0
########
