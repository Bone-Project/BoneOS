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

linker_objects = ../../kernel/i386/kernel.o ../../boot/i386/boot.o \
  		  ../../screen/i386/putch/putch.o \
  		  ../../arch/i386/cpu/gdt/gdt_flush.o \
  		  ../../io/i386/io_asm.o \
  		  ../../screen/i386/putch/cls.o

objects = kernel/i386/kernel.o boot/i386/boot.o \
  		  screen/i386/putch/putch.o \
  		  arch/i386/cpu/gdt/gdt_flush.o \
  		  io/i386/io_asm.o \
  		   screen/i386/putch/cls.o

libraries = --start-group \
			 ../../cpu/i386/cpu.a \
 			 ../../libc/stdio/stdio.a \
 			 ../../libc/string/string.a \
 			 --end-group  

libraries_rm = cpu/i386/cpu.a \
 			 libc/stdio/stdio.a \
 			 libc/string/string.a 		 
  		  

export GCCPARAMS
export NASM_PARAMS
export objects
export LDPARAMS
export ARCH
export ARCH_FAMILY
export libraries
export linker_objects

q_c: compile BoneOS.bin BoneOS.iso qemu_compile

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

clean:
	rm -f $(objects)
	rm -f $(libraries_rm)

BoneOS.iso:
	cp BoneOS.bin boot/boot/BoneOS.bin	
	grub-mkrescue --output=BoneOS.iso boot

gdb_q:
	qemu-system-i386  -kernel  BoneOS.bin -display sdl -s -S	

qemu_compile:
	qemu-system-i386 -kernel BoneOS.bin -display sdl

bochs:
	bochs -f bochsrc.txt -q	

.PHONY: all, q_c , compile, BoneOS.bin, BoneOS.iso, c_compiler,gdb_q,qemu_compile,bochs 	