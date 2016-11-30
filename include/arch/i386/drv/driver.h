#ifndef  _ARCH_DRV_DRIVER_H_
#define _ARCH_DRV_DRIVER_H_

#include <stdbool.h>

/*
 * @struct device_driver:
 *      Prototype for a device
 *      driver. Used to initalize
 *      a driver, and unintalize 
 *      a driver. 
 */
struct  device_driver
{
  char* name;
  int(*init) (void);
  int(*uninit)(void);
  volatile bool initalized;
  char* version;
};

#define PIT_DRIVER_INDEX 0
#define KBD_DRIVER_INDEX 1
#define VIDEO_DRIVER_INDEX 2

extern void setup_driver_handler();
extern int init_device_driver(uint32_t index);
extern int uninit_device_driver(uint32_t index);
extern int uninit_all_drivers();
extern int init_all_drivers();
extern bool device_initalized(int index);

extern struct device_driver *drivers[];

#endif /*_ARCH_DRV_DRIVER_H_*/