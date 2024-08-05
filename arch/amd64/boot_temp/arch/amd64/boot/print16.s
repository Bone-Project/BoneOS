.code16
# were in real mode we can just utilize BIOS

putc16:
    push %ax
    push %bx
    mov $14, %ah
    mov $0, %bh
    int $0x10
    pop %bx
    pop %ax
    ret

puts16:
    # Code  Mnemonic    Description
    # AC    LODS m8     Load byte at address DS:(E)SI into AL
    # AD    LODS m16    Load word at address DS:(E)SI into AX
    # AD    LODS m32    Load doubleword at address DS:(E)SI into EAX
    # AC    LODSB       Load byte at address DS:(E)SI into AL and inc SI
    # AD    LODSW       Load word at address DS:(E)SI into AX
    # AD    LODSD       Load doubleword at address DS:(E)SI into EAX
    lahf
    lodsb
    test %al, %al # null term
    jz .done_puts
    call putc16
    jmp puts16
    .done_puts:
        sahf
        ret

