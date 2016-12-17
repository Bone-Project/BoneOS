# Architecture
ARCH := i386

ifeq ($(ARCH), i386)
	ARCH_FAMILY := x86
	ARCH_FAMILY_S := "x86"
	ARCH_S := "i386"
	ARCH_QEMU := i386
	ARCH_LINKER := i386
else ifeq ($(ARCH), amd32)
	ARCH := x86
	ARCH_FAMILY := x86
	ARCH_FAMILY_S := "x86"
	ARCH_S := "i386"
	ARCH_QEMU := i386
	ARCH_LINKER := i386
 else ifeq ($(ARCH), 80836)
	ARCH := x86
	ARCH_FAMILY := x86
	ARCH_FAMILY_S := "x86"
	ARCH_S := "i386"
	ARCH_QEMU := i386
	ARCH_LINKER := i386	
else ifeq ($(ARCH),amd64)
	ARCH_FAMILY := x86
	ARCH_FAMILY_S := "x86"
	ARCH_S := "amd64"
	ARCH_QEMU := x86_64
	ARCH_LINKER := x86_64
else ifeq ($(ARCH),x86_64)
        ARCH:= amd64
	ARCH_FAMILY := x86
	ARCH_FAMILY_S := "x86"
	ARCH_S := "amd64"
	ARCH_QEMU := x86_64
	ARCH_LINKER := x86_64	
 else
 	echo "SUPPORTED Architectures are {i386,amd32,80836} , {amd64, x86_64}"
 	sleep 2
 	exit
endif

