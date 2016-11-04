all:
	i686-elf-gcc $(GCCPARAMS) -o VGA/textmode/putch/putch.o -c VGA/textmode/putch/putch.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o VGA/textmode/putch/cls.o -c VGA/textmode/putch/cls.c -I ../../ -ffreestanding 
	ar -cvq screen.a VGA/textmode/putch/putch.o VGA/textmode/putch/cls.o
