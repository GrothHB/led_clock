#include "basic_mapping.h"
#include <stdint.h>
#include "symbols.h"

#define POWER32 (1UL << 32)
#define MAGIC_NUM(k) ( POWER32 / (k) )
#define DIV(k, n) ( (uint32_t)( ((uint64_t)(n) * MAGIC_NUM(k)) >> 32 ))
#define MOD(k, n) ((n) - (DIV(k, n) * (k)))

void
set_power_port(uint32_t port, uint32_t state, struct GPIO* gpio)
{
	uint32_t off_set = port - (uint32_t)'A';
	if(state && (off_set > 0 && off_set < 5))
		RCC->ABH1ENR |= (1 << off_set);
		gpio = (struct GPIO*)(0x40020000 + (0x400 * off_set));
	else if(off_set > 0 && off_set < 5)
		RCC->ABH1ENR &= ~(1 << off_set);
}

void
set_moder(struct GPIO* reg, portconf IO_purp, uint32_t pin_num)
{
	uint8_t new_pin_num = pin_num << 1;
	reg->MODER = reg->MODER & ~((1 << (new_pin_num + 1)) | (1 << new_pin_num) );
	if(IO_purp == GENER)
		reg->MODER |= (1 << new_pin_num);
	else
	if(IO_purp == ALT_FUN)
		reg->MODER |= (1 << (new_pin_num + 1));
	else
	if(IO_purp == ANALOG)
		reg->MODER |= (1 << (new_pin_num + 1)) | (1 << new_pin_num);
}

void
set_otyper(struct GPIO* reg, portconf IO_purp, uinit32_t pin_num)
{
	if(IO_purp == PUSH_PULL)
		reg->OTYPER &= ~(1 << pin_num);
	else
		reg->OTYPER |= (1 << pin_num);
}

void
set_pupdr(struct GPIO* reg, portconf IO_purp, uinit32_t pin_num)
{
	uint8_t new_pin_num = pin_num << 1;
	if(IO_purp == PULL_UP)
		reg->PUPDR = (reg->PUPDR & ~(1 << (new_pin_num + 1)) | (1 << new_pin_num);
	else
	if(IO_purp == PULL_DOWN)
		reg->PUPDR = (reg->PUPDR & ~(1 << new_pin_num) | (1 << (new_pin_num + 1));
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
switches_port(struct GPIO* reg, pins_num pin_num, uint8_t state)
{
	if(state)
		reg-ODR |= (1 << pin_num);
	else
		reg-ODR &= ~(1 << pin_num);
}

void
set_interr(uint8_t port_name, pins_num pin_num, uint8_t state)
{
	uint8_t array_exti[] = {
		6, 7, 8, 9, 10,
		23, 23, 23, 23, 23,
		40, 40, 40, 40, 40, 40
	};
	uint8_t off_set_name = (port_name - (uint8_t)'A');
	uint8_t off_set_bit = off_set_name * 4;
	RCC->APB2ENR |= (1 << 14);
	if(pin_num >= 0 && pin_num <= 3) {
		SYSCFG->EXTICR1 = ((SYSCFG->EXTICR1 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC-ISER[MOD(32, array_exti[pin_num])] |= (1 << MOD(32, array_exti[pin_num]));
	}
	else
	if(pin_num >= 4 && pin_num <= 7) {
		SYSCFG->EXTICR2 = ((SYSCFG->EXTICR1 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC-ISER[MOD(32, array_exti[pin_num])] |= (1 << MOD(32, array_exti[pin_num]));
	}
	else
	if(pin_num >= 8 && pin_num <= 11) {
		SYSCFG->EXTICR3 = ((SYSCFG->EXTICR1 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC-ISER[MOD(32, array_exti[pin_num])] |= (1 << MOD(32, array_exti[pin_num]));
	}
	else
	if((pin_num >= 12 && pin_num <= 15) {
		SYSCFG->EXTICR4 = ((SYSCFG->EXTICR1 & ~(0xF << off_set_bit)) | (off_set_name << off_set_bit);
		EXTI->IMR |= (1 << pin_num);
		EXTI->RTSR |= (1 << pin_num);
		NVIC-ISER[MOD(32, array_exti[pin_num])] |= (1 << MOD(32, array_exti[pin_num]));
	}
}

void
halt_interr(uint8_t state, pins_num pin_num)
{
	if(state == 0)
		EXTI->IMR &= ~(1 << pin_num);
	else
		EXTI->IMR |= (1 << pin_num);
}
