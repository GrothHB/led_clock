#include "symbols.h"
#include "basic_mapping.h"
#include "hal.c"

void
set_all(struct GPIO* ptr, struct GPIO* ptr2)
{
	set_moder(ptr, GENERAL, Px4);
	set_moder(ptr, GENERAL, Px0);
	set_moder(ptr, GENERAL, Px1);
	set_moder(ptr2, GENERAL, Px0);
	set_moder(ptr, GENERAL, Px3);
	set_moder(ptr, GENERAL, Px2);
	set_moder(ptr, GENERAL, Px10);
	set_moder(ptr2, GENERAL, Px3);
	set_moder(ptr2, GENERAL, Px5);
	set_moder(ptr2, GENERAL, Px4);
	set_moder(ptr2, GENERAL, Px10);
	set_moder(ptr, INPUT, Px9);
	set_moder(ptr, INPUT, Px7);
	set_moder(ptr, INPUT, Px6);
	set_moder(ptr, INPUT, Px5);
	set_moder(ptr, GENERAL, Px8);


	set_otyper(ptr, OPEN_DRAIN, Px3);
	set_otyper(ptr, OPEN_DRAIN, Px2);
	set_otyper(ptr, OPEN_DRAIN, Px10);
	set_otyper(ptr2, OPEN_DRAIN, Px3);
	set_otyper(ptr2, OPEN_DRAIN, Px5);
	set_otyper(ptr2, OPEN_DRAIN, Px4);
	set_otyper(ptr2, OPEN_DRAIN, Px10);
	set_otyper(ptr, OPEN_DRAIN, Px8);

	set_pupdr(ptr, PULL_DOWN, Px9);
	set_pupdr(ptr, PULL_DOWN, Px7);
	set_pupdr(ptr, PULL_DOWN, Px6);
	set_pupdr(ptr, PULL_DOWN, Px5);
}

void
set_arraygnd(struct ARRAYGND* ptr, struct GPIO* GPIOA, struct GPIO* GPIOB)
{
	*ptr = (ARRAYGND) {
		.A = &GPIOA,
		.B = &GPIOA,
		.C = &GPIOA,
		.E = &GPIOB,
		.F = &GPIOB,
		.G = &GPIOB,
		.H = &GPIOB,
		.DOT = &GPIOA,
		.pins_num = { 
			Px3, Px2, Px10, Px3, Px5,
			Px4, Px10, Px8
		}
	};
}

void
set_all_interr(void)
{
	set_interr((uint8_t)'A', Px9, ON);
	set_interr((uint8_t)'A', Px7, ON);
	set_interr((uint8_t)'A', Px6, ON);
}
