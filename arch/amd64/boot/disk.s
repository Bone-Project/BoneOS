.code16
mydisk_load:
    pusha
    # Load CD descriptor at sector 17
    movw $0x1000, %bx  # KERNEL_OFFSET
    movw $0xf00, %ax
    movw %ax, %es
    movw $17, %cx      # DescriptorSector
    call load_sector
    jc disk_error

    # Get boot catalog sector offset
    movw %es:0x1047, %bx
    
    # Load boot catalog sector
    movw $0x1000, %dx  # KERNEL_OFFSET
    movw $0xf00, %ax
    movw %ax, %es
    movw %bx, %cx      # BootCatalogSector
    call load_sector
    jc disk_error
    
    # Read disk sector offset
    movw %es:0x1028, %bx
    # Get sector below, which is where the kernel is located
    addw $1, %bx
    
    # Load disk sector 
    movw $0x1000, %dx  # KERNEL_OFFSET
    movw $0xf00, %ax
    movw %ax, %es
    movw $155, %di     # Number of sectors to transfer
    call load_multiple_sectors
    jc disk_error

    popa
    ret

disk_error:
    jmp .

# Function to load a single sector
# Input: 
#   %bx: offset
#   %es: segment
#   %cx: sector number
load_sector:
    pusha
    movb $0x42, %ah
    movb $0x10, %al    # Packet size
    movw $0x0001, %di  # Number of sectors to transfer
    movw %sp, %si      # Use stack for temporary storage
    pushw %di          # Number of sectors
    pushw %bx          # Offset
    pushw %es          # Segment
    push %cx           # Sector number
    pushw $0           # Upper 32-bits of 48-bit LBA
    movw %sp, %si      # Pointer to the disk address packet
    int $0x13
    addw $10, %sp      # Clean up stack
    popa
    ret

# Function to load multiple sectors
# Input:
#   %bx: offset
#   %es: segment
#   %cx: starting sector number
#   %di: number of sectors to transfer
load_multiple_sectors:
    pusha
    movb $0x42, %ah
    movb $0x10, %al    # Packet size
    movw %sp, %si      # Use stack for temporary storage
    pushw %di          # Number of sectors
    pushw %bx          # Offset
    pushw %es          # Segment
    push %cx           # Sector number
    pushw $0           # Upper 32-bits of 48-bit LBA
    movw %sp, %si      # Pointer to the disk address packet
    int $0x13
    addw $10, %sp      # Clean up stack
    popa
    ret

#### DATA
.equ BootCatalogSectorOffset, 0x47
.equ BootLoaderOffset, 0x28
.equ KERNEL_OFFSET, 0x1000

// DISK_ERROR_MSG:     .asciz "Disk read error!"
// DISK_SUCCESS_MSG:   .asciz "Disk read success!"

// DiskAddressPacket:        
// DiskSize:           .byte 0x10
// DiskZero:           .byte 0
// DiskTransfers:      .word 155
// DiskOffset:         .word KERNEL_OFFSET
// DiskSegment:        .word 0xf00
// DiskSector:         .long 0
// DiskUpper:          .long 0

// DescriptorAddressPacket:        
// DescriptorSize:         .byte 0x10
// DescriptorZero:         .byte 0
// DescriptorTransfers:    .word 1
// DescriptorOffset:       .word KERNEL_OFFSET
// DescriptorSegment:      .word 0xf00
// DescriptorSector:       .long 17
// DescriptorUpper:        .long 0

// BootCatalogAddressPacket:        
// BootCatalogPacketSize:  .byte 0x10
// BootCatalogZero:        .byte 0
// BootCatalogTransfers:   .word 1
// BootCatalogOffset:      .word KERNEL_OFFSET
// BootCatalogSegment:     .word 0xf00
// BootCatalogSector:      .long 0
// BootCatalogUpper:       .long 0

#### DATA
