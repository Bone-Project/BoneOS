;
; This file is part of BoneOS.
;
;   BoneOS is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.

;   BoneOS is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.

;   You should have received a copy of the GNU General Public License
;   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
;
;  @main_author : Amanuel Bogale
;  
;  @contributors:

;   Amanuel Bogale <amanuel2> : start
;

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
    xor rbp,rbp
    add rbp,1
wait_debugger:
    test rbp,rbp
    jz wait_debugger

    mov rsp,kernel_stack
    call callConstructors
    mov rdi,rax
    mov rsi,rbx
    call kernelMain


_stop:
    cli
    hlt
    jmp _stop


section .bss
resb  2*1024*1024; # 2 MiB
kernel_stack:






