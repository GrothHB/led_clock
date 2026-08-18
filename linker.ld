MEMORY
{
	SRAM(rwx) : ORIGIN = 0x20000000 , LENGTH = 128K
	FLASH(rx) : ORIGIN = 0x08000000 , LENGTH = 512K
}
new_stack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)
	} > FLASH
	_la_data = LOADADDR(.data);
	.data :
	{
		_sdata = .;
		*(.data)
		_edata = .;
		*(.bss)
		_ebss = .;
	} > SRAM AT > FLASH
}
