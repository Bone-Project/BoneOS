#ifndef _DRV_PCI_H_
#define _DRV_PCI_H_ 

//32 bit I/O Locations
#define PORT_CONFIG_ADDRESS 0xCF8
#define PORT_CONFIG_DATA    0xCFC

typedef struct
{
    uint32_t portBase;
    uint32_t interrupt;

    uint16_t bus;
    uint16_t device;
    uint16_t function;

    uint16_t vendor_id;
    uint16_t device_id;

    uint8_t class_id;
    uint8_t subclass_id;
    uint8_t interface_id;

    uint8_t revision_id; 
    
    uint8_t cache_line_size;
}pci_descriptor_header00h_t;

typedef struct
{
    uint16_t vendor_id;
    uint16_t device_id;
    uint16_t class_id;
    uint16_t subclass_id;
    
    uint16_t bus;
    uint16_t function;
    
    char* name;
    char* vendor; //If Specified
}pci_device_t;

typedef struct
{ 
   pci_device_t pci_device[200];
}multiple_pci_device_t;

extern void write_config_address(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset);
extern uint16_t read_data(uint8_t offset);
extern uint16_t check_vendor(uint8_t bus, uint8_t slot);
extern void print_pci_devices_enumeration_scheme();

#endif /*_DRV_PCI_H_*/

//00000000000000000000000011110101