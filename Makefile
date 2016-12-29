#  This file is part of BoneOS.
 
#    BoneOS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    BoneOS is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.

# Subdirectory makes need to know this directory
BUILDROOT := $(realpath .)
export BUILDROOT

include config/ARCH.mk
include config/PLAT.mk
GENERATED_CONFIG := config/GENERATED-CONFIG.mk
ifndef GENCONFIG
 -include $(GENERATED_CONFIG)
 # Detect path to libgcc
 LIBGCC := $(shell $(CC) $(ARCH_MACHINE) -print-libgcc-file-name)
 LIBGCCDIR := $(dir $(LIBGCC))
 LIBGCCFILENAME := $(notdir $(LIBGCC))
 LIBGCCNAME := $(patsubst lib%.a,%,$(LIBGCCFILENAME))
endif


# Remember this the first time it is used
# so you don't have to keep specifying it
ifdef CROSSROOT
 $(shell echo $(CROSSROOT) > Makefile.cached.CROSSROOT)
else
 ifneq (,$(wildcard Makefile.cached.CROSSROOT))
  CROSSROOT := $(shell cat Makefile.cached.CROSSROOT)
 endif
endif

ifdef CROSSROOT
  HOST_ENV = $(shell uname -p)
  # Allow user to override cross-compiler directory
  CROSSROOT ?= $(BUILDROOT)/cross
  CC := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-gcc
  LD := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ld
  AR := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ar
  export CC
  export LD
  export AR
endif



VIDEO_DRIVER := VGA
VIDEO_DRIVER_LOW := vga
VIDEO_DRIVER_MODE := textmode
VIDEO_DRIVER_RES_W := 80
VIDEO_DRIVER_RES_H := 25
VIDEO_DRIVER_RES := $(VIDEO_DRIVER_RES_W)x$(VIDEO_DRIVER_RES_H)
export VIDEO_DRIVER
export VIDEO_DRIVER_LOW
export VIDEO_DRIVER_RES_W
export VIDEO_DRIVER_RES_H
export VIDEO_DRIVER_RES
export VIDEO_DRIVER_MODE

# Programs
BOCHS := bochs
QEMU := qemu-system-$(ARCH_QEMU)
PYTHON := python
SH := sh
VB := virtualbox
VBM := VBoxManage
GDB := gdb_q



INCDIRS := $(BUILDROOT)/include \
    $(BUILDROOT)/arch/$(ARCH)  \
    $(BUILDROOT)/include/arch/$(ARCH) \
    $(BUILDROOT)/include/apps \
    $(BUILDROOT)/include/bin \
    $(BUILDROOT)/include/sbin \
    $(BUILDROOT)/include/libc \
    $(BUILDROOT)/include/platform/$(PLAT) \
    $(BUILDROOT)/include/libc/string \
    $(BUILDROOT)/include/arch/shared/x86 \

# Parameters
LDPARAMS := -melf_$(ARCH_LINKER) --build-id=none
CFLAGS := \
	$(ARCH_MACHINE) -std=c11 \
	-O0 -g -Wall -Wextra -Wpedantic -Werror  -g \
	-Wno-error=missing-field-initializers \
	-nostdlib -ffreestanding $(patsubst %,-I%,$(INCDIRS))

ASFLAGS := $(ARCH_AS_FLAGS)

NASM ?= nasm
NASMFLAGS := -f elf32

export CFLAGS
export LDFLAGS
export CFLAGS
export NASM
export NASMFLAGS

# Paths
BONEOS_ISO := BoneOS.iso
BONEOS_BIN := BoneOS.bin
BONEOS_BOOT_DIR := boot/boot
BONEOS_BOOT_BIN := $(BONEOS_BOOT_DIR)/$(BONEOS_BIN)
BONEOS_GRUB_CFG := $(BONEOS_BOOT_DIR)/grub/grub.cfg
LINKER_SCRIPT := arch/$(ARCH)/link/linker.ld

SCRIPT_CC := utils/cross_compiler/toolchain.py

libraries = \
	libc/libc.a \
	arch/$(ARCH)/libarch.a \
	apps/libapps.a \
	bin/libbin.a \
	sbin/libsbin.a \
	arch/shared/$(ARCH_FAMILY)/libshared_arch.a \
	platform/$(PLAT)/libplatform.a
export libraries

# -----------------------------------------------
# Targets
# -----------------------------------------------

