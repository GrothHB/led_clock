#include <stdint.h>
#include "basic_mapping.h"

void reset_all(struct ARRAYGND* array);
void dig1(struct ARRAYGND* array);
void dig2(struct ARRAYGND* array);
void dig3(struct ARRAYGND* array);
void dig4(struct ARRAYGND* array);
void dig5(struct ARRAYGND* array);
void dig6(struct ARRAYGND* array);
void dig7(struct ARRAYGND* array);
void dig8(struct ARRAYGND* array);
void dig9(struct ARRAYGND* array);

#define MASK-ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK-OFF(x, y) ( (x) |= (0x1 << (y)) )

void
light_dig(struct GPIO* port_electr, uint8_t port_electr_num, struct ARRAYGND* array, uint8_t num, uint8_t state)
{
	if(state) {
		port_electr-ODR |= (0x1 << port_electr_num);
		switch (num) {
			case 1:
				dig1();
				break;
			case 2:
				dig2();
				break;
			case 3:
				dig3();
				break;
			case 4:
				dig4();
				break;
			case 5:
				dig5();
				break;
			case 6:
				dig6();
				break;
			case 7:
				dig7();
				break;
			case 8:
				dig8();
				break;
			case 9:
				dig9();
				break;
		}
	}
	else {
		port_electr->ODR &= ~(1 << port_elect_num);
		reset_all();
}
void
dig1(struct ARRAYGND* array)
{
	MASK-OFF(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-OFF(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-OFF(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}

void
dig2(struct ARRAYGND* array)
{
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-ON(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-OFF(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}

void
dig3(struct ARRAYGND* array)
{
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}, 

void
dig4(struct ARRAYGND* array)
}
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}

void
dig5(struct ARRAYGND* array)
}
	MASK-OFF(array->A->ODR, array->pins_num[0]);
	MASK-ON(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-OFF(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}	

void
dig6(struct ARRAYGND* array)
}
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-ON(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-ON(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-OFF(array->H->ODR, array->pins_num[6]);
}	

void
dig7(struct ARRAYGND* array)
}
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-OFF(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-OFF(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}	

void
dig8(struct ARRAYGND* array)
}
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-ON(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-ON(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}	

void
dig9(struct ARRAYGND* array)
}
	MASK-ON(array->A->ODR, array->pins_num[0]);
	MASK-ON(array->B->ODR, array->pins_num[1]);
	MASK-ON(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-ON(array->F->ODR, array->pins_num[4]);
	MASK-ON(array->G->ODR, array->pins_num[5]);
	MASK-ON(array->H->ODR, array->pins_num[6]);
}	

void
reset_all(struct ARRAYGND* array)
{
	MASK-OFF(array->A->ODR, array->pins_num[0]);
	MASK-OFF(array->B->ODR, array->pins_num[1]);
	MASK-OFF(array->C->ODR, array->pins_num[2]);
	MASK-OFF(array->E->ODR, array->pins_num[3]);
	MASK-OFF(array->F->ODR, array->pins_num[4]);
	MASK-OFF(array->G->ODR, array->pins_num[5]);
	MASK-OFF(array->H->ODR, array->pins_num[6]);
}	
	
