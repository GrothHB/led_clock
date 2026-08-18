#include <stdint.h>
#include "symbols.h"
#include "hal.h"
#include "basic_mapping.h"
#include "clock_led.h"
#include "hardware_laout.h"

#define ON 1
#define OFF 0
/* Set for 1 milisec */
#define TIME 16000
void time_inter(void);
void set_arraygnd(struct ARRAYGND* ptr, struct GPIO* fst, struct GPIO* snd);
void set_all_interr(void);

volatile uint32_t systime;
volatile uint32_t button_time1, button_time2, button_time3;

int
main(void)
{
	struct GPIO GPIOA, GPIOB;
	struct ARRAYGND ARRAY_PORTS;
	set_power('A', ON, &GPIOA);
	set_power('A', ON, &GPIOB);
	set_all(&GPIOA, &GPIOB);
	set_arraygnd(&ARRAY_PORTS, &GPIOA, &GPIOB);
	set_all_interr();
	

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
