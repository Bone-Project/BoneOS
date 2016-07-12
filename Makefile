GCC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc = i686-elf-gcc
as = i686-elf-as
bin_dir = bin/iso/boot/BoneOS.bin 
iso_dir = bin/iso/boot/BoneOS.iso
iso = BoneOS.iso
LINK_FLAGS = -ffreestanding -O2 -nostdlib linker/obj/boot.o linker/obj/kernel.o -lgcc
all: 
	cd toolchain/barebones-toolchain/ && . ./setenv.sh 
	$(as) src/bootstrapping/boot.S -o bin/iso/bootstrapping/boot.o
	cp bin/iso/bootstrapping/boot.o linker/obj
	$(gcc) -c src/kernel/kernel.c -o bin/iso/kernel/kernel.o $(GCC_FLAGS)
	cp bin/iso/kernel/kernel.o linker/obj
	$(gcc) -T linker/linker.ld -o $(bin_dir) $(LINK_FLAGS)
	grub-mkrescue -o $(iso) $(isodir)

clean:
	rm bin/iso/bootstrapping/boot.o
	rm bin/iso/kernel/kernel.o
	rm linker/obj/boot.o
	rm linker/obj/kernel.o
cd_rom:
	qemu-system-i386 -cdrom $(iso)

kernel_multiboot:
	qemu-system-i386 -kernel $(bin_dir)

test_hardware:
	sudo dd if=$(iso_dir) of=/dev/sdx && sync
