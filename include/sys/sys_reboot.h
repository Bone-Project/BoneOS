#ifndef _SYS_REBOOT_H_
#define _SYS_REBOOT_H_

#define __len_reboot_instance 1

typedef int(*reboot_t)();

typedef struct{
    reboot_t reboot_v;
    const char* arch;
    const char* arch_family;
    bool active;
}__reboot_t;

extern __reboot_t __reboot_i[];
extern int root_sys_reboot(void);

#endif /*_SYS_REBOOT_H_*/