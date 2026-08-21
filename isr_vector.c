extern unsigned int new_stack;
extern void handler(void);
extern void buttons_interr(void);
extern void systick_interr(void);
__attribute__((section(".isr_vector")))
void* vector[] =
{
	[0] = &new_stack,
	[1] = &handler, 
	[15] = &systick_interr,
	[39] = &buttons_interr
};
