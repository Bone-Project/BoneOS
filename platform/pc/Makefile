BUILDROOT ?= ../..

NSRCS =

CSRCS = \
	drv/video/video.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_LOW).c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/utils.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/putch.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/clear.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/term_scroll.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/vga_textmode.c \
	drv/video/$(VIDEO_DRIVER)/$(VIDEO_DRIVER_MODE)/update_cursor.c \
	drv/pit/pit.c \
	drv/ps2/kbd/kbd.c \
	drv/driver.c \
	drv/ps2/kbd/scancodes.c \
	drv/ps2/kbd/kbd_layouts/scancodes_usa.c \
	drv/ps2/kbd/utils.c  \
	cpu/interrupts/pic.c \
	drv/cmos/rtc/rtc.c \
	io/io.c \
	drv/pcspkr/pcspkr.c


LIBNAME := platform

include $(BUILDROOT)/library.mk
