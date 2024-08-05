# INPUT => EBX (address of string to print)
puts32:
    pushl %ebp
    movl %esp, %ebp
    pushl %ebx
    movl 8(%ebp), %ebx  # Get string address from stack
    movl $0xb8000, %edx # Video memory address
    movb $0x0f, %ah     # White on black attribute
puts32_loop:
    movb (%ebx), %al
    testb %al, %al
    jz puts32_done
    movw %ax, (%edx)
    addl $1, %ebx
    addl $2, %edx
    jmp puts32_loop
puts32_done:
    popl %ebx
    leave
    ret

# DATA
// .equ VIDEO_MEM, 0xb8000
// .equ WHITE_BLACK, 0x0f
##
