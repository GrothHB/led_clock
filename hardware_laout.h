#include "symbols.h"
#include "basic_mapping.h"
#include "hal.h"

void set_all(volatile struct GPIO* ptr, volatile struct GPIO* ptr2);
void set_arraygnd(volatile struct ARRAYGND* ptr, volatile struct GPIO* fst, volatile struct GPIO* snd);
void set_all_interr(void);
void set_power_pins(volatile struct ARRAYELECT* ptr, volatile struct GPIO* gpioa, volatile struct GPIO* gpiob);
