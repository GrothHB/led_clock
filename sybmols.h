#include <stdint.h>

typedef enum {
	Px0 = 0, Px1, Px2, Px3, Px4
	Px5, Px6, Px7, Px8, Px9, Px10,
	Px11, Px12, Px13, Px14, Px15
}pins_num;

typedef enum {
	INPUT = 0, GENERAL, ALT_FUN,
	ANALOG, PUSH-PULL, OPEN-DRAIN,
	PULL-UP, PULL-DOWN, NEITHER-PULL
}pinconf;

