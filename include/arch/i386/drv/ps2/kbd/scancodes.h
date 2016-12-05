#ifndef _ARCH_CPU_DRV_KBD_SCANCODES_H_
#define _ARCH_CPU_DRV_KBD_SCANCODES_H_

struct
kbd_layout_t
{
    char* name;
    char* country;
    char const * scancode_shift;
    char const * scancode_no_shift;
};

#define QWERTY_USA_INDEX 0

extern struct kbd_layout_t *kbd_layouts[];
extern char const QWERTY_USA_NOSHIFT_VAL[];
extern char const QWERTY_USA_SHIFT_VAL[];

#endif /*_ARCH_CPU_DRV_KBD_SCANCODES_H_*/