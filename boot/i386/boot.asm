MAGIC equ 0x1badb002
FLAGS equ (1<<0 | 1<<1)
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
    dd MAGIC
    dd FLAGS
    dd CHECKSUM


section .text
extern kernelMain
extern callConstructors
global loader


loader:
    mov esp,kernel_stack
    call callConstructors
    push eax
    push ebx
    call kernelMain


_stop:
    cli
    hlt
    jmp _stop


section .bss
resb  2*1024*1024; # 2 MiB
kernel_stack:
