#include <stdint.h>
#include "symbols.h"
#include "hal.h"
#include "basic_mapping.h"
#include "led_clock.h"
#include "hardware_laout.h"
#include "utilites.h"

#define ON 1
#define OFF 0
/* Set for 1 milisec */
#define TIME 16000
#define BASIC 1

void light_dot(volatile struct GPIO* ptr, pins_num pin, uint8_t lg);
void refresh_screen(volatile uint8_t *vec, uint8_t, uint8_t);


volatile uint32_t systime, tflag, time_of_button1, time_of_button2;
volatile uint32_t time_of_button3, time_of_button4, blink_time;
volatile logic state;
volatile uint8_t nflag, bflag1, bflag2, bflag3, right, left, digits[4];
volatile struct GPIO *GPIOA, *GPIOB;
volatile struct ARRAYGND ARRAY_PORTS;
volatile struct ARRAYELECT POWER_PINS;

int
main(void)
{
	digits[0] = 0;
	digits[1] = 0;
	digits[2] = 0;
	digits[3] = 0;
	nflag = bflag1 = bflag2 = bflag3 = right = 0;
	systime = tflag = 0;
	left = 1;
	state = NEUTRAL;
	set_power_port('A', ON, &GPIOA);
	set_power_port('B', ON, &GPIOB);
	set_all(GPIOA, GPIOB);
	set_arraygnd(&ARRAY_PORTS, GPIOA, GPIOB);
	set_power_pins(&POWER_PINS, GPIOA, GPIOB);
	set_all_interr();
	EXTI->IMR &= ~(0x1 << 7);
	EXTI->IMR &= ~(0x1 << 6);
	EXTI->IMR &= ~(0x1 << 5);
	while(1) {
		switch (state) {
			case NEUTRAL:
				break;
			case SETTING_TIME:
				bflag1 = MOD(2, (bflag1 + 1));
				state = bflag1 ? JUMP_BTW: SET;
				blink_time = systime;
				break;
			case JUMP_BTW:
				right ^= 0x1;
				left ^= 0x1;
				break;
			case SET_TIME_SPEND:
				bflag3 = MOD(2, (bflag3 + 1));
				state = bflag3 ? SET_SEC: SET_MIN;
				break;
			case SET:
				state = bflag3 ? ADD_SEC: ADD_MIN;
				bflag2 = 0;
				tflag = systime;
				break;
			case ADD_SEC:
				digits[0] =  MOD(10 , (MOD(60, (tflag / 1000))));
				digits[1] = (MOD(60, (tflag / 1000))) / 10;
				digits[2] =  MOD(10 , (MOD(60, (tflag / 60000))));
				digits[3] =  (MOD(60, (tflag / 60000))) / 10;
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
				digits[2] =  MOD(10 , (MOD(24, (nflag / 60))));
				digits[3] =  (MOD(24, (nflag / 60))) / 10;
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
			light_dot(POWER_PINS.THRD, POWER_PINS.pins_num[2], ON);
			light_dot(POWER_PINS.THRD, POWER_PINS.pins_num[2], OFF);
		}
		else {
			light_dot(POWER_PINS.FRTH, POWER_PINS.pins_num[3], ON);
			light_dot(POWER_PINS.FRTH, POWER_PINS.pins_num[3], OFF);
		}
		if(systime - blink_time > 65) {
			refresh_screen(&digits[0], ON, ON);
			blink_time = systime;
		}
		else 
			refresh_screen(&digits[0], right, left);
	}
	else refresh_screen(&digits[0], ON, ON);
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
	if(EXTI->PR & ~(0x1 << 9)) {
		time_of_button1 = systime;
		state = SETTING_TIME;
		EXTI->PR |= (0x1 << 9);
		EXTI->IMR &= ~(0x1 << 9);
		if(!bflag1) {
			EXTI->IMR &= ~(0X1 << 7);
			EXTI->IMR &= ~(0X1 << 6);
			EXTI->IMR &= ~(0X1 << 5);
		}
		else {  
			EXTI->IMR |= (0X1 << 7);
			EXTI->IMR |= (0X1 << 6);
			EXTI->IMR |= (0X1 << 5);
		}
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
	if(EXTI->PR & ~(0x1 << 5)) {
		time_of_button4 = systime;
		++nflag;
		EXTI->PR |= (0x1 << 5);
		EXTI->IMR &= ~(0x1 << 5);
	}
}

void
refresh_screen(volatile uint8_t *vec, uint8_t right, uint8_t left)
{
	turn_pin(POWER_PINS.FST, POWER_PINS.pins_num[0], ON & right);
	light_dig(&ARRAY_PORTS, vec[0]);
	turn_pin(POWER_PINS.FST, POWER_PINS.pins_num[0], OFF);
	turn_pin(POWER_PINS.SND, POWER_PINS.pins_num[1], ON & right);
	light_dig(&ARRAY_PORTS,vec[1]);
	turn_pin(POWER_PINS.SND, POWER_PINS.pins_num[1], OFF);
	light_dot(POWER_PINS.THRD, POWER_PINS.pins_num[2], ON);
	light_dot(POWER_PINS.THRD, POWER_PINS.pins_num[2], OFF);
	turn_pin(POWER_PINS.THRD, POWER_PINS.pins_num[2], ON & left);
	light_dig(&ARRAY_PORTS, vec[2]);
	turn_pin(POWER_PINS.THRD, POWER_PINS.pins_num[2], OFF);
	turn_pin(POWER_PINS.FRTH, POWER_PINS.pins_num[3], ON & left) ;
	light_dig(&ARRAY_PORTS, vec[3]);
	turn_pin(POWER_PINS.THRD, POWER_PINS.pins_num[3], OFF);
}
	
void
light_dot(volatile struct GPIO* ptr, pins_num pin, uint8_t lg)
{
	turn_pin(ptr, pin, lg);
	light_dig(&ARRAY_PORTS, 10);
}
