#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdint.h>

#define POWER32 (1UL << 31)
#define MAGIC_NUM(k) ( (POWER32 / (k)) + 1 )
#define DIV(k, n) ( (uint32_t)( ((uint64_t)(n) * MAGIC_NUM(k)) >> 31 ))
#define MOD(k, n) ((n) - (DIV(k, n) * (k)))

#define MASK_ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK_OFF(x, y) ( (x) |= (0x1 << (y)) )
uint32_t __aeabi_uidiv(uint32_t , uint32_t);

#endif
