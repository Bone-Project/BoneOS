section .text 
    extern common_interrupt_exception_handler
    %macro  _isrm_code 1
        global isr%1
        isr%1 :
            cli
            push %1
            jmp isr_service
    %endmacro

    %macro _isrm_nocode 1
        global isr%1
        isr%1:
            cli
            push 0
            push %1
            jmp isr_service
    %endmacro


    isr_service :
        push eax
        push ecx
        push edx
        push ds
        call common_interrupt_exception_handler
        add esp,24
        iret

    
    _isrm_nocode 0
    _isrm_nocode 1
    _isrm_nocode 2
    _isrm_nocode 3
    _isrm_nocode 4
    _isrm_nocode 5
    _isrm_nocode 6
    _isrm_nocode 7
    _isrm_code 8
    _isrm_nocode 9
    _isrm_code 10
    _isrm_code 11
    _isrm_code 12
    _isrm_code 13
    _isrm_code 14
    _isrm_nocode 15
    _isrm_nocode 16
    _isrm_nocode 17
    _isrm_nocode 18
    _isrm_nocode 19
    _isrm_nocode 20
    _isrm_nocode 21
    _isrm_nocode 22
    _isrm_nocode 23
    _isrm_nocode 24
    _isrm_nocode 25
    _isrm_nocode 26
    _isrm_nocode 27
    _isrm_nocode 28
    _isrm_nocode 29
    _isrm_nocode 30
    _isrm_nocode 31