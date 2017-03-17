/**
 ** This file is part of BoneOS.
 **
 **   BoneOS is free software: you can redistribute it and/or modify
 **   it under the terms of the GNU General Public License as published by
 **   the Free Software Foundation, either version 3 of the License, or
 **   (at your option) any later version.

 **   BoneOS is distributed in the hope that it will be useful,
 **   but WITHOUT ANY WARRANTY; without even the implied warranty of
 **   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 **   GNU General Public License for more details.

 **   You should have received a copy of the GNU General Public License
 **   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
 **
 **  @main_author : Amanuel Bogale
 **
 **  @contributors:

 **     Amanuel Bogale <amanuel2> : start
 **/
 
 #include <stdint.h>
 #include <stddef.h>
 #include <stdbool.h>
 #include <io/io.h>
 #include <drv/pci/pci.h>
 #include <stdio/stdio.h>
 
 /**
  * Get adress to send to CONFIG_PORT
  * via I/O.
  */
  
 static inline uint32_t pci_get_address(uint32_t bus, uint32_t slot, uint32_t func, uint8_t offset)
 {
     return ( 
              (uint32_t) 
     
              ( 
                 (bus << 16) | (slot << 11) |
                 (func << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)
              ) 
            );
 }
 
 void write_config_address(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset)
 {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus; //long bus(32bit pad)
    uint32_t lslot = (uint32_t)slot; //^^ slot/device
    uint32_t lfunc = (uint32_t)func;//^^ function
    
    address = pci_get_address(lbus,lslot,lfunc,offset);
    outd(PORT_CONFIG_ADDRESS,address); //32bit I/O Stream
 }
 
 uint16_t read_data(uint8_t offset)
 {
    uint16_t tmp = 0; //init + declare
    tmp = (uint16_t) (ind(PORT_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff;
    return tmp;
 }
 
 uint16_t write_address_read_data(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset) 
 {
   write_config_address(bus,slot,func,offset);
   uint16_t tmp = read_data(offset);
   return tmp;
 }
 
 pci_descriptor_header00h_t get_descriptor(uint16_t bus, uint16_t device, uint16_t function)
 {
  
   //Set up PCI DESCRIPTOR
   pci_descriptor_header00h_t pdt;
   
   pdt.bus = bus;
   pdt.device = device;
   pdt.function = function;
   
   //OFFSET = Diffrent Info.
   /*
    OFFSET
    ------
    
    0x00 = Vendor ID 
    0x02 = Device ID
    0x0B = Class ID
    0x0A = SubClass ID
    0x09 = Interface ID
    
    0x08 = Revision
    0x3C = Interrupt
    */
    
                
    pdt.vendor_id    = write_address_read_data(bus,device,function,0x00);
    pdt.device_id    = write_address_read_data(bus,device,function,0x02);
    
    pdt.class_id     = write_address_read_data(bus,device,function,0x0B);
    pdt.subclass_id  = write_address_read_data(bus,device,function,0x0A);
   
    pdt.interface_id = write_address_read_data(bus,device,function,0x09);
   
    pdt.revision_id     = write_address_read_data(bus,device,function,0x08);
    pdt.interrupt    = write_address_read_data(bus,device,function,0x3C);
    
    pdt.cache_line_size = write_address_read_data(bus,device,function,0xF);
    
    return pdt;
 } 
 
bool device_has_func(uint16_t bus, uint16_t device)
{
 return write_address_read_data(bus,device,0,0x0E) & (1<<7);
}

 
void print_pci_devices()
{
 printk("----PCI DEVICES----\n");
 
  for(int bus=0; bus<8; bus++)
  {
    for(int device=0; device<32; device++)
    {
     
      int num_func = device_has_func(bus,device);
      
      for(int func=0; func<num_func; func++)
      {
       
        pci_descriptor_header00h_t pci_head = get_descriptor(bus,device,func);
        
        if(pci_head.vendor_id != 0xFFFF && pci_head.device_id != 0xFF)
        { 
          printk("VENDOR : 0x%x , DEVICE_ID: 0x%x \n" , pci_head.vendor_id, pci_head.device_id);
        }
         
        }
     
    }
  }
}