#include <stdint.h>
#include "symbols.h"
#include "hal.h"
#include "basic_mapping.h"
#include "clock_led.h"

#define ON 1
#define OFF 0
/* Set for 1 milisec */
#define TIME 16000
volatile uint32_t systime;
volatile uint32_t button_time1, button_time2, button_time3;

void time_inter(void);
void set_all(struct GPIO* ptr, struct GPIO* potr2);
void set_arraygnd(struct ARRAYGND* ptr, struct GPIO* fst, struct GPIO* snd);

int
main(void)
{
	struct GPIO GPIOA, GPIOB;
	struct ARRAYGND ARRAY_PORTS;
	set_power('A', ON, &GPIOA);
	set_power('A', ON, &GPIOB);
	set_all(&GPIOA, &GPIOB);
	ARRAY_PORTS = {
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
	set_moder(ptr, GENERAL, Px9);
	set_moder(ptr, GENERAL, Px7);
	set_moder(ptr, GENERAL, Px6);
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
}

void
set_arraygnd(struct ARRAYGND* ptr, struct GPIO* GPIOA, struct GPIO* GPIOB)
{
	ARRAY_PORTS = {
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
	
