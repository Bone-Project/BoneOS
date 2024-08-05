gdt_lm:
    # NULL descriptor
    .quad 0

    # Kernel Code Segment descriptor
    .word 0        # Limit (bits 0-15)
    .word 0        # Base (bits 0-15)
    .byte 0        # Base (bits 16-23)
    .byte 0x9a     # Access byte
    .byte 0x20     # Flags (4 bits) + Limit (bits 16-19)
    .byte 0        # Base (bits 24-31)

    # Kernel Data Segment descriptor
    .word 0        # Limit (bits 0-15)
    .word 0        # Base (bits 0-15)
    .byte 0        # Base (bits 16-23)
    .byte 0x92     # Access byte
    .byte 0        # Flags (4 bits) + Limit (bits 16-19)
    .byte 0        # Base (bits 24-31)

    # TSS descriptor (16 bytes)
    .word 0        # Limit (bits 0-15)
    .word 0        # Base (bits 0-15)
    .byte 0        # Base (bits 16-23)
    .byte 0x89     # Access byte (Present, Type = 64-bit TSS)
    .byte 0        # Flags (4 bits) + Limit (bits 16-19)
    .byte 0        # Base (bits 24-31)
    .long 0        # Base (bits 32-63)
    .long 0        # Reserved

gdt_lm_descriptor:
    // So, in total, this structure defines:
    // A 16-bit limit (size of the GDT minus 1)
    // A 64-bit base address of the GDT
    .word gdt_lm_descriptor - gdt_lm - 1  # Size of GDT
    .quad gdt_lm                         # Address of GDT

.equ CODE_SEG64, 0x08  # Offset of Kernel Code Segment in GDT
.equ DATA_SEG64, 0x10  # Offset of Kernel Data Segment in GDT