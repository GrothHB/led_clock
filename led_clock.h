
#include <stdint.h>
#include "basic_mapping.h"

void reset_all(struct ARRAYGND* array);
void dig0(struct ARRAYGND* array);
void dig1(struct ARRAYGND* array);
void dig2(struct ARRAYGND* array);
void dig3(struct ARRAYGND* array);
void dig4(struct ARRAYGND* array);
void dig5(struct ARRAYGND* array);
void dig6(struct ARRAYGND* array);
void dig7(struct ARRAYGND* array);
void dig8(struct ARRAYGND* array);
void dig9(struct ARRAYGND* array);

#define MASK_ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK_OFF(x, y) ( (x) |= (0x1 << (y)) )

void light_dig( struct GPIO* port_electr, uint8_t port_electr_num, 
		struct ARRAYGND* array, uint8_t num, uint8_t state )
