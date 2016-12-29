# Architecture

ARCH ?= i386

ifeq ($(ARCH),$(filter $(ARCH),i386 x86 80386 amd32))
 $(info x86 32 BIT Architecture Running)
 ARCH := i386
 ARCH_MACHINE := -m32
 ARCH_AS_FLAGS := --32
 ARCH_FAMILY := x86
 ARCH_FAMILY_S := "x86"
 ARCH_S := "i386"
 ARCH_QEMU := i386
 ARCH_LINKER := i386
else ifeq ($(ARCH),$(filter $(ARCH), amd64 x86_64 x86-64 emt64 x64))
 ARCH := amd64
 ARCH_MACHINE := -m64
 ARCH_AS_FLAGS := --64
 ARCH_FAMILY := x86
 ARCH_FAMILY_S := "x86"
 ARCH_S := "amd64"
 ARCH_QEMU := x86_64
 ARCH_LINKER := x86_64
else
 $(error SUPPORTED Architectures are {i386,amd32,80386,x86} , {amd64,x86_64,x86-64,x64,emt64}. Change via ./configure --arch=ARCH_NAME) 
endif

export ARCH
export ARCH_MACHINE
export ARCH_AS_FLAGS
export ARCH_S
export ARCH_FAMILY
export ARCH_FAMILY_S
export ARCH_LINKER

