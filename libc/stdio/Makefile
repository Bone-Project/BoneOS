STDIO_SRC = 
all:
	i686-elf-gcc $(GCCPARAMS) -o itoa/itoa.o -c itoa/itoa.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o printk/printk.o -c printk/printk.c -I ../../ -ffreestanding 
	ar -cvq stdio.a itoa/itoa.o printk/printk.o