#include <stdint.h>

uint32_t 
__aeabi_uidiv(uint32_t numerator, uint32_t denominator) 
{
	uint32_t result;

	__asm volatile (
		"udiv %0, %1, %2"
		: "=r" (result)
		: "r" (numerator),
		  "r" (denominator)
	);

	return result;
}
