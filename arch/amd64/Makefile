BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm \
	cpu/interrupts/interrupts-asm.asm

CSRCS = \
	init/main.c \
	cpu/cpu.c \
	cpu/interrupts/idt.c \
	cpu/interrupts/interrupts.c \
	cpu/gdt/gdt.c \
	cpu/cpuid.c \

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/


LIBNAME := arch

include $(BUILDROOT)/library.mk
