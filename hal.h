#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"
#include "utilites.h"

void set_power_port(uint8_t port, uint8_t state, struct GPIO* gpio);
void set_moder(struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_otyper(struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_pupdr(struct GPIO* reg, pinconf IO_purp, pins_num pin_num);
void set_systick(uint32_t time);
void set_interr(uint8_t port_name, pins_num pin_num, uint8_t state);
void switches_port(struct GPIO* reg, pins_num pin_num, uint8_t state);
void halt_interr(uint8_t state, pins_num pin_num);

#endif
