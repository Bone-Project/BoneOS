.code32


# -- #define's
# - amazing reference on x86 paging: https://cs4118.github.io/www/2023-1/lect/18-x86-paging.html
# = another amazing read: https://web.archive.org/web/20230617201503/http://www.rcollins.org/articles/2mpages/2MPages.html

.equ PAGE_PRESENT, (1 << 0)
.equ PAGE_WRITE, (1 << 1)
.equ CODE_SEG, 0x0008
.equ DATA_SEG, 0x0010
.equ PAGING_DATA, 0x9000

# Function to switch directly to long mode from real mode.
# Identity maps the first 2MiB.
# Uses AT&T syntax.

# es:edi    Should point to a valid page-aligned 16KiB buffer, for the PML4, PDPT, PD and a PT.
# ss:esp    Should point to memory that can be used as a small (1 uint32_t) stack

SwitchToLongMode:
    # Zero out the 16KiB buffer.
    # Since we are doing a rep stosd, count should be bytes/4.   
    pushl %edi                           # REP STOSD alters DI.
    movl $0x1000, %ecx
    xorl %eax, %eax
    cld
    rep stosl
    popl %edi                            # Get DI back.
    
    # zero out tables
    pushl %edi
    pushl %edx

    leal 0x9000(%edi), %edx
    movl $0x0, %eax


# PML4 visual
# #define PAGE_ENTRY_COUNT 512

#typedef struct {
#    uint64_t entries[PAGE_ENTRY_COUNT];
#} PageTable;

#struct PageTables {
#    PageTable pml4_table;
#    PageTable pdpt_table;
#    PageTable pd_table;
#    PageTable pt_table;
#} __attribute__((aligned(4096)));


.ZeroOutAllTable:
    movl %eax, (%edi)  # zero out
    addl $4, %edi          
    cmpl %edx, %edi    
    jb .ZeroOutAllTable

    popl %edx
    popl %edi

    # Build the Page Map Level 4.
    # es:di points to the Page Map Level 4 table.    
    leal 0x1000(%edi), %eax         # Put the address of the Page Directory Pointer Table in to EAX.
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax # Or EAX with the flags - present flag, writable flag.
    movl %eax, (%edi)                  # Store the value of EAX as the first PML4E.

    # Build the Page Directory Pointer Table.
    leal 0x2000(%edi), %eax         # Put the address of the Page Directory in to EAX.
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax # Or EAX with the flags - present flag, writable flag.
    movl %eax, 0x1000(%edi)         # Store the value of EAX as the first PDPTE.

    # Build the Page Directory.
    leal 0x3000(%edi), %eax         # Put the address of the Page Table in to EAX.
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax # Or EAX with the flags - present flag, writeable flag.
    movl %eax, 0x2000(%edi)         # Store to value of EAX as the first PDE.
   
    # Build the Identity map.
    pushl %edi                           # Save DI for the time being.
    leal 0x3000(%edi), %edi             # Point DI to the page table.
    movl $(PAGE_PRESENT | PAGE_WRITE), %eax    # Move the flags into EAX - and point it to 0x0000.    

### LET MAPPING BEGIN
# LoopIdentityPageTable maps 0x0 - 0x200000 to 0x0 - 0x200000
# LoopKernelPageTable maps 0x100000 - 0x300000 to some page table entries


# Map Kernel to same place in Physical-Virt (Identitiy Mapping)
.LoopIdentityPageTable:
    movl %eax, (%edi)
    addl $0x1000, %eax
    addl $8, %edi
    cmpl $0x200000, %eax                 # If we did all 2MiB, end.
    jb .LoopIdentityPageTable
 
    popl %edi                            # Restore DI.

    # build kernel map
    leal (%edi), %eax        
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax
    movl %eax, 0xff0(%edi)     # move the first entry of PML4 into its second last entry for recursive page mapping. 

    # fill last entry of  PML4 with address edi + 0x4000
    leal 0x4000(%edi), %eax         # Put the address of the Page Directory Pointer Table in to EAX.
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax # Or EAX with the flags - present flag, writable flag.
    movl %eax, 0xff8(%edi)                  # Store the value of EAX as the last PML4E.

    # fill first entry of PDPT at edi + 0x4000
    leal 0x5000(%edi), %eax    
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax # need to change this to point to kernel memory address
    movl %eax, 0x4ff0(%edi)

    # fill first entry of PD
    leal 0x6000(%edi), %eax
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax
    movl %eax, 0x5000(%edi)    

    # fill 2m of memory in PT
    pushl %edi                           # Save DI for the time being.
    leal 0x6000(%edi), %edi             # Point DI to the page table.
    movl $0x100000, %eax
    orl $(PAGE_PRESENT | PAGE_WRITE), %eax    # Move the flags into EAX - and point it to 0x100000.
        
.LoopKernelPageTable:
    movl %eax, (%edi)
    addl $0x1000, %eax
    addl $8, %edi
    cmpl $0x300000, %eax
    jb .LoopKernelPageTable
    
    popl %edi                            # Restore DI.
    
    # Disable IRQs
    movb $0xFF, %al                      # Out 0xFF to 0xA1 and 0x21 to disable all IRQs.
    outb %al, $0xA1
    outb %al, $0x21
  
    # need to ensure disabled
    nop
    nop
 
    lidt IDT                        # Load a zero length IDT so that any NMI causes a triple fault.
 
    # Enter long mode.
    movl $0xA0, %eax                # Set the PAE and PGE bit.
    movl %eax, %cr4
 
    movl %edi, %edx                      # Point CR3 at the PML4.
    movl %edx, %cr3
 
    movl $0xC0000080, %ecx               # Read from the EFER MSR. 
    rdmsr    

    orl $0x00000100, %eax                # Set the LME bit.
    wrmsr
 
    movl %cr0, %ebx                      # Activate long mode -
    orl $0x80000001, %ebx                 # - by enabling paging and protection simultaneously.
    movl %ebx, %cr0                    
 
    lgdt GDT_Pointer                
 
    ljmp $CODE_SEG, $LongMode             # Load CS with 64 bit segment and flush the instruction cache
 
# Global Descriptor Table
GDT:
Null:
    .quad 0x0000000000000000             
 
Code:
    .word 0x0 
    .word 0x0
    .byte 0b00000000
    .byte 0b10011000
    .byte 0b00100000
    .byte 0b00000000
    
Data:    
    .word 0x0
    .word 0x0
    .byte 0b00000000
    .byte 0b10010000
    .byte 0b00000000
    .byte 0b00000000
    
.align 4
    .word 0                              # Padding to make the "address of the GDT" field aligned on a 4-byte boundary
 
GDT_Pointer:
    .word . - GDT - 1                    # 16-bit Size (Limit) of GDT.
    .long GDT                            # 32-bit Base Address of GDT. (CPU will zero extend to 64-bit)
 
 
.code64      
LongMode:
    # setup data segments
    movw $DATA_SEG, %ax
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs

    movq $0x90000, %rsp
    jmp BEGIN_LM
