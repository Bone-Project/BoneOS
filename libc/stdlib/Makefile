all:
	i686-elf-gcc $(GCCPARAMS) -o panik/panik.o -c panik/panik.c -I ../../ -ffreestanding 
	ar -cvq stdlib.a panik/panik.o