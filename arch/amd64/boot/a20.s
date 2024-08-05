.code16

_a20:
    call _has_a20
    testw %ax, %ax
    jnz .done 

    // movw $a20_trying_bios, %si
    // call puts16
    // call _enable_a20_bios
    // call _has_a20
    // testw %ax, %ax
    // jnz .done

    // movw $a20_trying_keyb, %si
    // call puts16
    // call _enable_a20_kbd
    // call _has_a20
    // testw %ax, %ax
    // jnz .done

    // movw $a20_trying_io92, %si
    // call puts16
    call _enable_a20_io
    call _has_a20
    testw %ax, %ax
    jnz .done

    // movw $a20_cant, %si
    // call puts16
    jmp .

.done:
    // movw $a20_enabled_message, %si
    // call puts16
    ret

_has_a20:
    pushf
    push %ds
    push %es
    push %di
    push %si
    cli

    xorw %ax, %ax
    movw %ax, %es

    notw %ax
    movw %ax, %ds
    movw $0x0500, %di
    movw $0x0510, %si

    # save two seg:off addresses
    movb %es:(%di), %al
    pushw %ax
    movb %ds:(%si), %al
    pushw %ax

    # try to overwrite to 0xFFFF+0510 which would be
    # above the 1MB boundary 0x100000(1MB)
    # normally wraps around if a20 disabled else actually writes (soc check [es:di])
    movb $0x00, %es:(%di)
    movb $0xFF, %ds:(%si)
    cmpb $0xFF, %es:(%di)
    
    movw $0, %ax
    je .nah
    movw $1, %ax

.nah:
    popw %ax
    movb %al, %ds:(%si)
    popw %ax
    movb %al, %es:(%di)
    pop %si
    pop %di
    pop %es
    pop %ds
    popf
    ret


# --- bios service
// _disable_a20:
//     movw $0x2400, %ax
//     int $0x15
//     ret


# ------ all of the strats to enable the a20 line (IBM sucks)


# -- first up bios
# https://wiki.osdev.org/A20_Line
// _enable_a20_bios:
//     # int 0x15, ax = 0x2401
//     # 0(fail)

//     movw $0x2403, %ax
//     int $0x15
//     jb .nah2                 # jump if CF set (aka not supp)
//     cmpb $0, %ah
//     jnz .nah2

//     movw $0x2402, %ax       # checking if yah this time
//     int $0x15
//     jb .nah2
//     cmpb $1, %al
//     jnz .yah

//     movw $0x2401, %ax       # why downward, devs are weird
//     int $0x15
//     jb .nah2
//     cmpb $0, %ah
//     jnz .nah2

// .yah:
//     movw $1, %ax
//     ret
// .nah2:
//     movw $0, %ax
//     ret

# --- second way kbd (8042 MC)
# -- lots of wait cause I/O is slow af
// _enable_a20_kbd:
//     cli
//     call _wait_io1

//     # disable kbd CMD(0xAD)
//     movb $0xAD, %al 
//     outb %al, $0x64
//     call _wait_io1

//     # read input CMD(0xD0)
//     movb $0xD0, %al
//     outb %al, $0x64
//     call _wait_io2
//     inb $0x60, %al
//     pushl %eax
//     call _wait_io1

//     # write to output CMD(0xD1)
//     movb $0xD1, %al
//     outb %al, $0x64
//     call _wait_io1
//     popl %eax
//     orb $2, %al             # make sure second bit set (corresponds to enable A20 line) + saving prev state(pop eax)
//     outb %al, $0x60
//     call _wait_io1

//     # enable kbd again CMD(0xAE)
//     movb $0xAE, %al
//     outb %al, $0x64
//     call _wait_io1

//     sti
//     ret

// _wait_io1:
//     inb $0x64, %al
//     testb $2, %al
//     jnz _wait_io1 
//     ret
// _wait_io2:
//     inb $0x64, %al
//     testb $1, %al
//     jz _wait_io2
//     ret

# --- third way use port 0x92
# -- bit layout
# - bit 0 = 1(fast reset (used to switch back to real mode; for MCA this took 13.4 ms).)
# - bit 1 = 1(enable a20)
# - bit 2 = see manufacturer manual
# - bit 3 =  power-on password bytes (stored in CMOS bytes 0x38-0x3f or 0x36-0x3f) 1=accessiable
# - bit 4-5 = Manufacturer manual
# - bit 6 = HDD/SSD/Any drive connected to SATA interface Acitvity light. (Most say HDD but they mean this...)

_enable_a20_io:
    inb $0x92, %al
    testb $2, %al           # bit 1
    jnz .donezo
    
    orb $2, %al
    andb $0xFE, %al         # no fast reset (most machine typically go through ACPI proccess)
    outb %al, $0x92

.donezo:
    ret



################# DATA

// a20_enabled_message: .asciz "A20 is enabled."
// a20_disabled_message: .asciz "A20 is disabled."
// a20_trying_bios: .asciz "Trying to enable A20 using BIOS..."
// a20_trying_keyb: .asciz "Trying to enable A20 using Keyboard Controller..."
// a20_trying_io92: .asciz "Trying to enable A20 using IO port 92..."
// a20_cant: .asciz "Cannot enable A20"

#################
