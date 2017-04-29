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
#include <stdarg.h>
#include <io/io.h>
#include <drv/serial/serialport.h>


/*
 * @function init_serial_port : 
 *   initalizes the serial port.
 */

void init_serial_port() {
    //Init I/O Procedures
    outb(COM_PORT1 + 1 , 0x00); //Disable Interrupts
    outb(COM_PORT1 + 3 , 0x80); //Enable Divisor Mode
    outb(COM_PORT1 + 0 , 0x03); //Set SerialPort to fire at 115200 bps. Be carefull to be same speed or less than computer can handle
    outb(COM_PORT1 + 1 , 0x00);
    outb(COM_PORT1 + 3 , 0x03);
    outb(COM_PORT1 + 2 , 0xC7);
    outb(COM_PORT1 + 4 , 0x0B);
}
