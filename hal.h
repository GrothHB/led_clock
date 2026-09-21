#ifndef HAL_H
#define HAL_H

#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"
#include "utilites.h"

void		set_power_port(uint8_t, uint8_t, volatile struct GPIO **);
void		set_moder(volatile struct GPIO *, enum pinconf, enum pin_num);
void		set_otyper(volatile struct GPIO *, enum pinconf, enum pin_num);
void		set_pupdr(volatile struct GPIO *, enum pinconf, enum pin_num);
void		set_systick(uint32_t);
void		set_interr(uint8_t, enum pin_num);
void		switches_port(volatile struct GPIO *, enum pin_num, uint8_t);
void		halt_interr(uint8_t, enum pin_num);

#endif
