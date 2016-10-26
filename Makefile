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

GCCPARAMS =  -O2 -g -Wall -Wextra -Werror -Wpedantic -g \
			 -Wno-unused-parameter -Wno-unused-but-set-parameter \
			 -nostdlib

ARCH_FAMILY=x86
ARCH=i386	

ARCH_FAMILY_S = "x86"
ARCH_S="i386"	    
		    
NASM_PARAMS = -f elf32		    
LDPARAMS =  -melf_i386


i686 = i686-elf-	
VB=virtualbox
VBM=VBoxManage
SCRIPT_CC = utils/cross_compiler/toolchain.py

objects = ../../kernel/i386/kernel.o ../../boot/i386/boot.o \
  		  ../../screen/i386/putch/putch.o \
  		  ../../arch/i386/cpu/gdt/gdt_flush.o \
  		  ../../io/i386/io_asm.o

libraries = --start-group \
 			 ../../libc/stdio/stdio.a \
 			 --end-group  
  		  

export GCCPARAMS
export NASM_PARAMS
export objects
export LDPARAMS
export ARCH
export ARCH_FAMILY
export libraries

q_c: 
	make compile -B
	make BoneOS.bin -B
	make BoneOS.iso -B
	make qemu_compile -B

compile:
	cd boot;make
	cd io;make
	cd libc;make
	cd arch;make
	cd cpu;make
	cd screen;make
	cd kernel;make
BoneOS.bin:
	cd link;make	
c_compiler:
	python utils/cross_compiler/toolchain.py
BoneOS.iso:
	cp BoneOS.bin boot/boot/BoneOS.bin	
	grub-mkrescue --output=BoneOS.iso boot

gdb_q:
	qemu-system-i386  -kernel  BoneOS.bin -display sdl -s -S	

qemu_compile:
	qemu-system-i386 -kernel BoneOS.bin -display sdl