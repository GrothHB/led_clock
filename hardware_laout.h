
#include "symbols.h"
#include "basic_mapping.h"
#include "hal.h"

void set_all(struct GPIO* ptr, struct GPIO* ptr2);
void set_arraygnd(struct ARRAYGND* ptr, struct GPIO* fst, struct GPIO* snd);
void set_all_interr(void);
