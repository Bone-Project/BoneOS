.code64

# INPUT => RBX (address of string to print)
putc64:
    pushq %rbx
    pushq %rdx
    pushq %rax
    movq $VIDEO_MEM, %rdx 
puts64:
    lahf
    movb (%rbx), %al
    movb $WHITE_BLACK, %ah
    cmpb $0, %al
    je puts64_done
    movw %ax, (%rdx)  # Write char+attribute to video memory
    addq $1, %rbx     # Next char 
    addq $2, %rdx     # Next video 
    jmp puts64
puts64_done:
    popq %rax
    popq %rdx
    popq %rbx
    sahf
    ret

# DATA
.equ VIDEO_MEM, 0xb8000
.equ WHITE_BLACK, 0x0f
##

