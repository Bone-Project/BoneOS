gdt_pm:
    # NULL descriptor
    .word 0, 0
    .byte 0, 0, 0, 0

    # Kernel Code Segment descriptor
    .word 0xffff    # Limit (bits 0-15)
    .word 0x0000    # Base (bits 0-15)
    .byte 0x00      # Base (bits 16-23)
    .byte 0x9a      # Access byte
    .byte 0xcf      # Flags (4 bits) + Limit (bits 16-19)
    .byte 0x00      # Base (bits 24-31)

    # Kernel Data Segment descriptor
    .word 0xffff    # Limit (bits 0-15)
    .word 0x0000    # Base (bits 0-15)
    .byte 0x00      # Base (bits 16-23)
    .byte 0x92      # Access byte
    .byte 0xcf      # Flags (4 bits) + Limit (bits 16-19)
    .byte 0x00      # Base (bits 24-31)

gdt_pm_descriptor:
    .word gdt_pm_descriptor - gdt_pm - 1  # Size of GDT
    .long 0  # Address of GDT (to be filled at runtime)

.equ CODE_SEG32, 0x08  # Offset of Kernel Code Segment in GDT
.equ DATA_SEG32, 0x10  # Offset of Kernel Data Segment in GDT