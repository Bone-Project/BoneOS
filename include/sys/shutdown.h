#ifndef _SYS_REBOOT_H_
#define _SYS_REBOOT_H_

#define __len_shutdown_instance 1

typedef int(*shutdown_t)();

typedef struct{
    shutdown_t shutdown_v;
    const char* arch;
    const char* arch_family;
    bool active;
}__shutdown_t;

extern __shutdown_t __shutdown_i[];

#endif /*_SYS_REBOOT_H_*/