all:
	i686-elf-gcc $(GCCPARAMS) -o gdt/gdt.o -c gdt/gdt.c -I ../../include -ffreestanding 
	ar -cvq cpu.a gdt/gdt.o