BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm

CSRCS = \
	init/main.c

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/


LIBNAME := arch

include $(BUILDROOT)/library.mk
