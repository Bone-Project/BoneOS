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
 
 uint32_t pci_get_address(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset)
 {
     return ( (uint32_t) 
     
              ((bus << 16) | (slot << 11) |
              (func << 8) | (offset & 0xfc) | ((uint32_t)0x80000000)); 
            )
 }