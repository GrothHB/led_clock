#ifndef LED_CLOCK_H
#define LED_CLOCK_H

#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"

void reset_all(struct ARRAYGND* array);
void dot(struct ARRAYGND* array);
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

void light_dig(struct ARRAYGND* array, uint8_t num);
void turn_pin(struct GPIO* port_electr, pins_num pin_electr_num , uint8_t state);

#endif
