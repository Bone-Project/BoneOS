#ifndef  _ARCH_DRV_DRIVER_H_
#define _ARCH_DRV_DRIVER_H_

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
  void(*init) (void);
  void(*uninit)(void);
}device_driver;

extern int init_device_driver(uint32_t index);
extern int uninit_device_driver(uint32_t index);
extern int uninit_all_drivers();
extern int init_all_drivers();

#endif /*_ARCH_DRV_DRIVER_H_*/