#include <stdint.h>
#include "symbols.h"
#include "basic_mapping.h"
#include "utilites.h"

void reset_all(volatile struct ARRAYGND* array);
void dig0(volatile struct ARRAYGND* array);
void dig1(volatile struct ARRAYGND* array);
void dig2(volatile struct ARRAYGND* array);
void dig3(volatile struct ARRAYGND* array);
void dig4(volatile struct ARRAYGND* array);
void dig5(volatile struct ARRAYGND* array);
void dig6(volatile struct ARRAYGND* array);
void dig7(volatile struct ARRAYGND* array);
void dig8(volatile struct ARRAYGND* array);
void dig9(volatile struct ARRAYGND* array);
void dot(volatile struct ARRAYGND* array);


void
turn_pin(volatile struct GPIO* port_electr,pins_num pin_electr_num, uint8_t state)
{
	if(state)
		port_electr->ODR |= (0x1 << pin_electr_num);
	else  
		port_electr->ODR &= ~(1 << pin_electr_num);
}

void
light_dig(volatile struct ARRAYGND* array, uint8_t num)
{
	switch (num) {
		case 0:
			dig0(array);
			break;
		case 1:
			dig1(array);
			break;
		case 2:
			dig2(array);
			break;
		case 3:
			dig3(array);
			break;
		case 4:
			dig4(array);
			break;
		case 5:
			dig5(array);
			break;
		case 6:
			dig6(array);
			break;
		case 7:
			dig7(array);
			break;
		case 8:
			dig8(array);
			break;
		case 9:
			dig9(array);
			break;
		default:
			dot(array);
			break;
	}
	reset_all(array);
}

void
dot(volatile struct ARRAYGND* array)
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
dig0(volatile struct ARRAYGND* array)
{
	MASK_ON(array->A->ODR, array->pins_num[0]);
	MASK_ON(array->B->ODR, array->pins_num[1]);
	MASK_OFF(array->C->ODR, array->pins_num[2]);
	MASK_ON(array->E->ODR, array->pins_num[3]);
	MASK_ON(array->F->ODR, array->pins_num[4]);
	MASK_ON(array->G->ODR, array->pins_num[5]);
	MASK_ON(array->H->ODR, array->pins_num[6]);
	MASK_OFF(array->DOT->ODR, array->pins_num[7]);
}

void
dig1(volatile struct ARRAYGND* array)
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
dig2(volatile struct ARRAYGND* array)
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
dig3(volatile struct ARRAYGND* array)
{
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
dig4(volatile struct ARRAYGND* array)
{
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
dig5(volatile struct ARRAYGND* array)
{
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
dig6(volatile struct ARRAYGND* array)
{
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
dig7(volatile struct ARRAYGND* array)
{
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
dig8(volatile struct ARRAYGND* array)
{
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
dig9(volatile struct ARRAYGND* array)
{
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
reset_all(volatile struct ARRAYGND* array)
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
