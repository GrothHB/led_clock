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
		*(.text.*)
	} > FLASH
	.rodata :
	{
		. = ALIGN(4); 	/* To make sure that addresses
				 * would be by 4 bytes
				 */
		*(.rodata*)
		. = ALIGN(4);
	} > FLASH
	_la_data = LOADADDR(.data);
	.data :
	{
		_sdata = .;
		*(.data*)
		_edata = .;
	} > SRAM AT > FLASH
	.bss :
	{
		_sbss = .;
		*(.bss)
		*(.bss.*)
		*(COMMON)
		_ebss = .;
	} > SRAM
}
