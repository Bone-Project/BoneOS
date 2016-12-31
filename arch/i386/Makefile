BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm \
	cpu/gdt/gdt-asm.asm \
	cpu/interrupts/irq.asm \
	cpu/interrupts/isr.asm \
	cpu/interrupts/interrupts-asm.asm 

CSRCS = \
	init/main.c \
	cpu/gdt/gdt.c \
	cpu/interrupts/interrupts.c \
	cpu/interrupts/pic.c \
	cpu/interrupts/idt.c \
	cpu/interrupts/irq.c \
	cpu/interrupts/isr.c \
	cpu/cpu.c \
	sys/sys_reboot.c \
	sys/sys_poweroff.c \
	mm/pmm.c

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/


LIBNAME := arch

include $(BUILDROOT)/library.mk
