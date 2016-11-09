all:
	i686-elf-gcc $(GCCPARAMS) -o sleep/sleep.o -c sleep/sleep.c -I ../../ -ffreestanding 
	ar -cvq unistd.a sleep/sleep.o
