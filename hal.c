#include <stdint.h>
#include "basic_mapping.h"
#include "symbols.h"
#include "utilites.h"
#include "mod.h"
#include "hal.h"

void
set_power_port(uint8_t port, uint8_t state, volatile struct GPIO **gpio)
{
	uint8_t off_set = port - (uint8_t)'A';
	if(state && off_set <= 5) {
		RCC->AHB1ENR |= (1 << off_set);
		*gpio = (volatile struct GPIO*)(0x40020000 + (0x400 * off_set));
	}
	else 
	if(off_set <= 5)
		RCC->AHB1ENR &= ~(1 << off_set);
}

void
set_moder(volatile struct GPIO *reg, enum pinconf IO_purp, enum pin_num pin_num)
{
	uint8_t new_pin_num = pin_num << 1;
	reg->MODER = reg->MODER & ~((1 << (new_pin_num + 1)) | (1 << new_pin_num) );
	if(IO_purp == GENERAL)
		reg->MODER |= (1 << new_pin_num);
	else
	if(IO_purp == ALT_FUN)
		reg->MODER |= (1 << (new_pin_num + 1));
	else
	if(IO_purp == ANALOG)
		reg->MODER |= (1 << (new_pin_num + 1)) | (1 << new_pin_num);
}

void
set_otyper(volatile struct GPIO *reg, enum pinconf IO_purp, enum pin_num pin_num)
{
	if(IO_purp == PUSH_PULL)
		reg->OTYPER &= ~(1 << pin_num);
	else
		reg->OTYPER |= (1 << pin_num);
}

void
set_pupdr(volatile struct GPIO *reg, enum pinconf IO_purp, enum pin_num pin)
{
	uint8_t new_pin_num = pin << 1;
	if(IO_purp == PULL_UP)
		reg->PUPDR = (reg->PUPDR & ~(1 << (new_pin_num + 1))) | (1 << new_pin_num);
	else
	if(IO_purp == PULL_DOWN)
		reg->PUPDR = (reg->PUPDR & ~(1 << new_pin_num)) | (1 << (new_pin_num + 1));
	else
	if(IO_purp == NEITHER_PULL)
		reg->PUPDR &= ~(3 << new_pin_num); 
}

void
set_systick(uint32_t time)
{
	STK->VAL &= ~(0xF << 24);
	STK->LOAD = (STK->LOAD & ~(0xF << 24)) | time;
	STK->CTRL |= (1 << 0) | (1 << 1) | (1 << 2);
}

void
set_interr(uint8_t port_name, enum pin_num pin_num)
{
	uint8_t array_exti[] = {
		6, 7, 8, 9, 10,
		23, 23, 23, 23, 23,
		40, 40, 40, 40, 40, 40
	};
	uint8_t off_set_name = (port_name - (uint8_t)'A');
	uint8_t off_set_bit = off_set_name * 4;
	RCC->APB2ENR |= (1 << 14);
	if(pin_num <= 3) {
		SYSCFG->EXTICR1 = (SYSCFG->EXTICR1 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC->ISER[(array_exti[pin_num] / 32)] |= (1 << mod(array_exti[pin_num], 32));
	}
	else
	if(pin_num >= 4 && pin_num <= 7) {
		SYSCFG->EXTICR2 = (SYSCFG->EXTICR2 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC->ISER[(array_exti[pin_num] / 32)] |= (1 << mod(array_exti[pin_num], 32));
	}
	else
	if(pin_num >= 8 && pin_num <= 11) {
		SYSCFG->EXTICR3 = (SYSCFG->EXTICR3 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC->ISER[(array_exti[pin_num] / 32)] |= (1 << mod(array_exti[pin_num], 32));
	}
	else
	if(pin_num >= 12 && pin_num <= 15) {
		SYSCFG->EXTICR4 = (SYSCFG->EXTICR4 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC->ISER[(array_exti[pin_num] / 32)] |= (1 << mod(array_exti[pin_num], 32));
	}
}

void
halt_interr(uint8_t state, enum pin_num pin_num)
{
	if(state == 0)
		EXTI->IMR &= ~(1 << pin_num);
	else
		EXTI->IMR |= (1 << pin_num);
}
