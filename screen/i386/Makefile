all:
	i686-elf-gcc $(GCCPARAMS) -o putch/putch.o -c putch/putch.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o putch/cls.o -c putch/cls.c -I ../../ -ffreestanding 
	ar -cvq screen.a putch/putch.o putch/cls.o
