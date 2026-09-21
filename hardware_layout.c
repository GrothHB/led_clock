#include "symbols.h"
#include "basic_mapping.h"
#include "hal.h"
#include "utilites.h"
#include "hardware_layout.h"

void
set_all(volatile struct GPIO* ptr, volatile struct GPIO* ptr2)
{
	set_moder(ptr, GENERAL, Px4);
	set_moder(ptr, GENERAL, Px0);
	set_moder(ptr, GENERAL, Px1);
	set_moder(ptr2, GENERAL, Px0);
	set_moder(ptr2, GENERAL, Px6);
	set_moder(ptr2, GENERAL, Px9);
	set_moder(ptr, GENERAL, Px10);
	set_moder(ptr2, GENERAL, Px3);
	set_moder(ptr2, GENERAL, Px8);
	set_moder(ptr2, GENERAL, Px4);
	set_moder(ptr2, GENERAL, Px10);
	set_moder(ptr, INPUT, Px9);
	set_moder(ptr, INPUT, Px7);
	set_moder(ptr, INPUT, Px6);
	set_moder(ptr, INPUT, Px5);
	set_moder(ptr, GENERAL, Px8);


	set_otyper(ptr2, OPEN_DRAIN, Px6);
	set_otyper(ptr2, OPEN_DRAIN, Px9);
	set_otyper(ptr, OPEN_DRAIN, Px10);
	set_otyper(ptr2, OPEN_DRAIN, Px3);
	set_otyper(ptr2, OPEN_DRAIN, Px8);
	set_otyper(ptr2, OPEN_DRAIN, Px4);
	set_otyper(ptr2, OPEN_DRAIN, Px10);
	set_otyper(ptr, OPEN_DRAIN, Px8);

	set_pupdr(ptr, PULL_DOWN, Px9);
	set_pupdr(ptr, PULL_DOWN, Px7);
	set_pupdr(ptr, PULL_DOWN, Px6);
	set_pupdr(ptr, PULL_DOWN, Px5);
}

void
set_arraygnd(volatile struct ARRAYGND* ptr, volatile struct GPIO* GPIOA, volatile struct GPIO* GPIOB)
{
	*ptr = (volatile struct ARRAYGND) {
		.pin = {
			[0] = GPIOB, /* A */
			[1] = GPIOB, /* B */
			[2] = GPIOA, /* C */
			[3] = GPIOB, /* E */
			[4] = GPIOB, /* F */
			[5] = GPIOB, /* G */
			[6] = GPIOB, /* H */
			[7] = GPIOA /* DOT */
		},
		.pin_num = { 
			Px9, Px6, Px10, Px3, Px8,
			Px4, Px10, Px8
		}
	};
}

void
set_all_interr(void)
{
	set_interr((uint8_t)'A', Px9);
	set_interr((uint8_t)'A', Px7);
	set_interr((uint8_t)'A', Px6);
	set_interr((uint8_t)'A', Px5);
}

void
set_power_pins(volatile struct ARRAYELECT* power_array, volatile struct GPIO* GPIOA, volatile struct GPIO* GPIOB)
{
	*power_array = (volatile struct ARRAYELECT) {
		.pin = {
			[0] = GPIOA,
			[1] = GPIOA,
			[2] = GPIOA,
			[3] = GPIOB
		},
		.pin_num = { Px4, Px0, Px1, Px0 }
	};
}
