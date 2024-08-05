.code16
mydisk_load:
    cmpw $127, %cx
    jbe check_extension

    pusha
    movw $127, %cx
    call mydisk_load
    popa
    
    addl $127, %eax
    addw $4064, %dx # 127*512/16
    subw $127, %cx
    jmp mydisk_load
    


check_extension:
    // clc

    pusha
    pushf
    # Check for INT 13h extensions support
    movb $0x41, %ah
    movw $0x55AA, %bx
    movb $0x80, %dl  # drive number
    int $0x13
    jc disk_error
    cmpw $0xAA55, %bx
    jne disk_error
    popf
    popa


#     - %ax: Segment of buffer to write to
#     - %bx: Lower 32 bit of starting LBA
#     - %cx: Number of sectors to read
load_dap:
    movw $load_dap_msg, %si
    call puts16

    movw %bx, DAP_LBA_lower
    movw %cx, DAP_num_sectors

    lea DAP, %si

    movw %ax, DAP_buf_segment

    movb $0x80, %dl 
    movb $0x42, %ah

    int $0x13
    jc disk_error


after_int:
    lea disk_suc_msg, %si
    call puts16
    ret
  
disk_error:
    lea disk_err_msg, %si
    call puts16
    jmp .

#### DATA

// .align 2
DAP:
#*******************************************************************************#
# Disk Address Packet                                                           #
#-------------------------------------------------------------------------------#
# Offset  Size   Description                                                    #
#   0       1    size of packet (16 bytes)                                      #
#   1       1    always 0                                                       #
#   2       2    number of sectors to load (max = 127 on some BIOS)             #
#   4       2    16-bit offset of target buffer                                 #
#   4       2    16-bit segment of target buffer                                #
#   8       4    lower 32 bits of 48-bit starting LBA                           #   
#  12       4    upper 32 bits of 48-bit starting LBA                           #
#*******************************************************************************#
    DAP_size:        .byte 0x10 # size of packet = 16 bytes
    DAP_reserved:    .byte 0
    DAP_num_sectors: .short 1 # gets reset to number of sectors read
    DAP_buf_offset:  .short 0 # 16 bit offset target
    DAP_buf_segment: .short 0 # 16 bit segent target
    DAP_LBA_lower:   .long 1 # lower 32 bit 48bit LBA
    DAP_LBA_upper:   .long 0 # upper 32 bit 48bit LBA

.byte 0
disk_tmp: .byte 0x80
disk_err_msg: .asciz "disk err..\n"
load_dap_msg: .asciz "load dapping...\n"
disk_suc_msg: .asciz "sector loaded...\n"
#### DATA