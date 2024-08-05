.set GDTEntry_limitl, 0
.set GDTEntry_basel, 2
.set GDTEntry_basem, 4
.set GDTEntry_attribute, 5
.set GDTEntry_flags__limith, 6
.set GDTEntry_baseh, 7
.set GDTEntry_size, 8

.set gdt_attr_present, 1 << 7
.set gdt_attr_ring1, 1 << 5
.set gdt_attr_ring2, 1 << 6
.set gdt_attr_ring3, (1 << 5) | (1 << 6)
.set gdt_attr_user, 1 << 4
.set gdt_attr_code, 1 << 3
.set gdt_attr_conforming, 1 << 2
.set gdt_attr_readable, 1 << 1
.set gdt_attr_expand_down, 1 << 2
.set gdt_attr_writable, 1 << 1
.set gdt_attr_accessed, 1 << 0

.set gdt_attr_tssAvailabe16, 0x1
.set gdt_attr_ldt, 0x2
.set gdt_attr_tssBusy16, 0x3
.set gdt_attr_call16, 0x4
.set gdt_attr_task, 0x5
.set gdt_attr_interrupt16, 0x6
.set gdt_attr_trap16, 0x7
.set gdt_attr_tssAvailabe32, 0x9
.set gdt_attr_tssBusy32, 0xB
.set gdt_attr_call32, 0xC
.set gdt_attr_interrupt32, 0xE
.set gdt_attr_trap32, 0xF
.set gdt_attr_ldt32, 0x2
.set gdt_attr_tssAvailabe64, 0x9
.set gdt_attr_tssBusy64, 0xB
.set gdt_attr_call64, 0xC
.set gdt_attr_interrupt64, 0xE
.set gdt_attr_trap64, 0xF

.set gdt_flag_granularity, 1 << 7
.set gdt_flag_available, 1 << 4
.set gdt_flag_default_operand_size, 1 << 6
.set gdt_flag_long_mode, 1 << 5
.set gdt_flag_reserved, 1 << 5

gdtr:
    .word gdt_end - gdt - 1  # size
    .quad gdt                # offset

gdt:
.set gdt_null, . - gdt
    .quad 0

.set gdt_lm64_code, . - gdt
    .word 0                  # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_code # attribute
    .byte gdt_flag_long_mode # flags__limith
    .byte 0                  # baseh

.set gdt_lm64_data, . - gdt
    .word 0                  # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_writable # attribute
    .byte 0                  # flags__limith
    .byte 0                  # baseh

.set gdt_pm32_code, . - gdt
    .word 0xFFFF             # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_code | gdt_attr_readable # attribute
    .byte 0xF | gdt_flag_granularity | gdt_flag_default_operand_size # flags__limith
    .byte 0                  # baseh

.set gdt_pm32_data, . - gdt
    .word 0xFFFF             # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_writable # attribute
    .byte 0xF | gdt_flag_granularity | gdt_flag_default_operand_size # flags__limith
    .byte 0                  # baseh

.set gdt_pm16_code, . - gdt
    .word 0xFFFF             # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_code | gdt_attr_readable # attribute
    .byte 0xF                # flags__limith
    .byte 0                  # baseh

.set gdt_pm16_data, . - gdt
    .word 0xFFFF             # limitl
    .word 0                  # basel
    .byte 0                  # basem
    .byte gdt_attr_present | gdt_attr_user | gdt_attr_writable # attribute
    .byte 0xF                # flags__limith
    .byte 0                  # baseh

gdt_end: