ENTRY(loader)
OUTPUT_FORMAT(elf64-x86-64)

KERNEL_VMA = 0x400000000000;
KERNEL_PMA = 0x100000;
 
SECTIONS
{
    . = KERNEL_VMA;

    .text . : AT(ADDR(.text) - KERNEL_VMA + KERNEL_PMA)
    {
        _code = .;
        *(.multiboot)
        *(.text)
        *(.rodata*)

        start_ctors = .;
        *(.init_array)
        *(SORT(.init_array.*));
        end_ctors = .;

        start_dtors = .;
        *(.fini_array)
        *(SORT(.fini_array.*));
        end_dtors = .;

        . = ALIGN(4096);
    }

   .data . : AT(ADDR(.data) - KERNEL_VMA + KERNEL_PMA)
   {
        _data = .;
        *(.data)
        . = ALIGN(4096);
   }

   .eh_frame . : AT(ADDR(.eh_frame) - KERNEL_VMA + KERNEL_PMA)
   {
        _ehframe = .;
        *(.eh_frame)
 
        . = ALIGN(4096);
   }

   .bss . : AT(ADDR(.bss) - KERNEL_VMA + KERNEL_PMA)
   {
       _bss = .;
       *(.bss)

       /*
        * You usually need to include generated COMMON symbols
        * under kernel BSS section or use gcc's -fno-common
        */

        *(COMMON)

        . = ALIGN(4096);
   }

   _end = .;

   /DISCARD/ :
   {
        *(.comment)
   }
}
