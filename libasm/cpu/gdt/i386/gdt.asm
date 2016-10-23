section .text
 global gdt_load
    gdt_load:
        lgdt[esp+4]
        mov ax,0x10
        mov ds,ax
        mov es,ax
        mov fs,ax
        mov gs,ax
        mov ss,ax
        jmp 0x08:flushcs
flushcs:
    ret