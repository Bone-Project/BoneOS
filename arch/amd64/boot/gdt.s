.code16

gdt:
    .word   0,0,0,0                         # NULL DESCRIPTOR
    .word   0xffff, 0x0000, 0x9a00, 0x00cf  # KERNEL CS
    .word   0xffff, 0x0000, 0x9200, 0x00cf  # KERNEL DS
    .word   0xffff, 0x0000, 0xfa00, 0x00cf  # USER CS
    .word   0xffff, 0x0000, 0xf200, 0x00cf  # USER DS
#    .word   0x0068, (tss - _start), 0x8901, 0x00cf  # TSS

# Hardware task switching is generally not used, but the TSS is still required.
# A single TSS is often used per CPU core, rather than per task.

gdt_descriptor:
    .word   gdt_descriptor - gdt    # Size of the GDT
    .long   gdt               # Address of the GDT