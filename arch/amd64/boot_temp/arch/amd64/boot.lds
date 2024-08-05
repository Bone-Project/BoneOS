OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)

SECTIONS
{
    . = 0x7C00;

    .boot : {
        *(.boot)
    }
}