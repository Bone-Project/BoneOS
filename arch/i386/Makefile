BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm \
	cpu/gdt/gdt-asm.asm \
	cpu/interrupts/interrupts-asm.asm 

CSRCS = \
	init/main.c \
	cpu/gdt/gdt.c \
	cpu/interrupts/idt.c \
	cpu/cpu.c \
	cpu/interrupts/interrupts.c \
	mm/pmm.c \
	mm/pmm_util.c \
	mm/bitmap.c \
	cpu/cpuid.c \

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/


LIBNAME := arch

include $(BUILDROOT)/library.mk
