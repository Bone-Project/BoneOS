BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm \
	io/io.asm \
	cpu/gdt/gdt-asm.asm \
	cpu/interrupts/irq.asm \
	cpu/interrupts/isr.asm \
	cpu/interrupts/interrupts-asm.asm \
	io/io.asm \
	boot/boot.asm

CSRCS = \
	kernel/kernel.c \
	cpu/gdt/gdt.c \
	cpu/interrupts/interrupts.c \
	cpu/interrupts/pic.c \
	cpu/interrupts/idt.c \
	cpu/interrupts/irq.c \
	screen/VGA/textmode/putch/putch.c \
	screen/VGA/textmode/putch/cls.c \
	misc/asm_util.c \
	drv/pit/pit.c \
	drv/kbd/kbd.c

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/

#cpu/interrupts/isr.c \

LIBNAME := arch

include $(BUILDROOT)/library.mk
