# INTERUPTS

# REFERENCE : https://www.logix.cz/michal/doc/i386/chp09-00.htm
# REFERENCE : https://en.wikipedia.org/wiki/Interrupt_descriptor_table

# INT_NUM    Event Type    Short Description
# 0x00    Processor Exception    Division by zero
# 0x01    Processor Exception    Single-step interrupt (see trap flag)
# 0x02    Processor Exception    NMI
# 0x03    Processor Exception    Breakpoint (which benefits from the shorter 0xCC encoding of INT 3)
# 0x04    Processor Exception    Overflow
# 0x05    Processor Exception    Bound Range Exceeded
# 0x06    Processor Exception    Invalid Opcode
# 0x07    Processor Exception    Coprocessor not available
# 0x08    Processor Exception    Double Fault
# 0x09    Processor Exception    Coprocessor Segment Overrun (386 or earlier only)
# 0x0A    Processor Exception    Invalid Task State Segment
# 0x0B    Processor Exception    Segment not present
# 0x0C    Processor Exception    Stack Segment Fault
# 0x0D    Processor Exception    General Protection Fault
# 0x0E    Processor Exception    Page Fault
# 0x0F    Processor Exception    reserved
# 0x10    Processor Exception    x87 Floating Point Exception
# 0x11    Processor Exception    Alignment Check
# 0x12    Processor Exception    Machine Check
# 0x13    Processor Exception    SIMD Floating-Point Exception
# 0x14    Processor Exception    Virtualization Exception
# 0x15    Processor Exception    Control Protection Exception (only available with CET)
# 0x16-0x1F    Processor Exception    reserved
# 0x20-0x27    Hardware Interrupt    IRQ 0-7
# 0x70-0x77    Hardware Interrupt    IRQ 8-15


intr00:
    pushl $0
    pushl $0
    jmp intr_handler

intr01:
    pushl $0
    pushl $1
    jmp intr_handler

intr02:
    pushl $0
    pushl $2
    jmp intr_handler

intr03:
    pushl $0
    pushl $3
    jmp intr_handler

intr04:
    pushl $0
    pushl $4
    jmp intr_handler

intr05:
    pushl $0
    pushl $5
    jmp intr_handler

intr06:
    pushl $0
    pushl $6
    jmp intr_handler

intr07:
    pushl $0
    pushl $7
    jmp intr_handler

intr08:
    pushl $8
    jmp intr_handler

intr09:
    pushl $0
    pushl $9
    jmp intr_handler

intr10:
    pushl $10
    jmp intr_handler

intr11:
    pushl $11
    jmp intr_handler

intr12:
    pushl $12
    jmp intr_handler

intr13:
    pushl $13
    jmp intr_handler

intr14:
    pushl $14
    jmp intr_handler

intr15:
    pushl $0
    pushl $15
    jmp intr_handler

intr16:
    pushl $0
    pushl $16
    jmp intr_handler

intr17:
    pushl $17
    jmp intr_handler

intr18:
    pushl $0
    pushl $18
    jmp intr_handler

intr19:
    pushl $0
    pushl $19
    jmp intr_handler

intr20:
    pushl $0
    pushl $20
    jmp intr_handler

intr21:
    pushl $0
    pushl $21
    jmp intr_handler

intr22:
    pushl $0
    pushl $22
    jmp intr_handler

intr23:
    pushl $0
    pushl $23
    jmp intr_handler

intr24:
    pushl $0
    pushl $24
    jmp intr_handler

intr25:
    pushl $0
    pushl $25
    jmp intr_handler

intr26:
    pushl $0
    pushl $26
    jmp intr_handler

intr27:
    pushl $0
    pushl $27
    jmp intr_handler

intr28:
    pushl $0
    pushl $28
    jmp intr_handler

intr29:
    pushl $0
    pushl $29
    jmp intr_handler

intr30:
    pushl $0
    pushl $30
    jmp intr_handler

intr31:
    pushl $0
    pushl $31
    jmp intr_handler

intr32:
    pushl $0
    pushl $32
    jmp intr_handler

intr33:
    pushl $0
    pushl $33
    jmp intr_handler

intr34:
    pushl $0
    pushl $34
    jmp intr_handler

intr35:
    pushl $0
    pushl $35
    jmp intr_handler

intr36:
    pushl $0
    pushl $36
    jmp intr_handler

intr37:
    pushl $0
    pushl $37
    jmp intr_handler

intr38:
    pushl $0
    pushl $38
    jmp intr_handler

intr39:
    pushl $0
    pushl $39
    jmp intr_handler

intr40:
    pushl $0
    pushl $40
    jmp intr_handler

intr41:
    pushl $0
    pushl $41
    jmp intr_handler

intr42:
    pushl $0
    pushl $42
    jmp intr_handler

intr43:
    pushl $0
    pushl $43
    jmp intr_handler

intr44:
    pushl $0
    pushl $44
    jmp intr_handler

intr45:
    pushl $0
    pushl $45
    jmp intr_handler

intr46:
    pushl $0
    pushl $46
    jmp intr_handler

intr47:
    pushl $0
    pushl $47
    jmp intr_handler