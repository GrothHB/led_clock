extern unsigned int 	new_stack;
extern void 		handler(void);
extern void 		buttons_interr(void);
extern void 		systick_interr(void);
extern void 		trap(void);
typedef void		(*isr)(void);
__attribute__((section(".isr_vector")))
isr vector[] =
{
	[0] = (isr)(unsigned int)&new_stack,
	[1] = handler, 
	[2] = trap,
	[3] = trap,
	[4] = trap,
	[5] = trap,
	[6] = trap,
	[15] = systick_interr,
	[39] = buttons_interr
};
