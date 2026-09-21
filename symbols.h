#ifndef SYMBOLS_H
#define SYMBOLS_H

enum pin_num {
	Px0 = 0, Px1, Px2, Px3, Px4,
	Px5, Px6, Px7, Px8, Px9, Px10,
	Px11, Px12, Px13, Px14, Px15
};

enum pinconf {
	INPUT = 0, GENERAL, ALT_FUN,
	ANALOG, PUSH_PULL, OPEN_DRAIN,
	PULL_UP, PULL_DOWN, NEITHER_PULL
};

enum mode_state {
	BLOCK,
	SET_INTERVAL,
	SET_SIDE,
	ADD
};

enum time_interval {
	HOURS,
	MIN
};

enum side_focus {
	LEFT,
	RIGHT
};

enum clock_state {
	SLEEP,
	TURN_ON,
	REAL_TIME
};

#endif
