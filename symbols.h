#ifndef SYMBOLS_H
#define SYMBOLS_H

typedef enum {
	Px0 = 0, Px1, Px2, Px3, Px4,
	Px5, Px6, Px7, Px8, Px9, Px10,
	Px11, Px12, Px13, Px14, Px15
}pins_num;

typedef enum {
	INPUT = 0, GENERAL, ALT_FUN,
	ANALOG, PUSH_PULL, OPEN_DRAIN,
	PULL_UP, PULL_DOWN, NEITHER_PULL
}pinconf;

typedef enum {
	NEUTRAL = 0,
	SETTING_TIME,
	JUMP_BTW,
	JUMP_BTW_WAIT,
	SET_TIME_SPEND,
	SET,
	SET_SEC,
	SET_MIN,
	ADD_SEC,
	ADD_MIN
}logic;

#endif
