#include <stdint.h>
#include "symbols.h"
#include "hal.h"
#include "basic_mapping.h"
#include "hardware_layout.h"
#include "utilites.h"
#include "mod.h"
#include "dig_disp.h"

#define ON 1
#define OFF 0
/* Set for 1 milisec */
#define TIME 16000

void 		refresh_screen(uint8_t , uint8_t);
void		switch_off(void);
void		calc_digits(uint32_t);


volatile uint32_t 		systime, time_of_button1, tflag;
volatile uint32_t		clock_time;
volatile uint32_t		time_of_button2, blink_time, nflag;
volatile uint32_t 		time_of_button3, time_of_button4;
volatile uint8_t		digits[4];
volatile struct GPIO 		*GPIOA, *GPIOB;
volatile struct ARRAYGND 	ARRAY_PORTS;
volatile struct ARRAYELECT 	POWER_PINS;
volatile enum clock_state	state;
volatile enum side_focus	side;
volatile enum time_interval	timep;
volatile enum mode_state	in_mode;

int
main(void)
{
	digits[0] = 0;
	digits[1] = 0;
	digits[2] = 0;
	digits[3] = 0;
	nflag = 0;
	systime = clock_time = tflag = 0;
	state = SLEEP;
	timep = HOURS;
	in_mode = BLOCK;
	set_power_port('A', ON, &GPIOA);
	set_power_port('B', ON, &GPIOB);
	set_SEG();
	set_all(GPIOA, GPIOB);
	set_arraygnd(&ARRAY_PORTS, GPIOA, GPIOB);
	set_power_pins(&POWER_PINS, GPIOA, GPIOB);
	set_all_interr();
	set_systick(TIME);
	halt_interr(OFF, Px7);
	halt_interr(OFF, Px6);
	halt_interr(OFF, Px5);
	while (1) {
		__asm volatile ("wfi");
		switch (state) {
		case SLEEP:
			break;
		case TURN_ON:
			switch (in_mode) {
			case BLOCK:
				break;
			case SET_INTERVAL:
				if (timep == HOURS) {
					timep = MIN;
					digits[0] = 0;
					digits[1] = 0;
					digits[2] = 0;
					digits[3] = 0;
				} else {
					timep = HOURS;
					digits[0] = 0;
					digits[1] = 0;
					digits[2] = 0;
					digits[3] = 0;
				}
				nflag = 0;
				in_mode = BLOCK;
				break;
			case SET_SIDE:
				if (side == LEFT) {
					side = RIGHT;
				} else {
					side = LEFT;
				}
				in_mode = BLOCK;
				break;
			case ADD:
				if (side == RIGHT)
					++nflag;
				else
					nflag += 60;
				calc_digits(nflag);
				in_mode = BLOCK;
				break;
			}
			break;
		case REAL_TIME:
			if (timep == MIN) {
				if (systime - clock_time < 1000)
					break;
				++tflag;
				clock_time = systime;
			} else {
				if (systime - clock_time < 60000)
					break;
				++tflag;
				clock_time = systime;
			}
			calc_digits(tflag);
			break;
		}
	}
	return 0;
}
				
void
systick_interr(void)
{
	static uint32_t iter = 0;
	iter = mod((iter + 1), 4);
	++systime;
	if (state == SLEEP) {
		halt_interr(ON, Px9);
		return;
	}
	if (state == TURN_ON) {
		if (side == RIGHT) {
			switch_off();
			if (iter == 0 || iter == 1) {
				if (systime - blink_time < 350) {
					refresh_screen(digits[iter], iter);
				} else if (systime - blink_time >= 700) {
					blink_time = systime;
				}
			} else {
				refresh_screen(digits[iter], iter);
			}
		} else {
			switch_off();
			if (iter == 2 || iter == 3) {
				if (systime - blink_time < 350) {
					refresh_screen(digits[iter], iter);
				} else if (systime - blink_time >= 700) {
					blink_time = systime;
				}
			} else {
				refresh_screen(digits[iter], iter);
			}
		}
	} else {
		switch_off();
		refresh_screen(digits[iter], iter);
	}
	if (systime - time_of_button1 > 200 && time_of_button1)
		halt_interr(ON, Px9);
	if (systime - time_of_button2 > 200 && time_of_button2)
		halt_interr(ON, Px7);
	if (systime - time_of_button3 > 200 && time_of_button3)
		halt_interr(ON, Px6);
	if (systime - time_of_button4 > 200 && time_of_button4)
		halt_interr(ON, Px5);
}

