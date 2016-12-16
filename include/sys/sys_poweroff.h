#ifndef _SYS_REBOOT_H_
#define _SYS_REBOOT_H_

#define __len_poweroff_instance 1

typedef int(*poweroff_t)();

typedef struct{
    poweroff_t poweroff_v;
    const char* arch;
    const char* arch_family;
    bool active;
}__poweroff_t;

extern __poweroff_t __poweroff_i[];
extern int root_sys_poweroff(void);


#endif /*_SYS_REBOOT_H_*/