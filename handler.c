extern unsigned int _la_data;
extern unsigned int _edata;
extern unsigned int _sdata;
extern unsigned int _ebss;
extern unsigned int _sbss;

extern int main(void);

void
handler(void)
{
	
	volatile unsigned int *src, *dst;
	src = &_la_data;
	dst = &_sdata;
	while(dst < &_edata) {
		*(dst++) = *(src++);
	}
	for(dst = &_sbss; dst < &_ebss; ++dst)
		*dst = 0;

	main();
}