void
buttons_interr(void)
{
	if ((EXTI->PR >> 9) & 0x1) {
		time_of_button1 = systime;
		if (state == SLEEP) {
			state = TURN_ON;
			side = RIGHT;
			switch_off();
			EXTI->IMR |= (0X1 << 7);
			EXTI->IMR |= (0X1 << 6);
			EXTI->IMR |= (0X1 << 5);
		} else if (state == TURN_ON) {
			state = REAL_TIME;
			switch_off();
			tflag = nflag;
			clock_time = systime;
			EXTI->IMR &= ~(0X1 << 7);
			EXTI->IMR &= ~(0X1 << 6);
			EXTI->IMR &= ~(0X1 << 5);
		} else if (state == REAL_TIME) {
			state = SLEEP;
			switch_off();
			in_mode = BLOCK;
			nflag = tflag;
		}
		EXTI->PR = (0x1 << 9);
		EXTI->IMR &= ~(0x1 << 9);
	} else if ((EXTI->PR >> 7) & 0x1) {
		time_of_button2 = systime;
		in_mode = SET_INTERVAL;
		EXTI->PR = (0x1 << 7);
		EXTI->IMR &= ~(0x1 << 7);
	} else if ((EXTI->PR >> 6) & 0x1) {
		time_of_button3 = systime;
		in_mode = SET_SIDE;
		EXTI->PR = (0x1 << 6);
		EXTI->IMR &= ~(0x1 << 6);
	} else if ((EXTI->PR >> 5) & 0x1) {
		time_of_button4 = systime;
		in_mode = ADD;
		EXTI->PR = (0x1 << 5);
		EXTI->IMR &= ~(0x1 << 5);
	}
}
void
refresh_screen(uint8_t digv, uint8_t scn)
{
	set_digit(&ARRAY_PORTS, digv);
	if (timep == HOURS && state == TURN_ON && scn == 0)		
		MASK_ON(ARRAY_PORTS.pin[7]->BSRR, ARRAY_PORTS.pin_num[7]);
	else if (state == REAL_TIME && scn == 2)
		MASK_ON(ARRAY_PORTS.pin[7]->BSRR, ARRAY_PORTS.pin_num[7]);
	else if (timep == MIN && state == TURN_ON && scn == 3)
		MASK_ON(ARRAY_PORTS.pin[7]->BSRR, ARRAY_PORTS.pin_num[7]);
	turn_pin(POWER_PINS.pin[scn], POWER_PINS.pin_num[scn], ON);
}
	
void
switch_off(void)
{
	turn_pin(POWER_PINS.pin[0] ,POWER_PINS.pin_num[0], OFF);
	turn_pin(POWER_PINS.pin[1] ,POWER_PINS.pin_num[1], OFF);
	turn_pin(POWER_PINS.pin[2] ,POWER_PINS.pin_num[2], OFF);
	turn_pin(POWER_PINS.pin[3] ,POWER_PINS.pin_num[3], OFF);
}

void
calc_digits(uint32_t val)
{
	uint32_t 		divbs, ms;
	ms = mod(val, 60);
	divbs = val / 60; 
	if (timep == MIN) {
		digits[0] = mod(ms, 10); 
		digits[1] = ms / 10;
		digits[2] = mod(mod(divbs, 60), 10);
		digits[3] = mod(divbs, 60) / 10;
	} else {
		digits[0] = mod(ms, 10);
		digits[1] = ms / 10;
		digits[2] = mod(mod(divbs, 24), 10);
		digits[3] = mod(divbs, 24) / 10;
	}
}
