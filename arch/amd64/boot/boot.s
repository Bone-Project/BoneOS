.section .boot, "ax"
.code16
.global _start
_start:
    # Setup segs + save boot drive
    xor %ax, %ax
    mov %ax, %ss
    # Set up stack so that it starts below Main.
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    cld
    movb %dl, BOOT_DRIVE
    // movw $MSG_REAL_MODE, %si
    // call puts16
    movw $0x7C00, %sp # lets not override bootloader code...
    call _has_a20 
    cmpw $0x0, %ax
    jne advance
    call _a20
advance:
    movw $MEMORY_MAP, %di
    call mem_map
    call load_kernel

switch_pm:
    # Disable interrupts
    cli

    # Enable A20 line
    inb $0x92, %al
    orb $2, %al
    outb %al, $0x92

    # Load GDT
    lgdt gdt_descriptor

    # Enter protected mode
    movl %cr0, %eax
    orl $1, %eax
    movl %eax, %cr0

    jmp prot_tramp # avoiding relocation 16/32 relocation issues

load_kernel:
    pusha
    // movw $MSG_LOAD_KERNEL, %si
    // call puts16
    movb BOOT_DRIVE, %dl
    call mydisk_load
    popa
    ret

#### INCLUDES FOR BOOT SECTION
.include "gdt.s"
.include "a20.s"
.include "print16.s"
.include "disk.s"
.include "e820.s"
# Include other 16-bit code files here

# Data for boot section
.equ KERNEL_OFFSET, 0x1000
.equ FREE_SPACE, 0x9000
.equ MEMORY_MAP, 0x1000
BOOT_DRIVE:  .byte 0
mmap_ent:    .long 0
// MSG_REAL_MODE:	.asciz "Started in 16-bit Real Mode"

prot_tramp:
    .code32
    jmp init_prot

# End of boot section
.space 510 - (. - _start), 0
.word 0xaa55

### 32 BIT

.section .text, "ax"
.code32

# Include 32-bit and 64-bit code files
.include "print32.s"
.include "idt.s"
.include "prot.s"

.code32

CheckCPU:
    # Check whether CPUID is supported or not.
    pushfl                            # Get flags in EAX register.
 
    popl %eax
    movl %eax, %ecx  
    xorl $0x200000, %eax 
    pushl %eax 
    popfl
 
    pushfl 
    popl %eax
    xorl %ecx, %eax
    shrl $21, %eax 
    andl $1, %eax                     # Check whether bit 21 is set or not. If EAX now contains 0, CPUID isn't supported.
    pushl %ecx
    popfl 
 
    testl %eax, %eax
    jz NoLongMode
 
    movl $0x80000000, %eax   
    cpuid                 
 
    cmpl $0x80000001, %eax            # Check whether extended function 0x80000001 is available are not.
    jb NoLongMode                     # If not, long mode not supported.
 
    movl $0x80000001, %eax  
    cpuid                 
    testl $(1 << 29), %edx            # Test if the LM-bit, is set or not.
    jz NoLongMode                     # If not Long mode not supported.
 
    ret
 
NoLongMode:
    stc
    ret

.code32
### DATA
MSG_PROT_MODE:    .asciz "Successfully landed in 32-bit Protected Mode"
####


.code64


### INCLUDES
.include "print64.s"
###

##### 64 BIT
    movw $0x7C00, %sp # lets not override bootloader code...
    call _has_a20 
    cmpw $0x0, %ax
    jne advance
    call _a20
.include "long.s"


BEGIN_LM:
    # Blank out the screen to a blue color.
    movq $MEMORY_MAP, %rdi		# set up arguments for kmain
    movl mmap_ent, %esi		

    # Higher half kernel. Phys Adr: 0x100000, Virt: 0xfff..88.00
    movabs $kernel_start, %rax
    jmp *%rax # change to call later to provide args
    jmp .

#### DATA
.code64
no_long_mode_msg: .asciz "ERROR: CPU does not support long mode.\n\r"
MSG_LOAD_KERNEL:    .asciz "Loading kernel into memory"
MSG_LONG_MODE:    .asciz "Successfully landed in Long Mode"
###
