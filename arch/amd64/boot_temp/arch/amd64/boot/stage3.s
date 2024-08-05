.section .boot, "ax"
.code64
   
stage3_start_code:
    cli
    # setup data segments
    movw $DATA_SEG64, %ax  
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    movq $0x90000, %rsp

    # Blank out the screen to a blue color.
    // movq $MEMORY_MAP, %rdi		# set up arguments for kmain
    // movq mmap_ent, %rsi		

    # Higher half kernel. Phys Adr: 0x100000, Virt: 0xfff..88.00
    mov $0x100000, %rax 
    jmp *%rax # change to call later to provide args
    jmp .


### INCLUDES
.include "print64.s"
// .include "long.s"
###