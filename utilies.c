#include <stdint.h>

#define POWER32 (1UL << 32)
#define MAGIC_NUM(k) ( POWER32 / (k) )
#define DIV(k, n) ( (uint32_t)( ((uint64_t)(n) * MAGIC_NUM(k)) >> 32 ))
#define MOD(k, n) ((n) - (DIV(k, n) * (k)))

