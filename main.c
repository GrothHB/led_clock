#include <stdint.h>
#include "symbols.h"
#include "hal.h"
#include "basic_mapping.h"
#include "led_clock.h"
#include "hardware_laout.h"

#define ON 1
#define OFF 0
/* Set for 1 milisec */
#define TIME 16000

typedef enum {
	NEUTRAL = 0,
	SETTING_TIME,
	JUMP_BTW,
	SET_TIME_SPEND,
	SET,
	ADD
}logic;

typedef enum {
	RIGHT,
	LEFT
}side;

volatile uint32_t systime;
volatile uint32_t button_time1, button_time2, button_time3;
volatile logic state = NEUTRAL;
volatile side setting = RIGHT;

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

	while(1) {
		switch (state) {
			case NEUTRAL:
				break;
			case SETTING_TIME:
				
