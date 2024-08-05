.section .text, "ax"

_setup32:

  mov	$0,%ah
	int	$0x13
// switch_pm:
//     # Disable interrupts
//     cli
// 	// mov	$0x4f02, %ax
//  	// mov	$0x4112, %bx
// 	// int	$0x10

//     # Enable A20 line
//     inb $0x92, %al
//     orb $2, %al
//     outb %al, $0x92


//     # Calculate and set the correct GDT base address
//     xor %eax, %eax
//     mov %ds, %ax
//     shl $4, %eax
//     add $gdt_pm, %eax
//     mov %eax, gdt_pm_descriptor + 2

//     lgdtl (gdt_pm_descriptor)

    
//     lea enter_prot_msg, %si
//     call puts16
    
//     cli
//     movl %cr0, %eax
//     orl $1, %eax
//     movl %eax, %cr0 # (we are now in protected mode)
    
//     # Far jump to stage2
//     // jmp .
//     ljmpl	$(1*8), $(pmode_entry)

// .code32
// .align 4
// pmode_entry:
//     jmp .
//     cli # Make sure to disable interupts before protected mode or triple fault
//     movw $0x10, %ax
//     movw %ax, %ds
//     movw %ax, %es
//     movw %ax, %fs
//     movw %ax, %gs
//     movw %ax, %ss
 

//     # Now that a20 enabled we have 4gib to work with so make stack larger val
//     movl $0x9000, %ebp
//     movl %ebp, %esp

//     # Debug: Write directly to video memory
//     movl $0x07690748, 0xB8000
//     jmp .
