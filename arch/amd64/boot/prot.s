.code32
init_prot:
    movl $MSG_PROT_MODE, %esi
    call puts32
.GetKernelMemSize:
    # calculate total memsz; copy memory to 0x100000
    # eax contains the address of the wanted program header
    
    addl p_memsz_offset(%eax), %edx
    addl %ebx, %eax
    subl $1, %ecx
    cmpl $0, %ecx
    ja .GetKernelMemSize
    # get load address which should be 0x10000, relocation is at 1 mb
    movl $load_address, %ebx
    addl program_offset + p_offset_offset, %ebx
    movl $relocation_address, %eax
    movl $0, %ecx
    # edx contain the total amount of memory that needs to be loaded
.LoadKernel:
    pushl %edx
    movl (%ebx), %edx
    movl %edx, (%eax)
    popl %edx
    
    addl $4, %ebx     # if ebx == 0x9B000, load more memory starting at 0x11000
    addl $4, %eax     
    addl $4, %ecx     # ecx contains memory that has been loaded
    cmpl %edx, %ecx
    jb .LoadKernel
    movl $0, %ebx     # init to zero since we are using lower half.
    movl $0, %ecx
    
    movw elf_offset+e_phentsize_offset, %bx    # sizeof program headers
    movl $program_offset, %eax                 # set eax to program offset
    movw elf_offset+e_phnum_offset, %cx        # set cx to number of program headers
    # zero out bss section
    # analyze each program header
    ##if memsz > filesz then zero out offset: data_offset + filesz
    # length: memsz - filesz

.ZeroOutBss:
    pushl %ecx
    
    addl p_memsz_offset(%eax), %edx
    addl p_filesz_offset(%eax), %ecx
    cmpl %ecx, %edx
    jbe .NextProgramHeader
    movl $relocation_address, %edi
    addl p_offset_offset(%eax), %edi
    addl p_filesz_offset(%eax), %edi
    subl program_offset + p_offset_offset, %edi
    
    addl p_memsz_offset(%eax), %esi
    subl p_filesz_offset(%eax), %esi
    
    pushl %eax        # need spare registers
    pushl %ecx
    movl $0, %ecx     # init to zero for counter
    movl $0, %eax
.ZeroOutSection:
    movl %eax, (%edi)
    addl $4, %edi
    addl $4, %ecx
    cmpl %esi, %ecx
    jb .ZeroOutSection
    popl %ecx         # restore
    popl %eax
.NextProgramHeader:    
    
    addl %ebx, %eax
    popl %ecx     
    subw $1, %cx
    cmpw $0, %cx
    ja .ZeroOutBss
skip:   
    movl $FREE_SPACE, %edi
    call SwitchToLongMode

#### DATA

.equ load_address, 0x10000        # where we initally load the kernel.
.equ relocation_address, 0x100000 # where the kernel is going to be relocated.
.equ elf_offset, 0x10000          # assume elf header size is 64 bytes.
.equ program_offset, 0x10040
.equ e_indent_offset, 0           # elf header offsets.
.equ e_type_offset, 16
.equ e_machine_offset, 18
.equ e_version_offset, 20
.equ e_entry_offset, 24
.equ e_phoff_offset, 32
.equ e_shoff_offset, 40
.equ e_flags_offset, 48
.equ e_ehsize_offset, 52
.equ e_phentsize_offset, 54
.equ e_phnum_offset, 56
.equ e_shentsize_offset, 58
.equ e_shnum_offset, 60
.equ e_shstrndx_offset, 62
.equ p_type_offset, 0             # program header offsets
.equ p_flags_offset, 4    
.equ p_offset_offset, 8   
.equ p_vaddr_offset, 16   
.equ p_paddr_offset, 24   
.equ p_filesz_offset, 32  
.equ p_memsz_offset, 40
.equ p_align_offset, 48

####
