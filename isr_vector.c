extern unsigned int new_stack;
extern void handler(void);
extern void change_diod(void);
__attribute__((section(".isr_vector")))
void* vector[] =
{
	[0] = &new_stack,
	[1] = &handler, 
	[26] = &change_diod
};