#
# Standard targets

all: iso

clean: clean-subdirs
	rm -f $(BONEOS_ISO)
	rm -rf iso

.PHONY: all clean

#
# Build and clean subdirectories

$(libraries): subdirs

subdirs:
	(cd libc && $(MAKE))
	(cd arch && $(MAKE))
	(cd apps && $(MAKE))
	(cd bin  && $(MAKE))
	(cd sbin && $(MAKE))
	(cd platform && $(MAKE))

clean-subdirs:
	(cd libc && $(MAKE) clean)
	(cd arch && $(MAKE) clean)
	(cd apps && $(MAKE) clean)
	(cd bin  && $(MAKE) clean)
	(cd sbin && $(MAKE) clean)
	(cd platform && $(MAKE) clean)

.PHONY: subdirs clean-subdirs

#
# Link

$(BONEOS_BIN): $(libraries) $(LINKER_SCRIPT)
	$(LD) $(LDPARAMS) \
	-T $(LINKER_SCRIPT) \
	-o $@ \
	--start-group $(libraries) --end-group \
	-L$(LIBGCCDIR) -l$(LIBGCCNAME)

#
# Build ISO

$(BONEOS_BOOT_BIN): $(BONEOS_BIN)
	mkdir -p $(dir $(BONEOS_BOOT_BIN))
	cp $(BONEOS_BIN) $(BONEOS_BOOT_BIN)

$(BONEOS_ISO): $(BONEOS_BOOT_BIN)
	cp BoneOS.bin boot/boot/BoneOS.bin
	grub-mkrescue --output=BoneOS.iso boot

iso: $(BONEOS_ISO)

#
# Get toolchain

$(COMPILER): get-toolchain

get-toolchain:
	$(PYTHON) utils/cross_compiler/toolchain.py

.PHONY: iso

no_vnc:
	$(SH) utils/novnc/install.sh
	$(SH) utils/novnc/run.sh

.PHONY: no_vnc

#
# Launch and debug

gdb_q: $(BONEOS_BIN)
	$(QEMU) -kernel $(BONEOS_BIN) -display sdl -s -S

debug_q:
	$(GDB) --symbols=$(BONEOS_BIN) --tui \
		-iex 'set architecture i386:x86-64' \
		-ex 'target remote localhost:1234' \
		-ex 'layout regs' \
		-ex 'set radix 16' \

qemu_compile: $(BONEOS_BIN)
	$(QEMU) -kernel $(BONEOS_BIN) -display sdl -k en-us -s

qemu_iso: $(BONEOS_BIN) $(BONEOS_ISO)
	$(QEMU) -cdrom $(BONEOS_ISO) -k en-us -s

bochs: $(BONEOS_ISO)
	$(BOCHS) -f bochsrc.bxrc -q

new_line:
	find . \( -name "*.asm" -o -name "*.h" -o -name "*.c" \) -print0 | \
		xargs -0 -iFILE sh -c 'echo >> FILE'

custom:
	xterm -fg white -bg black
	unset TMUX

distclean: clean
	rm -f $(GENERATED_CONFIG)

configure-help:
	@echo ''
	@echo 'Usage: configure [options]'
	@echo 'Options: [defaults in brackets after descriptions]'
	@echo ''
	@echo '--cc=CC             use C compiler [$(CC)]'
	@echo '--arch=ARCH         compile kernel that runs on ARCH'
	@echo '                    Available ARCH: x86, x86-64'
	@echo '--plat=PLAT         compile kernel that is of platform PLAT'
	@echo '                    Available PLAT: pc'
	@echo ''

configure-set:
	@echo '# This file is automatically generated' > $(GENERATED_CONFIG)
	@echo '# Invoke the configure script to make changes' >> $(GENERATED_CONFIG)
	@echo "CC := $(CC)" >> $(GENERATED_CONFIG)
	@echo "ARCH := $(ARCH)" >> $(GENERATED_CONFIG)
	@echo "PLAT := $(PLAT)" >> $(GENERATED_CONFIG)
	@echo "export CC" >> $(GENERATED_CONFIG)
	@echo "export ARCH" >> $(GENERATED_CONFIG)
	@echo "export PLAT" >> $(GENERATED_CONFIG)
	@echo '' >> $(GENERATED_CONFIG)

.PHONY: gdb_q qemu_compile bochs qemu_iso custom new_line distclean configure-help configure-set