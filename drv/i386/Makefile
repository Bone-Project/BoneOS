all:
	i686-elf-gcc $(GCCPARAMS) -o pit/pit.o -c pit/pit.c -I ../../include -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o kbd/kbd.o -c kbd/kbd.c -I ../../include -ffreestanding 
	ar -cvq drv.a pit/pit.o kbd/kbd.o