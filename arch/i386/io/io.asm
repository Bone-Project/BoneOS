;
; This file is part of BoneOS.
;
;   BoneOS is free software: you can redistribute it and/or modify
;   it under the terms of the GNU General Public License as published by
;   the Free Software Foundation, either version 3 of the License, or
;   (at your option) any later version.

;   BoneOS is distributed in the hope that it will be useful,
;   but WITHOUT ANY WARRANTY; without even the implied warranty of
;   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;   GNU General Public License for more details.

;   You should have received a copy of the GNU General Public License
;   along with BoneOS.  If not, see <http://www.gnu.org/licenses/>.
;
;  @main_author : Amanuel Bogale
;  
;  @contributors:

;   Amanuel Bogale <amanuel2> : start
;

section .text
  global inb8
  global outb8
  global inb16
  global outb16
  global inb32
  global outb32

	inb8:
		mov edx,[esp+4]
		in al,dx
		ret

	outb8:
		mov edx,[esp+4]
		mov al,[esp+4+4]
		out dx,al
		ret

	inb16:
		mov edx,[esp+4]
		in ax,dx
		ret

	outb16:
		mov edx,[esp+4]
		mov ax,[esp+4+4]
		out dx,ax
		ret

	inb32:
		mov edx,[esp+4]
		in eax,dx
		ret

	outb32:
		mov edx,[esp+4]
		mov eax,[esp+4+4]
		out dx,eax
		ret