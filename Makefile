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

# Remember this the first time it is used
# so you don't have to keep specifying it
ifdef CROSSROOT
 $(shell echo $(CROSSROOT) > Makefile.cached.CROSSROOT)
else
 ifneq (,$(wildcard Makefile.cached.CROSSROOT))
  CROSSROOT := $(shell cat Makefile.cached.CROSSROOT)
 endif
endif

HOST_ENV = $(shell uname -p)
# Allow user to override cross-compiler directory
CROSSROOT ?= $(BUILDROOT)/cross
CC := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-gcc
LD := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ld
AR := $(CROSSROOT)/cross/$(HOST_ENV)/bin/i686-elf-ar
export CC
export LD
export AR

ARCH_FAMILY := x86
ARCH := i386
export ARCH
export ARCH_FAMILY

# Programs
BOCHS := bochs
QEMU := qemu-system-i386
PYTHON := python
VB := virtualbox
VBM := VBoxManage
GDB := gdb

# Architecture
ARCH_FAMILY_S = "x86"
ARCH_S="i386"


INCDIRS := $(BUILDROOT)/include \
    $(BUILDROOT)/arch/$(ARCH)  \
    $(BUILDROOT)/include/arch/$(ARCH) \
    $(BUILDROOT)/include/apps

# Parameters
LDPARAMS := -melf_i386
CFLAGS := \
	-O2 -g -Wall -Wextra -Wpedantic  -g \
	-Wno-unused-parameter -Wno-unused-but-set-parameter \
	-nostdlib -ffreestanding $(patsubst %,-I%,$(INCDIRS))

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
BONEOS_BOOT_DIR := boot
BONEOS_BOOT_BIN := $(BONEOS_BOOT_DIR)/$(BONEOS_BIN)
LINKER_SCRIPT := arch/i386/link/linker.ld

SCRIPT_CC := utils/cross_compiler/toolchain.py

libraries = \
	libc/libc.a \
	arch/$(ARCH)/libarch.a \
	apps/libapps.a
export libraries

# -----------------------------------------------
# Targets
# -----------------------------------------------

#
# Standard targets

all: iso

clean: clean-subdirs
	rm -f $(BONEOS_ISO)

.PHONY: all clean

#
# Build and clean subdirectories

$(libraries): subdirs

subdirs:
	(cd libc && $(MAKE))
	(cd arch && $(MAKE))
	(cd apps && $(MAKE))

clean-subdirs:
	(cd libc && $(MAKE) clean)
	(cd arch && $(MAKE) clean)

.PHONY: subdirs clean-subdirs

#
# Link

$(BONEOS_BIN): $(libraries) $(LINKER_SCRIPT)
	$(LD) $(LDPARAMS) \
	-T $(LINKER_SCRIPT) \
	-o $@ \
	--start-group $(libraries) --end-group

#
# Build ISO

$(BONEOS_BOOT_BIN): $(BONEOS_BIN)
	-rm -r boot
	mkdir -p boot/boot
	cp -R arch/$(ARCH)/boot/* boot/boot
	cp $(BONEOS_BIN) $(BONEOS_BOOT_BIN)

$(BONEOS_ISO): $(BONEOS_BOOT_BIN)
	grub-mkrescue --output=$(BONEOS_ISO) boot

iso: $(BONEOS_ISO)

#
# Get toolchain

$(COMPILER): get-toolchain

get-toolchain:
	$(PYTHON) utils/cross_compiler/toolchain.py

.PHONY: iso

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
	$(QEMU) -kernel $(BONEOS_BIN) -display sdl

qemu_iso : $(BONEOS_BIN) $(BONEOS_ISO)
	$(QEMU) -cdrom $(BONEOS_ISO)

bochs: $(BONEOS_ISO)
	$(BOCHS) -f bochsrc.bxrc -q

.PHONY: gdb_q qemu_compile bochs qemu_iso
