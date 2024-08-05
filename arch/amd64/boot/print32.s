.code32

# INPUT => EBX (address of string to print)
putc32:
    pushl %ebx
    pushl %edx
    pushl %eax
    movl $VIDEO_MEM, %edx 
puts32:
    movb (%ebx), %al
    movb $WHITE_BLACK, %ah
    cmpb $0, %al
    je puts32_done
    movw %ax, (%edx)  # Write char+attribute to video memory
    addl $1, %ebx     # Next char 
    addl $2, %edx     # Next video 
    jmp puts32
puts32_done:
    popl %eax
    popl %edx
    popl %ebx
    ret

# DATA
.equ VIDEO_MEM, 0xb8000
.equ WHITE_BLACK, 0x0f
##
