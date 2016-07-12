GCC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc = i686-elf-gcc
as = i686-elf-as
bin_dir = bin/iso/boot/BoneOS.bin 
iso_dir = bin/iso/boot/BoneOS.iso
LINK_FLAGS = -ffreestanding -O2 -nostdlib linker/obj/boot.o linker/obj/kernel.o -lgcc
all:
	$(as) src/bootstrapping/boot.S -o bin/iso/bootstrapping/boot.o
	cp bin/iso/bootstrapping/boot.o linker/obj
	$(gcc) -c src/kernel/kernel.c -o bin/iso/kernel/kernel.o $(GCC_FLAGS)
	cp bin/iso/kernel/kernel.o linker/obj
	$(gcc) -T linker/linker.ld -o $(bin_dir) $(LINK_FLAGS)
	grub-mkrescue -o $(iso_dir)
clean:
	rm bin/iso/bootstrapping/boot.o
	rm bin/iso/kernel/kernel.o
	rm linker/obj/boot.0
	rm linker/obj/kernel.0

