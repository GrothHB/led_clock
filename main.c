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
/* light_dig() draws the colon for any value it has no digit for */
#define DOT_DIG 10

void refresh_screen(volatile uint8_t *vec, uint8_t, uint8_t);


volatile uint32_t systime, tflag, time_of_button1, time_of_button2;
volatile uint32_t time_of_button3, time_of_button4, blink_time;
volatile logic state;
volatile uint8_t nflag, bflag1, bflag2, bflag3, right, left, nblink, digits[4];
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
	nflag = bflag1 = bflag2 = bflag3 = right = nblink = 0;
	systime = tflag = 0;
	left = 1;
	state = NEUTRAL;
	set_power_port('A', ON, &GPIOA);
	set_power_port('B', ON, &GPIOB);
	set_all(GPIOA, GPIOB);
	set_arraygnd(&ARRAY_PORTS, GPIOA, GPIOB);
	set_power_pins(&POWER_PINS, GPIOA, GPIOB);
	set_all_interr();
	set_systick(TIME);
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
				state = JUMP_BTW_WAIT;
				break;
			case JUMP_BTW_WAIT:
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
				digits[2] =  MOD(10 , (MOD(24, (tflag / 3600000))));
				digits[3] =  (MOD(24, (tflag / 3600000))) / 10;
				break;
			case SET_SEC:
				digits[0] = MOD(10, (MOD(60, nflag)));
				digits[1] = (MOD(60, nflag)) / 10;
				digits[2] = MOD(10, (MOD(60, (nflag / 60))));
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
		if(systime - blink_time > 65) {
			nblink ^= 0x1;
			blink_time = systime;
		}
		if(nblink)
			refresh_screen(&digits[0], ON, ON);
		else
			refresh_screen(&digits[0], right, left);
	}
	else refresh_screen(&digits[0], ON, ON);
	if(systime - time_of_button1 > 50)
		EXTI->IMR |= (0x1 << 9);
	if(systime - time_of_button2 > 50)
		EXTI->IMR |= (0x1 << 7);
	if(systime - time_of_button3 > 50)
		EXTI->IMR |= (0x1 << 6);
	if(systime - time_of_button4 > 50)
		EXTI->IMR |= (0x1 << 8);
}

void
buttons_interr(void)
{
	if(EXTI->PR & (0x1 << 9)) {
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
	if(EXTI->PR & (0x1 << 7)) {
		time_of_button2 = systime;
		state = JUMP_BTW;
		bflag2 = 1;
		EXTI->PR |= (0x1 << 7);
		EXTI->IMR &= ~(0x1 << 7);
	}
	else
	if(EXTI->PR & (0x1 << 6)) {
		time_of_button3 = systime;
		EXTI->PR |= (0x1 << 6);
		EXTI->IMR &= ~(0x1 << 6);
	}
	else
	if(EXTI->PR & (0x1 << 5)) {
		time_of_button4 = systime;
		++nflag;
		EXTI->PR |= (0x1 << 5);
		EXTI->IMR &= ~(0x1 << 5);
	}
}

void
refresh_screen(volatile uint8_t *vec, uint8_t right, uint8_t left)
{
	/* One element per tick. Driving all five inside a single 1 ms
	   interrupt leaves each of them lit for only a few microseconds. */
	static uint8_t slot;
	volatile struct GPIO* port;
	pins_num pin;
	uint8_t show;

	reset_all(&ARRAY_PORTS);
	turn_pin(POWER_PINS.FST, POWER_PINS.pins_num[0], OFF);
	turn_pin(POWER_PINS.SND, POWER_PINS.pins_num[1], OFF);
	turn_pin(POWER_PINS.THRD, POWER_PINS.pins_num[2], OFF);
	turn_pin(POWER_PINS.FRTH, POWER_PINS.pins_num[3], OFF);

	switch (slot) {
		case 0:
			port = POWER_PINS.FST;
			pin = POWER_PINS.pins_num[0];
			show = right;
			light_dig(&ARRAY_PORTS, vec[0]);
			break;
		case 1:
			port = POWER_PINS.SND;
			pin = POWER_PINS.pins_num[1];
			show = right;
			light_dig(&ARRAY_PORTS, vec[1]);
			break;
		case 2:
			/* colon, and the marker for the field being edited */
			if(bflag2 && !bflag3) {
				port = POWER_PINS.FRTH;
				pin = POWER_PINS.pins_num[3];
			}
			else {
				port = POWER_PINS.THRD;
				pin = POWER_PINS.pins_num[2];
			}
			show = 1;
			light_dig(&ARRAY_PORTS, DOT_DIG);
			break;
		case 3:
			port = POWER_PINS.THRD;
			pin = POWER_PINS.pins_num[2];
			show = left;
			light_dig(&ARRAY_PORTS, vec[2]);
			break;
		default:
			port = POWER_PINS.FRTH;
			pin = POWER_PINS.pins_num[3];
			show = left;
			light_dig(&ARRAY_PORTS, vec[3]);
			break;
	}
	if(show)
		turn_pin(port, pin, ON);
	slot = (slot < 4) ? (slot + 1) : 0;
}
