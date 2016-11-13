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

section .text
    
    extern interupt_handler

    %macro  interupt_m_code 1
        global int%1
        int%1 :
            cli
            push %1
            jmp int_service
    %endmacro

    %macro interupt_m_nocode 1
        global int%1
        int%1:
            cli
            push 0
            push %1
            jmp int_service
    %endmacro



    int_service :
        push eax
        push ecx
        push edx
        push ds
        push esp
        call interupt_handler
        pop eax
        pop ds
        pop edx
        pop ecx
        pop eax
        add esp,8
        iret

    %include "isr.asm"
    %include "irq.asm"