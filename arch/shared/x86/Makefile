BUILDROOT ?= ../../../

NSRC = cpu/interrupts/isr.asm \
	   cpu/interrupts/irq.asm
CSRCS = \
		misc/asm_util.c \
		cpu/interrupts/irq.c \
		cpu/interrupts/isr.c \
		sys/sys_reboot.c \
		sys/sys_poweroff.c 

LIBNAME := shared_arch

include $(BUILDROOT)/library.mk
