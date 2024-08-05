
.section .boot, "ax"
.code32

# -- #define's
# - amazing reference on x86 paging: https://cs4118.github.io/www/2023-1/lect/18-x86-paging.html
# = another amazing read: https://web.archive.org/web/20230617201503/http://www.rcollins.org/articles/2mpages/2MPages.html


stage2_start_code:
  cli
# Includes
// .include "print32.s"
.include "gdt_lm.s"
// .include "idt.s"
// .include "prot.s"
####
    // lea MSG_PROT_MODE, %si
    // call puts32
    jmp .
     # Setup segs for protected mode
    movw $0x10, %ax  
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs


# GAS doesnt support dotted labels...
long_mode_entry:

    cpu_id_check:
        pushfd
        popl %eax
        mov %eax, %ecx

        shrl $21, %eax

        pushl %eax # Update flags register
        popfd

        pushl %ecx # Now for checking (go back to org)
        popfd 

        xor %eax, %ecx
        jz long_mode_err

    cpu_id_extended:
        movl $0x80000000, %eax
        cpuid // eax => highest extended function input value understood by CPUID
        cmpl $0x80000001, %eax # if its lower no extended ability
        jb long_mode_err
        
    cpu_id_long_mode:
        # CPUID EAX=80000001h: Feature Information in EDX and ECX
        #
        # Bit EDX Feature                  ECX Feature
        # --- ---------------------------- ----------------------------
        # 0   fpu: Onboard x87 FPU         sse3: SSE3 instructions
        # 1   vme: Virtual 8086 mode ext.  pclmulqdq: PCLMULQDQ instruction
        # 2   de: Debugging extensions     dtes64: 64-bit debug store
        # 3   pse: Page Size Extension     monitor: MONITOR and MWAIT instructions
        # 4   tsc: Time Stamp Counter      ds-cpl: CPL qualified debug store
        # 5   msr: Model-specific regs     vmx: Virtual Machine eXtensions
        # 6   pae: Physical Address Ext.   smx: Safer Mode Extensions
        # 7   mce: Machine Check Exception est: Enhanced SpeedStep
        # 8   cx8: CMPXCHG8B instruction   tm2: Thermal Monitor 2
        # 9   apic: Onboard APIC           ssse3: Supplemental SSE3 instructions
        # 10  (reserved)                   cnxt-id: L1 Context ID
        # 11  sep: SYSENTER/SYSEXIT        sdbg: Silicon Debug interface
        # 12  mtrr: Memory Type Range Regs fma: Fused multiply-add (FMA3)
        # 13  pge: Page Global Enable      cx16: CMPXCHG16B instruction
        # 14  mca: Machine check arch.     xtpr: Can disable task priority messages
        # 15  cmov: Conditional move instr. pdcm: Perfmon & debug capability
        # 16  pat: Page Attribute Table    (reserved)
        # 17  pse-36: 36-bit PSE           pcid: Process context identifiers
        # 18  psn: Processor Serial Number dca: Direct cache access for DMA writes
        # 19  clfsh: CLFLUSH instruction   sse4.1: SSE4.1 instructions
        # 20  (reserved)                   sse4.2: SSE4.2 instructions
        # 21  ds: Debug store              x2apic: x2APIC
        # 22  acpi: Thermal control MSRs   movbe: MOVBE instruction
        # 23  mmx: MMX instructions        popcnt: POPCNT instruction
        # 24  fxsr: FXSAVE/FXRSTOR         tsc-deadline: TSC deadline value
        # 25  sse: SSE instructions        aes-ni: AES instruction set
        # 26  sse2: SSE2 instructions      xsave: XSAVE, XRSTOR, etc.
        # 27  ss: Self-snoop               osxsave: XSAVE enabled by OS
        # 28  htt: Max APIC IDs reserved   avx: Advanced Vector Extensions
        # 29  tm: Thermal monitor          f16c: Float16 conversion
        # 30  ia64: IA64 emulating x86     rdrand: RDRAND instruction
        # 31  pbe: Pending Break Enable    hypervisor: Hypervisor present
        movl $0x80000001, %eax
        cpuid
        testl 1<<29, %edx
        jz long_mode_err

    long_mode_paging:
        # In protected mode a page table entry was only four bytes long, so you had 1024 entries per table. In long mode, however, you only have 512 entries per table as each entry is eight bytes long
        # This means that one entry in a PT can address 4kB, 
        #                 one entry in a PDT can address 2MB, 
        #                 one entry in a PDPT can address 1GB  
        #                 one entry in a PML4T can address 512GB. 
        # This means that *only* 256TB can be addressed. (512 entries of PML4T)

    # Identity map the first 2MiB.
    identity_map:
        # First Clear
        movl $0x1000, %edi
        movl %edx, %cr3

        xor %eax, %eax
        mov $4096, %ecx

        # rep stosd:
        # For ecx repetitions, stores the contents of eax into where edi points to, incrementing or decrementing edi
        rep stosl
        mov %edi, %cr3
        

        ###
        # Now that the page are clear we're going to set up the tables, the page tables are going to be located at these addresses:
        # PML4T - 0x1000
        # PDPT - 0x2000
        # PDT - 0x3000
        # PT - 0x4000
        movl $0x2003, %edi
        addl $0x1000, %edi
        movl $0x3003, %edi
        addl $0x1000, %edi
        movl $0x4003, %edi
        addl $0x1000, %edi # %edi points to first PT
        # All these are three since first two bits present + writeable

        mov $0x00000003, %ebx # present + writeable
        mov $512, %ecx # 512 * 1024 => 2MB which we identity map
        
        id_map_loop:
            movl %ebx, (%edi)
            addl $0x1000, %ebx
            addl $8, %edi
            loop id_map_loop
            # loop = dec ecx / jnz without flags


    long_final:
        # Enter long mode.
        movl 1<<5, %eax    # Set the PAE bit.
        movl %eax, %cr4
    
        # TODO: Enable PML5 by enabling CR4.LA57 bit

        movl $0xC0000080, %ecx               # Read from the EFER MSR. 
        rdmsr    

        orl $0x00000100, %eax                # Set the LME bit.
        wrmsr
    
        movl %cr0, %ebx                      # Activate long mode -
        orl $0x80000001, %ebx                 # - by enabling paging and protection simultaneously.
        movl %ebx, %cr0   
                    
        lgdt gdt_lm_descriptor           
    
        ljmp $CODE_SEG64, $stage3_start      # Load CS with 64 bit segment and flush the instruction cache
    

    long_mode_err:
        jmp .



### DATA
MSG_PROT_MODE:    .asciz "Successfully landed in 32-bit Protected Mode"
####

