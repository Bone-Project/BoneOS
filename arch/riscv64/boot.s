.section .text.init
.global _start

_start:
    # Set up stack pointer
    li sp, 0x80100000

    # Jump to Rust code
    call kernel_main

    # If we return, just spin
spin:
    j spin
