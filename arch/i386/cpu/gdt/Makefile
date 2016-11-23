all:
	i686-elf-gcc $(GCCPARAMS) -o gdt.o -c gdt.c -I ../../../../include -ffreestanding 
	nasm $(NASM_PARAMS) gdt.asm -o gdt_flush.o