all:
	i686-elf-gcc $(GCCPARAMS) -o memset/memset.o -c memset/memset.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o strlen/strlen.o -c strlen/strlen.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o strcpy/strcpy.o -c strcpy/strcpy.c -I ../../ -ffreestanding 
	i686-elf-gcc $(GCCPARAMS) -o strchr/strchr.o -c strchr/strchr.c -I ../../ -ffreestanding 
	ar -cvq string.a memset/memset.o strlen/strlen.o strcpy/strcpy.o strchr/strchr.o
