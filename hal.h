#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"
#include "utilites.h"

void set_power_port(uint8_t port, uint8_t state, volatile struct GPIO** gpio);
void set_moder(volatile struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_otyper(volatile struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_pupdr(volatile struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_systick(uint32_t time);
void set_interr(uint8_t port_name, pins_num pin_num);
void switches_port(volatile struct GPIO* reg, pins_num pin_num, uint8_t state);
void halt_interr(uint8_t state, pins_num pin_num);

#endif
