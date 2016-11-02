all:
	i686-elf-gcc $(GCCPARAMS) -o idt.o -c idt.c -I ../../../../include -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o pic.o -c pic.c -I ../../../../include -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o isr.o -c isr.c -I ../../../../include -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o irq.o -c irq.c -I ../../../../include -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o interrupts.o -c interrupts.c -I ../../../../include -ffreestanding 
	nasm $(NASM_PARAMS) interrupts.asm -o interrupts_asm.o