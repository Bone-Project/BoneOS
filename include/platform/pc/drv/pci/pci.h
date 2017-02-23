#ifndef _DRV_PCI_H_
#define _DRV_PCI_H_ 

//32 bit I/O Locations
#define CONFIG_ADDRESS 0xCF8
#define CONFIG_DATA    0xCFC

typedef struct
{
    
}pci_device_t;

extern uint32_t get_address(void);

#endif /*_DRV_PCI_H_*/