#include <stdint.h>
#include "basic_mapping.h"

void reset_all(struct ARRAYGND* array);
void dig0(struct ARRAYGND* array);
void dig1(struct ARRAYGND* array);
void dig2(struct ARRAYGND* array);
void dig3(struct ARRAYGND* array);
void dig4(struct ARRAYGND* array);
void dig5(struct ARRAYGND* array);
void dig6(struct ARRAYGND* array);
void dig7(struct ARRAYGND* array);
void dig8(struct ARRAYGND* array);
void dig9(struct ARRAYGND* array);
void dot)strict ARRAYGND* array);

#define MASK_ON(x, y) ( (x) &= ~(0x1 << (y)) )
#define MASK_OFF(x, y) ( (x) |= (0x1 << (y)) )

void
turn_pin(struct GPIO* port_electr,pins_num pin_electr_num, uint8_t state)
{
	if(state)
		port_electr->ODR |= (0x1 << port_electr_num);
	else  
		port_electr->ODR &= ~(1 << port_elect_num);
}

void
light_dig(struct ARRAYGND* array, uint8_t num)
{
	switch (num) {
		case 0:
			dig0();
			break;
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
		default:
			dot();
			break;
	}
	reset_all();
}

void
dig0(struct ARRAYGND* array)
{
	MASK_OFF(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_OFF(array->G->ODR, array->pins_num[5]);
	MASK_OFF(array->H->ODR, array->pins_num[6]);
	MASK_ON(array->DOT->ODR, array->pins_num[7]);
}

void
dig0(struct ARRAYGND* array)
{
	MASK_OFF(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_OFF(array->G->ODR, array->pins_num[5]);
	MASK_OFF(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}

void
dig1(struct ARRAYGND* array)
{
	MASK_OFF(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}

void
dig2(struct ARRAYGND* array)
{
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_ON(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_OFF(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}

void
dig3(struct ARRAYGND* array)
{
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}, 

void
dig4(struct ARRAYGND* array)
}
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}

void
dig5(struct ARRAYGND* array)
}
	MASK_OFF(array->A->ODR, array->pins_num[0]);
	MASK_ON(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	

void
dig6(struct ARRAYGND* array)
}
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_ON(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_ON(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_OFF(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	

void
dig7(struct ARRAYGND* array)
}
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	

void
dig8(struct ARRAYGND* array)
}
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_ON(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_ON(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	

void
dig9(struct ARRAYGND* array)
}
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_ON(array->B->ODR, array->pins_num[1]);
	MASK_ON(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	

void
reset_all(struct ARRAYGND* array)
{
	MASK_OFF(array->A->ODR, array->pins_num[0]);
	MASK_OFF(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_OFF(array->E->ODR, array->pins_num[3]);
	MASK_OFF(array->F->ODR, array->pins_num[4]);
	MASK_OFF(array->G->ODR, array->pins_num[5]);
	MASK_OFF(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}	
