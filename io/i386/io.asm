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