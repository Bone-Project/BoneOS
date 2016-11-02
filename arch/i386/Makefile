all:
	cd cpu;make
	ar -cvq arch.a cpu/gdt/gdt.o cpu/gdt/gdt_flush.o cpu/interrupts/idt.o cpu/interrupts/isr.o cpu/interrupts/interrupts_asm.o cpu/interrupts/interrupts.o cpu/interrupts/irq.o cpu/interrupts/pic.o