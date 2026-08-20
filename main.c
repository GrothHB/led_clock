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
#define BASIC 1
#define MIN 60
#define HOUR 24

typedef enum {
	NEUTRAL = 0,
	SETTING_TIME,
	JUMP_BTW,
	SET_TIME_SPEND,
	SET,
	SET_SEC,
	SET_MIN,
	ADD_SEC,
	ADD_MIN
}logic;

void update_time(side val);
void display(uint8_t val, struct ARRAYELECT* ptr, struct ARRAYGND*);
void get_time(struct ARRAYGND*, struct ARRAYELECT*, uint32_t, side);

volatile uint32_t systime, tflag, time_of_button1, time_of_button2;
volatile uint32_t time_of_button3, time_of_button4;
volatile logic state = NEUTRAL;
volatile uint8_t nflag, bflag1, bflag2, bflag3, rigth, left, digits[4];
nflag = bflag1 = bflag2 = bflag3 = rflag = right = 0;
left = 1;

systime = tflag = 0;
volatile struct GPIO GPIOA, GPIOB;
volatile struct ARRAYGND ARRAY_PORTS;
volatile struct ARRAYELECT POWER_PINS;
set_power('A', ON, &GPIOA);
set_power('A', ON, &GPIOB);
set_all(&GPIOA, &GPIOB);
set_arraygnd(&ARRAY_PORTS, &GPIOA, &GPIOB);
set_power_pins(&POWER_PINS, &GPIOA, &GPIOB);
set_all_interr();

int
main(void)
{
	while(1) {
		switch (state) {
			case NEUTRAL:
				break;
			case SETTING_TIME:
				bflag1 = MOD(2, (bflag1 + 1));
				state = bflag1 ? JUMP_BTW: SET;
				break;
			case JUMP_BTW:
				right ^= 0x1;
				left ^= 0x1;
				break;
			case SET_TIME_SPEND:
				bflag3 = MOD(2, (bfalg3 + 1));
				state = bfalg3 ? SET_SEC: SET_MIN;
				break;
			case SET:
				state = bflag3 ? ADD_SEC: ADD_MIN;
				bflag2 = 0;
				tflag = systime;
				break;
			case ADD_SEC:
				digits[0] =  MOD(10 , (MOD(60, (tflag / 1000)))));
				digits[1] = (MOD(60, (mflag / 1000)) / 10));
				digits[2] =  MOD(10 , (MOD(60, (tflag / 60000)))));
				digits[3] =  (MOD(60, (mflag / 60000)) / 10));
				break;
			case ADD_MIN:
				digits[0] =  MOD(10 , (MOD(60, (tflag / 60000))));
				digits[1] = (MOD(60, tflag / 60000)) / 10;
				digits[2] =  MOD(10 , (MOD(24, (tflag / 360000))));
				digits[3] =  (MOD(24, (tflag / 360000))) / 10;
				break;
			case SET_SEC:
				digits[0] = MOD(10, (MOD(60, nflag)));
				digits[1] = (MOD(60, nflag)) / 10;
				digits[2] = MOD(60, (nflag / 60));
				digits[3] = (MOD(60, (nflag / 60))) / 10;
				break;
			case SET_MIN:
				digits[0] =  MOD(10 , (MOD(60, nflag)));
				digits[1] = (MOD(60, nflag)) / 10;
				digits[2] =  MOD(10 , (MOD(24, (tflag / 60))));
				digits[3] =  (MOD(24, (tflag / 60))) / 10;
				break;
		}
	}
	return 0;
}
				
void
systick_interr(void)
{
	++systime;
	++tflag;
	if(bflag2) {
		if(bflag3) {
			turn_dot(POWER_PINS->THRD, POWER_PINS->pins_num[2], ON);
			turn_dot(POWER_PINS->THRD, POWER_PINS->pins_num[2], OFF);
		}
		else {
			turn_dot(POWER_PINS->FRTH, POWER_PINS->pins_num[3], ON);
			turn_dot(POWER_PINS->FRTH, POWER_PINS->pins_num[3], OFF);
		}
		refresh_screen(&digits[0], right, left);
	}
	else refresh_screen(&digits[0], 1, 1);
	if(systime - time_of_button1 > 50)
		EXTI->IMR |= (0x1 << 9);
	if(systime - time_of_button2 > 50)
		EXTI->IMR |= (0x1 << 7);
	if(systime - time_of_button3 > 50)
		EXTI->IMR &= (0x1 << 6);
	if(systime - time_of_button4 > 50)
		EXTI->IMR |= (0x1 << 8);
}

void
buttons_interr(void)
{
	if(EXTI->PR & ~(Ox1 << 9)) {
		time_of_button1 = systime;
		state = SETTING_TIME;
		EXTI->PR |= (0x1 << 9);
		EXTI->IMR &= ~(0x1 << 9);
	}
	else
	if(EXTI->PR & ~(0x1 << 7)) {
		time_of_button2 = systime;
		state = JUMP_BTW;
		bflag2 = 1;
		EXTI->PR |= (0x1 << 7);
		EXTI->IMR &= ~(0x1 << 7);
	}
	else
	if(EXTI->PR & ~(0x1 << 6)) {
		time_of_button3 = systime;
		EXTI->PR |= (0x1 << 6);
		EXTI->IMR &= ~(0x1 << 6);
	}
	else
	if(EXTI->PR & ~(0x1 << 8)) {
		time_of_button4 = systime;
		++nflag;
		EXTI->PR |= (0x1 << 8);
		EXTI->IMR &= ~(0x1 << 8);
	}
}

void
refresh_screen(uint8_t *vec, right, left)
{
	turn_pin(POWER_PIN.FST, POWER_PIN.pins_num[0], ON & left);
	light_dig(&ARRAY_PORTS, vec[0]);
	turn_pin(POWER_PIN.FST, POWER_PIN.pins_num[0], OFF);
	turn_pin(POWER_PIN.SND, POWER_PIN.pins_num[1], ON & left);
	light_dig(&ARRAY_PORTS,vec[1]);
	turn_pin(POWER_PIN.SND, POWER_PIN.pins_num[1], OFF);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[2], ON & right);
	light_dig(&ARRAY_PORTS, vec[2]);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[2], OFF);
	turn_pin(POWER_PIN.FRTH, POWER_PIN.pins_num[3], ON & right);
	light_dig(&ARRAY_PORTS, vec[3]);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[3], OFF);
}
	
void
light_dot(struct GPIO* ptr, pins_num pin, uint8_t lg)
{
	turn_pin(ptr, pin, lg);
	light_dig(&ARRAY_PORTS, 10);
}
