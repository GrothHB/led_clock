extern unsigned int _la_data;
extern unsigned int _la_bss;
extern unsigned int _edata;
extern unsigned int _sdata;
extern unsigned int _ebss;

int main(void);

void handler(void)
{
	volatile unsigned int *src, *dst;
	src = &_la_data;
	dst = &_sdata;
	while(dst < &_edata) {
		*dst = *src;
		++src;
		++dst;
	}
	while(dst < &_ebss) {
		*dst = 0;
		++dst;
	}
	main();
}
