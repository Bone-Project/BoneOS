-include ../kconfig.mk

all:
	@echo "nothing to do for all"
boot:
	@echo "Starting boot process for  ..."
	@echo "Boot mode: $(CONFIG_BOOT_MODE)"
	@echo "Architecture: $(CONFIG_ARCH)"
ifeq ($(CONFIG_BOOT_MODE),UEFI)
ifeq ($(CONFIG_ARCH),riscv64)
	@echo "Building riscv64 UEFI boot..."
	# Add riscv64-specific commands here
else ifeq ($(CONFIG_ARCH),aarch64)
	@echo "Building aarch64 UEFI boot..."
	# Add aarch64-specific commands here
else ifeq ($(CONFIG_ARCH),x86_64)
	@echo "Building x86_64 UEFI boot..."
	cd uefi-os && cargo build --target x86_64-unknown-uefi && cd ..
else
	@echo "Unsupported architecture for UEFI boot: $(CONFIG_ARCH)"
	@exit 1
endif
	mkdir -p uefi-os/esp/efi/boot
	cp uefi-os/target/x86_64-unknown-uefi/debug/uefi-os.efi uefi-os/esp/efi/boot/bootx64.efi

else
	@echo "Non-UEFI boot mode selected: $(CONFIG_BOOT_MODE)"
	# Add commands for other boot modes here
endif


.PHONY: boot
