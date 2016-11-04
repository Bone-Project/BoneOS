all:
	i686-elf-gcc $(GCCPARAMS) -o pit/pit.o -c pit/pit.c -I ../../include -ffreestanding 
	ar -cvq drv.a pit/pit.o