#ifndef _ARCH_CPU_DRV_KBD_SCANCODES_H_
#define _ARCH_CPU_DRV_KBD_SCANCODES_H_

struct
scancode_layout
{
    char* name;
    char const * scancode_shift;
    char const * scancode_no_shift;
};

#define QWERTY_EN_INDEX 0

extern struct scancode_layout *kbd_layouts[];

#endif /*_ARCH_CPU_DRV_KBD_SCANCODES_H_*/