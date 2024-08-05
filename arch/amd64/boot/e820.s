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
    xor %bx, %bx
    xor %bp, %bp # entry count
    mov $0xE820, %ax
    mov $0x534D, %dx # magic number (SMAP)
    push %dx
    mov $0x4150, %dx
    movl $1, %es:20(%di)  # force a valid ACPI 3.X entry
    mov $24, %cx # ask 24 bytes
    int $0x15
    jc .err_mem

.checke8201:
    pop %dx
    push %dx
    mov $0x4150, %dx
    cmp %ax, %dx
    pop %dx
    test %bx, %bx # bx = 0 implies list is only 1 entry long (worthless)
    je .err_mem
    jmp .loop_mem_start
.e8201:
    mov $0xE820, %ax          # ax, cx get trashed on every int 0x15 call
    movl $1, %es:20(%di)        # force a valid ACPI 3.X entry
    mov $24, %cx              # ask for 24 bytes again
    int $0x15
    jc .mm_end                  # carry set means "end of list already reached"
    mov $0x534D, %dx
    push %dx
    mov $0x4150, %dx     # repair potentially trashed register
.loop_mem_start:
    jcxz .skip_ent # 0 length entry (cx==0)
    cmpb $20, %cl
    
.load_ent:
#   typedef struct SMAP_entry {
# 	uint32_t BaseL; // base address uint64_t
# 	uint32_t BaseH;
# 	uint32_t LengthL; // length uint64_t
# 	uint32_t LengthH;
# 	uint32_t Type; // entry Type
# 	uint32_t ACPI; // extended
# }__attribute__((packed)) SMAP_entry_t;
    mov %es:8(%di), %cx # get lower uint16_t of mmap
    or %es:10(%di), %cx
    jz .check_upper
    jmp .entry_valid
.check_upper:
    mov %es:12(%di), %cx # check upper uint16_t
    or %es:14(%di), %cx
    jz .skip_ent
.entry_valid:
    inc %bp
    add $24, %di # each struct 24 bytes long (ACPI spec)
  
.skip_ent:
    test %bx, %bx # if 0 list complete
    jne .e8201
  
.mm_end:
    mov %bp, (mmap_ent) # store curr entry count
    clc
    ret
.err_mem:
    hlt
    jmp .err_mem

.equ mmap_ent, 0x8000 # entry count stored at this addr