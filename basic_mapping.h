#include <stdint.h>
#include "symbols."

struct GPIO {
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
};

struct RCC_type {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RST;
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t AHB1LPENR;
	volatile uint32_t AHB2LPENR;
	volatile uint32_t APB1LPENR;
	volatile uint32_t APB2LPENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t SSCGR;
	volatile uint32_t PLLI2SCFGR;
	volatile uint32_t DCKCFGR;
};

#define RCC ((struct RCC_type*)0x40023800)
struct SYSCFG_type {
	volatile uint32_t MEMRMP;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR1;
	volatile uint32_t EXTICR2;
	volatile uint32_t EXTICR3;
	volatile uint32_t EXTICR4;
	volatile uint32_t CPMCR;
};

#define SYSCFG ((struct SYSCFG_type*)0x40013000)
struct NVID_type {
	volatile uint32_t ISER[8];
	volatile uint32_t RESERVED0[24];
	volatile uint32_t ICER[8];
	volatile uint32_t RESERVED1[24];
	volatile uint32_t ISPR[8];
	volatile uint32_t RESERVED2[24];
	volatile uint32_t ICPR[8];
	volatile uint32_t RESERVED3[24];
	volatile uint32_t IABR[8];
	volatile uint32_t RESERVED4[56];
	volatile uint32_t IPR[60];
};

#define NVIC ( (struct NVIC_type*)0xE000E100 )

struct STK_type {
	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
};

struct EXTI_type {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
};

#define EXTI ((struct EXTI_type*)0x40013C00)

struct ARRAYGND {
	struct GPIO* A;
	struct GPIO* B;
	struct GPIO* C;
	struct GPIO* E;
	struct GPIO* F;
	struct GPIO* G;
	struct GPIO* H;
	struct GPIO* DOT;
	volatile uint8_t pins_num[8];
};

struct ARRAYELECT {
	struct GPIO* FST;
	struct GPIO* SND;
	struct GPIO* THRD;
	struct GPIO* FRTH;
	volatile pins_num pins_num[4];
};
