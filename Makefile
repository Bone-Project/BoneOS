#  This file is part of BoneOS.
 
#    BoneOS is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.

#    BoneOS is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.

#    You should have received a copy of the GNU General Public License
#    along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.

GCCPARAMS =  -O2 -g -Wall -Wextra -Werror \
			 -Wno-unused-parameter

ARCH_FAMILY=x86
ARCH=i386	

ARCH_FAMILY_S = "x86"
ARCH_S="i386"	    
		    
NASM_PARAMS = -f elf32		    
LDPARAMS =  -melf_i386


i686 = i686-elf-	
VB=virtualbox
VBM=VBoxManage
SCRIPT_CC = scripts/cross_compiler/toolchain.py

objects = ../../main/i386/kernel.o ../../boot/i386/boot.o \
  		  ../../libc/i386/stdio/printf/printf.o \
  		  ../../libc/i386/stdio/putchar/putchar.o \
  		  ../../libc/i386/stdio/itoa/itoa.o
  		  

export GCCPARAMS
export NASM_PARAMS
export objects
export LDPARAMS
export ARCH
export ARCH_FAMILY

q_c: 
	make compile -B
	make BoneOS.bin -B
	make BoneOS.iso -B
	make qemu_compile -B

compile:
	cd boot;make
	cd libc;make
	cd main;make
BoneOS.bin:
	cd linkage;make	
c_compiler:
	python scripts/cross_compiler/toolchain.py
BoneOS.iso:
	cp BoneOS.bin boot/boot/BoneOS.bin	
	grub-mkrescue --output=BoneOS.iso boot

gdb_q:
	qemu-system-i386  -kernel  BoneOS.bin -display sdl -s -S	

qemu_compile:
	qemu-system-i386 -kernel BoneOS.bin -display sdl