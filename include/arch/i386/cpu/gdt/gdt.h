#ifndef _ARCH_CPU_GDT_H_
#define _ARCH_CPU_GDT_H_

/*
 * @struct SegmentDescriptor:
 *     Descriptor to each segments
 *     such as the code segments,
 *     data segments and NULL segments
 *
 */

struct SegmentDescriptor{ 
    uint16_t limit_low; 
    uint16_t base_low; 
    uint8_t base_middle; 
    uint8_t access;
    uint8_t flags_limit_high; 
    uint8_t base_high;
};

/*
 * @struct gdt_ptr
 *     The GDT Pointer that
 *     gets loaded as the final  
 *     result. Contains limit
 *     of GDT , and the base  
 *     address of GDT
 */

struct gdt_ptr
{
    uint16_t limit;
    uintptr_t base;
}__attribute__((packed)) gp;

extern void gdt_load(struct gdt_ptr gp);

#define GDT_MAKE_SEGMENT_DESCRIPTOR(base, \
            limit, \
            present, \
            privilege, \
            executable, \
            downward, \
            rw, \
            granularity, \
            is32, \
            is64) \
{ \
    ((limit) & 0xFFFF), \
    ((base) & 0xFFFF), \
    (((base) >> 16) & 0xFF), \
    ( \
        ((present) ? 1 << 7 : 0) | \
        (((privilege) & 0x03) << 5) | \
        (1 << 4) | \
        ((executable) ? 1 << 3 : 0) | \
        ((downward) ? 1 << 2 : 0) | \
        ((rw) ? 1 << 1 : 0) \
    ), \
    ( \
        ((granularity) ? 1 << 7 : 0) | \
        ((is32) ? 1 << 6 : 0) | \
         ((is64) ? 1 << 5 : 0)| \
        (((limit) >> 16) & 0x0F) \
    ), \
    (((base) >> 24) & 0xFF) \
}

#define GDT_MAKE_EMPTY() \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0, 0, 0, 0, 0, 0, 0,0, 0)

#define GDT_MAKE_CODESEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 1, 0, 1, 1, 1,1)

#define GDT_MAKE_DATASEG(ring) \
    GDT_MAKE_SEGMENT_DESCRIPTOR(0, 0xFFFFF, 1, ring, 0, 0, 1, 1, 1,0)


extern void init_gdt();

#endif /*_ARCH_CPU_GDT_H_*/






