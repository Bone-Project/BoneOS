STDIO_SRC = 
all:
	i686-elf-gcc $(GCCPARAMS) -o itoa/itoa.o -c itoa/itoa.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o printf/printf.o -c printf/printf.c -I ../../ -ffreestanding 
	ar -cvq stdio.a itoa/itoa.o printf/printf.o