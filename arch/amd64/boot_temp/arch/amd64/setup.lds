/* OUTPUT_FORMAT(binary) */
OUTPUT_FORMAT(elf32-i386)
ENTRY(_setup32)

SECTIONS
{
	. = 1M;

	.text : {
			*(.text)
	}

	.data : {
			*(.data)
	}

	.bss : {
			*(.bss)
	}

	/DISCARD/ : {
			*(.eh_frame)
			*(.comment)
	}

	_SETUP_END = .;
}