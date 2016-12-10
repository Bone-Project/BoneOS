BUILDROOT ?= ../..

NSRCS = \
	boot/boot.asm \
	io/io.asm \
	cpu/gdt/gdt-asm.asm \
	cpu/interrupts/irq.asm \
	cpu/interrupts/isr.asm \
	cpu/interrupts/interrupts-asm.asm \
	io/io.asm

CSRCS = \
	init/main.c \
	cpu/gdt/gdt.c \
	cpu/interrupts/interrupts.c \
	cpu/interrupts/pic.c \
	cpu/interrupts/idt.c \
	cpu/interrupts/irq.c \
	cpu/interrupts/isr.c \
	cpu/cpu.c \
	drv/video/video.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_LOW).c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/$(VIDEO_DRIVER_RES)/utils.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/$(VIDEO_DRIVER_RES)/putch/putch.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/$(VIDEO_DRIVER_RES)/clear.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/$(VIDEO_DRIVER_RES)/term_scroll.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/vga_textmode.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/update_cursor.c \
	drv/pit/pit.c \
	drv/ps2/kbd/kbd.c \
	drv/driver.c \
	drv/ps2/kbd/scancodes.c \
	drv/ps2/kbd/kbd_layouts/scancodes_usa.c \
	drv/ps2/kbd/utils.c 

cpu/interrupts/interrupts-asm.o: NASMFLAGS += -i cpu/interrupts/


LIBNAME := arch

include $(BUILDROOT)/library.mk
