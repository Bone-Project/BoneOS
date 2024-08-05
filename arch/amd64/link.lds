ENTRY(_start)
PROVIDE(kernel_start = 0xffffffff80000000);

SECTIONS
{
    /* The bootloader starts at 0x7C00 */
    . = 0x7C00;

    .boot :
    {
        *(.boot)
    }

    /* Kernel is loaded at 1MB */
    . = 1M;

    .text :
    {
        *(.text .text.*)
        . = ALIGN(4K);
    }

    .rodata :
    {
        *(.rodata .rodata.*)
        . = ALIGN(4K);
    }

    .data :
    {
        *(.data .data.*)
        . = ALIGN(4K);
    }

    .bss :
    {
        *(.bss .bss.*)
        *(COMMON)
        . = ALIGN(4K);
    }

    /* Kernel is mapped to this virtual address */
    . = 0xffffffff80000000;

    /* reason for AT(ADDR's) */
    /* The kernel is physically loaded at a lower address (around 1MB). */
    /* But it needs to run at a high virtual address (0xffffffff80000000). */
    .text.kernel : AT(ADDR(.text))
    {
        _kernel_start = .;
        *(.text .text.*)
        . = ALIGN(4K);
    }

    .rodata.kernel : AT(ADDR(.rodata))
    {
        *(.rodata .rodata.*)
        . = ALIGN(4K);
    }

    .data.kernel : AT(ADDR(.data))
    {
        *(.data .data.*)
        . = ALIGN(4K);
    }

    .bss.kernel : AT(ADDR(.bss))
    {
        *(.bss .bss.*)
        *(COMMON) /* Due to fortran... */
        . = ALIGN(4K);
        _kernel_end = .;
    }

    /DISCARD/ :
    {
        *(.eh_frame)
        *(.comment)
    }
}