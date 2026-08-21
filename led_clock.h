#ifndef LED_CLOCK_H
#define LED_CLOCK_H

#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"

void reset_all(volatile struct ARRAYGND* array);
void dot(volatile struct ARRAYGND* array);
void dig0(volatile struct ARRAYGND* array);
void dig1(volatile struct ARRAYGND* array);
void dig2(volatile struct ARRAYGND* array);
void dig3(volatile struct ARRAYGND* array);
void dig4(volatile struct ARRAYGND* array);
void dig5(volatile struct ARRAYGND* array);
void dig6(volatile struct ARRAYGND* array);
void dig7(volatile struct ARRAYGND* array);
void dig8(volatile struct ARRAYGND* array);
void dig9(volatile struct ARRAYGND* array);

#define MASK_ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK_OFF(x, y) ( (x) |= (0x1 << (y)) )

void light_dig(volatile struct ARRAYGND* array, uint8_t num);
void turn_pin(volatile struct GPIO* port_electr, pins_num pin_electr_num , uint8_t state);

#endif
