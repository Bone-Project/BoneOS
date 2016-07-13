GCC_FLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra
gcc = i686-elf-gcc
as = i686-elf-as
bin_dir = bin/iso/boot/BoneOS.bin 
kernel_dir = bin/iso/kernel/kernel.o
bootstrapping_dir = bin/iso/boot_self/boot.o
iso_dir = bin/iso
iso = bin/BoneOS.iso
LINK_FLAGS = -ffreestanding -O2 -nostdlib linker/obj/boot.o linker/obj/kernel.o -lgcc
all: 
	cd toolchain/BoneOS-toolchain/ && . ./setenv.sh 
	rm -rf bin/iso/boot_self
	rm -rf bin/iso/kernel
	rm -rf linker/obj
	cd bin/iso && mkdir boot_self
	cd bin/iso && mkdir kernel
	cd linker && mkdir obj
	$(as) src/boot/boot.S -o $(bootstrapping_dir)
	cp $(bootstrapping_dir) linker/obj/boot.o
	$(gcc) -c src/kernel/kernel.c -o $(kernel_dir) $(GCC_FLAGS)
	cp $(kernel_dir) linker/obj/kernel.o
	$(gcc) -T linker/linker.ld -o $(bin_dir) $(LINK_FLAGS)
	grub-mkrescue -o $(iso) $(iso_dir)

clean:
	rm bin/iso/boot/boot.o
	rm bin/iso/kernel/kernel.o
	rm linker/obj/boot.o
	rm linker/obj/kernel.o
cd_rom:
	qemu-system-i386 -cdrom $(iso)

kernel_multiboot:
	qemu-system-i386 -kernel $(bin_dir)

test_hardware:
	sudo dd if=$(iso_dir) of=/dev/sdx && sync


