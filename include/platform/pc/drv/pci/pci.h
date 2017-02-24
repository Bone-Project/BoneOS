#ifndef _DRV_PCI_H_
#define _DRV_PCI_H_ 

//32 bit I/O Locations
#define PORT_CONFIG_ADDRESS 0xCF8
#define PORT_CONFIG_DATA    0xCFC

typedef struct
{
    uint32_t vendor_id;
    uint32_t class_id;
}pci_device_t;

extern uint32_t pci_get_address(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset);

#endif /*_DRV_PCI_H_*/