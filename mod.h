#ifndef MOD_H
#define MOD_H

static uint32_t
mod(uint32_t ideal, uint32_t num)
{
	uint32_t	div, rest;
	__asm volatile (
		"udiv %0, %2, %3 \n\t"
		"mls %1, %0, %3, %2"
		: "=&r" (div), "=r" (rest)
		: "r" (num), "r" (ideal)
	);
	return (rest);
}

#endif /* MOD_H */
