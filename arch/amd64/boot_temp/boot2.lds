/* OUTPUT_FORMAT(binary) */
OUTPUT_FORMAT(elf32-i386)
ENTRY(_setup32)

SECTIONS
{
	. = 0x8000;

  .boot2 :
  {
      *(.boot2)
  }

	/DISCARD/ : {
		*(.comment*)
	}

	_SETUP_END = .;
}