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
 
 #include <stdargs.h>
 #include <stdint.h>
 #include <io/io.h>
 
 /**
  * Get adress to send to CONFIG_PORT
  * via I/O.
  */
  
 static inline uint32_t pci_get_address(uint32_t bus, uint32_t slot, uint32_t func, uint8_t offset)
 {
     return ( (uint32_t) 
     
              ((bus << 16) | (slot << 11) |
              (func << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)); 
            )
 }
 
 void write_config_address(uint8_t bus, uint8_t slot,uint8_t func, uint8_t offset)
 {
    uint32_t address;
    uint32_t lbus  = (uint32_t)bus; //long bus(32bit pad)
    uint32_t lslot = (uint32_t)slot; //^^ slot/device
    uint32_t lfunc = (uint32_t)func;//^^ function
    uint16_t tmp = 0;
    
    address = pci_get_address(lbus,lslot,lfunc,offset);
    outl(PORT_CONFIG_ADDRESS,address); //32bit I/O Stream
 }
 
 uint16_t read_data(uint8_t offset)
 {
    uint16_t tmp = 0; //init + declare
    tmp = (uint16_t) (inl(PORT_CONFIG_DATA) >> ((offset & 2) * 8)) & 0xffff);
    return tmp;
 }
 
 void get_descriptor(uint16_t bus, uint16_t device, uint16_t function)
 {
  
  //Set up PCI DESCRIPTOR
  pci_descriptor_t pdt;
  
  pdt.bus = bus;
  pdt.device = device;
  pdt.function = function;
  
  //OFFSET = Diffrent Info.
  pdt.vendor_id = read_data(bus,device,function,0x00);
  pci.device_id = read_data(bus,device,function,0x02);
  
 }