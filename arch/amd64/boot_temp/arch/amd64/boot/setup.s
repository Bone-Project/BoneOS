.code16
.global _start
_start:
  	jmp	realstart

.set KERNEL_SIZE_OFF, 20
.org KERNEL_SIZE_OFF

.global kernel_size
kernel_size:
	.long	_end-_start
		
realstart:

	call .reset
	call .turn_off_cursor

	mov $setup_msg, %esi
	call bios_putstring 


// OLD 1994 grandpa interrupt
// RVeturn
// CF clear if successful
// AX = extended memory between 1M and 16M, in K (max 3C00h = 15MB)
// BX = extended memory above 16M, in 64K blocks
// CX = configured memory 1M to 16M, in K
// DX = configured memory above 16M, in 64K blocks
// CF set on error
memtest1:	
	clc
	mov	$0, %bx
	mov	$0xe801,%ax
	int	$0x15
	jc	memtest2
	
	shr	$10, %ax
	shr	$4, %bx
	add	%ax, %bx
	mov	%bx, total_memory-_start
	jmp	cont

// not as old... i guess my uncle's interrupt
// CF clear if successfulV
// AX = number of contiguous KB starting at absolute address 100000h
// CF set on error
// AH = status
// 80h invalid command (PC,PCjr)
// 86h unsupported function (XT,PS30)
memtest2:
	clc
	mov	$0, %ax
	mov	$0x88, %ah
	int	$0x15
	shr	$10, %ax
	inc	%ax
	mov	%ax, total_memory-_start


cont:
	call video_start # get video information

	# enable a20 fast mode
    inb $0x92, %al
    orb $2, %al     
	outb %al, $0x92

	jmp .

# turn off screen cursor
.turn_off_cursor:
	mov	$1,%ah
	mov	$0,%cl
	mov	$0x20,%ch
	int	$0x10
	ret

// reset disk
.reset:
    mov $0, %ah
    int $0x13
    ret

# bios_putchar invokes the bios to display
# one character on the screen.


.include "video.s"
.include "print16.s"

bios_putstring:
	mov	(%si), %al
	cmp	$0, %al
	jz	bios_putstring_done
        call	bios_putchar
	inc	%si
	jmp	bios_putstring
bios_putstring_done:
        ret

bios_putchar:
	push	%ax
	push	%bx
        mov	$14,%ah
        mov	$1,%bl
        int	$0x10
	pop	%bx
	pop	%ax
	ret
setup_msg: .asciz "inside setup\r\n"
.global total_memory
total_memory:
	.word	32
// stage2_start:
//   # .org 512 # second sector
//   .include "stage2.s"
//   .align 512, 0 # align by sector, going to next
// stage2_end:

// stage3_start:
//   # .org 4096 # 9th sector (4KB offset)
//   .include "stage3.s"
//   .align 512, 0
// stage3_end:
