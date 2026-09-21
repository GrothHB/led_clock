#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>

/* #define POWER32 (1UL << 31)
 * #define MAGIC_NUM(k) ( POWER32 / (k) )
 * #define DIV(k, n) ( (uint32_t)( ((uint64_t)(n) * MAGIC_NUM(k)) >> 32 ))
 * #define MOD(k, n) ((n) - (DIV(k, n) * (k)))
 * #define MOD(k, n) ((n) & ((k) - 1))
 */

#define MASK_ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK_OFF(x, y) ( (x) |= (0x1 << (y)) )
uint32_t 		__aeabi_uidiv(uint32_t , uint32_t);

#endif
