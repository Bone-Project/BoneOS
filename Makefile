-include ../kconfig.mk

ARCH := $(CONFIG_ARCH)
BOOT := $(CONFIG_BOOT_MODE)
VENDOR ?= 
LOG ?=
STATS ?= off
PORT ?= 2333

### CLANG ROUTE
CC := clang
BOOT_CC_FLAGS := -target i386-none-elf -m16 -g -fno-pic -fno-pie 
BOOT_LD_FLAGS := -m elf_i386 
CC_FLAGS := -target x86_64-none-elf -mcmodel=kernel -g -fno-pic -fno-pie
KERNEL_LD_FLAGS := -n -m elf_x86_64
AS := $(CC) -c
LD := ld.lld
OBJCOPY := llvm-objcopy

#### ZIG ROUTE
#CC := zig cc
#CC_FLAGS := -target x86_64-freestanding -mcmodel=kernel -g
#AS := $(CC) -c
#LD := $(CC)
#OBJCOPY := llvm-objcopy

### ISO
ISODIR := iso
BOOTDIR := boot
BOOTPATH := $(ISODIR)/$(BOOTDIR)
BOOT := boot
SETUP := setup
BOOTBIN := $(BOOT).bin
SETUPBIN := $(SETUP).bin
LOADERISO := $(BOOT).iso

BOOTIMG := $(BOOTDIR)/$(BOOTBIN)


# do not support debug mode
MODE := debug

export MODE
export LOG
export ARCH
export VENDOR
export STATS

-include kconfig.mk


features := $(ARCH)

ifeq ($(STATS), on)
  features += --features stats
endif

build_args := --features "$(features)" --target arch/$(ARCH)/setup.json -Z build-std=core,alloc -Z build-std-features=compiler-builtins-mem

ifeq ($(MODE), release)
  build_args += --release
endif

all: build
run: qemu-$(CONFIG_BOOT_MODE)-$(CONFIG_ARCH)
debug: debug-$(ARCH)

setup:
	rm -f boot.lds setup.lds kernel.lds
	cp arch/$(ARCH)/boot.lds .
	cp arch/$(ARCH)/setup.lds .

	rm -rf $(ISODIR)
	mkdir -p $(BOOTPATH)
	# cp src/kernel.lds .

build: setup
    #cargo clean
    
	cd arch/$(ARCH)/boot && $(AS) $(BOOT_CC_FLAGS) -o ../../../boot.o boot.s && cd ../../
	#cd arch/$(ARCH)/boot && $(CC) $(BOOT_CC_FLAGS) -ffreestanding -c -o ../../../test.o test.c && cd ../../
	$(LD) $(BOOT_LD_FLAGS) -Ttext 0 boot.o -o boot.elf  -nostdlib
	$(OBJCOPY) -O binary boot.elf boot.bin

	cd arch/$(ARCH)/boot && $(AS) $(BOOT_CC_FLAGS) -o ../../../setup.o setup.s && cd ../../
	$(LD) $(BOOT_LD_FLAGS) -Ttext 0x10000 setup.o -o setup.elf -nostdlib
	$(OBJCOPY) -O binary setup.elf $(SETUPBIN)

	# ARCH=$(ARCH) cargo build $(build_args)

	# $(LD) $(KERNEL_LD_FLAGS) -T kernel.lds -o kernel.elf target/setup/$(MODE)/libamanlib.a
	# $(OBJCOPY) -O binary kernel.elf kernel.bin

  # Combine boot sector and kernel
	cat boot.bin setup.bin > os.img
	#cp $(BOOTBIN) $(BOOTPATH)
	#cp $(SETUPBIN) $(BOOTPATH)
	#genisoimage -R -b $(BOOTIMG) -no-emul-boot -boot-load-size 4 -boot-info-table -V CR0S -v -o $(LOADERISO) $(ISODIR)
	#grub-mkrescue -o boot.iso $(ISODIR)


check_boot:
	# ld -n -T arch/$(ARCH)/link.lds -o boot.elf boot.o
	# objcopy -O binary boot.elf boot.bin 
	xxd -l 512 boot.bin

uefi_boot:
	cd arch; make boot; cd ../

menuconfig:
	@$(MAKE) -f scripts/Makefile $@

qemu-UEFI-x86_64:
	qemu-system-x86_64 -enable-kvm \
    -drive if=pflash,format=raw,readonly=on,file=arch/amd64/OVMF_CODE.fd \
    -drive if=pflash,format=raw,readonly=on,file=arch/amd64/OVMF_VARS.fd \
	-drive format=raw,file=fat:rw:arch/uefi-os/esp \
    -device virtio-rng-pci -vga std

qemu-riscv64:
	qemu-system-aarch64 \
    -M virt \
    -m 1024M \
    -cpu rv64 \
    -nographic \
    -machine virtualization=on \
    -kernel target/setup/release/armv8-baremetal-demo-rust

qemu-aarch64:
	qemu-system-aarch64 \
    -M virt \
    -m 1024M \
    -cpu cortex-a53 \
    -nographic \
    -machine virtualization=on \
    -kernel target/setup/release/armv8-baremetal-demo-rust

debug-aarch64:
	qemu-system-aarch64 \
    -M virt \
    -m 1024M \
    -cpu cortex-a53 \
    -nographic \
    -machine virtualization=on \
    -kernel target/setup/release/armv8-baremetal-demo-rust \
    -S -s

clean:
	cd arch/uefi-os && cargo clean && cd ../..
