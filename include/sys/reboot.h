#ifndef _SYS_REBOOT_H_
#define _SYS_REBOOT_H_

#define __len_reboot_instance 1

typedef int(*reboot_t)();

typedef struct{
    reboot_t reboot_v;
    const char* arch;
    const char* arch_family;
    bool active;
}__reboot_s;

extern __reboot_s __reboot_i[];

#endif /*_SYS_REBOOT_H_*/