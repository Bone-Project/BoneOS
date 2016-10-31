all:
	cd cpu;make
	ar -cvq arch.a cpu/gdt/gdt.o cpu/gdt/gdt_flush.o cpu/interrupts/idt.o cpu/interrupts/isr.o cpu/interrupts/isr_asm.o cpu/interrupts/interrupts.o