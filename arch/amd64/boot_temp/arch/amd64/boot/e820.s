.code16
# Memory Tests
# Goal: Mem size above 1MB aka Kernel load addr
# Reference: https://en.wikipedia.org/wiki/E820
# we can go E820 (modern much more info) or E801 (compatibility)
mem_map:
    # Lets try E820
    # note: initially di is 0, be sure to set it to a value so that the BIOS code will not be overwritten. 
    #       The consequence of overwriting the BIOS code will lead to problems like getting stuck in `int 0x15`
    # inputs: es:di -> destination buffer for 24 byte entries
    # outputs: bp = entry count, trashes all registers except si
    movw $0x8004, %di          # Set di to 0x8004. Otherwise this code will get stuck in `int 0x15` after some entries are fetched 
    xorl %ebx, %ebx            # ebx must be 0 to start
    xorw %bp, %bp              # keep an entry count in bp
    movl $0x0534D4150, %edx    # Place "SMAP" into edx
    movl $0xe820, %eax
    movl $1, %es:20(%di)       # force a valid ACPI 3.X entry
    movl $24, %ecx             # ask for 24 bytes
    int $0x15
    jc .err_mem                 # carry set on first call means "unsupported function"
    movl $0x0534D4150, %edx    # Some BIOSes apparently trash this register?
    cmpl %edx, %eax            # on success, eax must have been reset to "SMAP"
    jne .err_mem
    testl %ebx, %ebx           # ebx = 0 implies list is only 1 entry long (worthless)
    je .err_mem
    jmp .e8201

.checke8201:
    movl $0xe820, %eax         # eax, ecx get trashed on every int 0x15 call
    movl $1, %es:20(%di)       # force a valid ACPI 3.X entry
    movl $24, %ecx             # ask for 24 bytes again
    int $0x15
    jc .mm_end                 # carry set means "end of list already reached"
    movl $0x0534D4150, %edx    # repair potentially trashed register

.e8201:
    movl $0xe820, %eax         # eax, ecx get trashed on every int 0x15 call
    movl $1, %es:20(%di)       # force a valid ACPI 3.X entry
    movl $24, %ecx             # ask for 24 bytes again
    int $0x15
    jc .mm_end                  # carry set means "end of list already reached"
    movl $0x0534D4150, %edx    # repair potentially trashed register

.loop_mem_start:
    jecxz .skip_ent            # skip any 0 length entries
    cmpb $20, %cl             # got a 24 byte ACPI 3.X response?
    jbe .load_ent
    testb $1, %es:20(%di)     # if so: is the "ignore this data" bit clear?
    je .skip_ent
    

#   typedef struct SMAP_entry {
# 	uint32_t BaseL; // base address uint64_t
# 	uint32_t BaseH;
# 	uint32_t LengthL; // length uint64_t
# 	uint32_t LengthH;
# 	uint32_t Type; // entry Type
# 	uint32_t ACPI; // extended
# }__attribute__((packed)) SMAP_entry_t;
.load_ent:
    movl %es:8(%di), %ecx     # get lower uint32_t of memory region length
    orl %es:12(%di), %ecx     # "or" it with upper uint32_t to test for zero
    jz .skip_ent               # if length uint64_t is 0, skip entry
    incw %bp                  # got a good entry: ++count, move to next storage spot
    addw $24, %di
.skip_ent:
    testl %ebx, %ebx # if 0 list complete
    jne .e8201


### Finished
.mm_end:
    movw %bp, mmap_ent # store curr entry count
    clc
    ret
.err_mem:
    stc
    ret

.equ mmap_ent, 0x8000 # entry count stored at this addr