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

typedef enum {
	RIGHT,
	LEFT
}side;

void update_time(side val);
void display(uint8_t val, struct ARRAYELECT* ptr, struct ARRAYGND*);
void get_time(struct ARRAYGND*, struct ARRAYELECT*, uint32_t, side);

volatile uint32_t systime, pflag1, pflag2, pflag3, sflag;
volatile uint32_t button_time1, button_time2, button_time3;
volatile logic state = NEUTRAL;
volatile side setting = RIGHT;
volatile uint8_t nflag, rflag, cflag1, cflag3, digits[4];
nflag = mflag = cflag1 = cflag2 = cflag3 = 0;

systime = button_time1 = button_time2 = button_time3 = 0;
pflag = BASIC;

int
main(void)
{
	struct GPIO GPIOA, GPIOB;
	struct ARRAYGND ARRAY_PORTS;
	struct ARRAYELECT POWER_PINS;
	set_power('A', ON, &GPIOA);
	set_power('A', ON, &GPIOB);
	set_all(&GPIOA, &GPIOB);
	set_arraygnd(&ARRAY_PORTS, &GPIOA, &GPIOB);
	set_power_pins(&POWER_PINS, &GPIOA, &GPIOB);
	set_all_interr();

	while(1) {
		switch (state) {
			case NEUTRAL:
				break;
			case SETTING_TIME:
				state = cflag1 ? JUMP_BTW: SET_TIME_SPEND;
				break;
			case JUMP_BTW:
				setting = (setting == RIGHT) ? LEFT: RIGHT;
				state = cflag3 ? ADD_SEC: ADD_MIN;
				break;
			case SET_TIME_SPEND:
				cflag3 = MOD(2, (cflag3 + 1));
				break;
			case SET:
				state = cflag3 ? SET_SEC: SET_MIN;
				break;
			case ADD_SEC:
				digits[0] =  MOD(10 , (MOD(60, (mflag / 1000)))));
				digits[1] = (MOD(60, (mflag / 1000)) / 10));
				digits[2] =  MOD(10 , (MOD(60, (mflag / 60000)))));
				digits[3] =  (MOD(60, (mflag / 60000)) / 10));
				break;
			case ADD_MIN:
				digits[0] =  MOD(10 , (MOD(60, (mflag / 60000)))));
				digits[1] = (MOD(60, (mflag / 60000)) / 10));
				digits[2] =  MOD(10 , (MOD(60, (mflag / 360000)))));
				digits[3] =  (MOD(60, (mflag / 360000)) / 10));
				break;
			case SET_SEC:
				
void
systick_inter(void)
{
	++systime;
	++sflag;
	refresh_screen(&digits[0]);

}

void
refresh_screen(uint8_t *vec)
{
	turn_pin(POWER_PIN.FST, POWER_PIN.pins_num[0], ON);
	light_dig(&ARRAY_PORTS, vec[0]);
	turn_pin(POWER_PIN.FST, POWER_PIN.pins_num[0], OFF);
	turn_pin(POWER_PIN.SND, POWER_PIN.pins_num[1], ON);
	light_dig(&ARRAY_PORTS,vec[1]);
	turn_pin(POWER_PIN.SND, POWER_PIN.pins_num[1], OFF);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[2], ON);
	light_dig(&ARRAY_PORTS, vec[2]);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[2], OFF);
	turn_pin(POWER_PIN.FRTH, POWER_PIN.pins_num[3], ON);
	light_dig(&ARRAY_PORTS, vec[3]);
	turn_pin(POWER_PIN.THRD, POWER_PIN.pins_num[3], OFF);
}
	
void
sys_inter(void)
{
	
uint8_t
update_time(side val)
{
	uint32_t time;
	time = cflag3 ? MIN: HOUR;
	if(val == RIGHT) {
		nflag = MOD(60, (nflag + 1));
		return nflag;
	}
	else {
		mflag = MOD(time, (mflag + 1));
		return mflag;
	}
}

void
display(uint8_t time, struct ARRAYELECT* ptr, struct ARRAYGND* ARRAY_PORT, side sideflag)
{
	if(sideflag == RIGHT) {
		turn_pin(ptr->FST, ptr->pins_num[0], ON);
		light_dig(ARRAY_PORTS, MOD(10, time));
		turn_pin(ptr->FST, ptr->pins_num[0], OFF);
		turn_pin(ptr->SND, ptr->pins_num[1], ON);
		ligth_dig(ARRAY_PORTS, (time - MOD(10, time)));
		turn_pin(ptr->SND, ptr->pins_num[1], OFF);
	}
	else {
		turn_pin(ptr->THRD, ptr->pins_num[2], ON);
		light_dig(ARRAY_PORTS, MOD(10, time));
		turn_pin(ptr->THRD, ptr->pins_num[2], OFF);
		turn_pin(ptr->FRTH, ptr->pins_num[3], ON);
		ligth_dig(ARRAY_PORTS, (time - MOD(10, time)));
		turn_pin(ptr->FRTH, ptr->pins_num[3], OFF);
	}
}
