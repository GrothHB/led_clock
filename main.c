#include <stdint.h>
#define GPIOA_BASE 0x40020000
#define GPIOA_MODER (GPIOA_BASE + 0x00)
#define GPIOA_ODR (GPIOA_BASE + 0x14)
#define RCC_BASE 0x40023800
#define RCC_AHB1ENR (RCC_BASE + 0x30)
#define GPIOA_PUPDR (GPIOA_BASE + 0x0C)
#define SYSCFG_BASE 0x40013000
#define SYSCFG_EXTICR2 (SYSCFG_BASE + 0x0C) /* Odbieranie sygnalu z PA[x] */
#define NVIC_BASE 0xE000E000
#define NVIC_ISER0 (NVIC_BASE + 0x100)
#define EXTI 0x40013C00
#define EXTI_IMR (EXTI + 0x00) /* do otwarcia maski, 1 na 4 bit.*/
#define EXTI_RTSR (EXTI + 0x08) /* wlacza wlacznik, 1 na 4 bit */
#define EXTI_PR (EXTI + 0x14)
#define RCC_APB2ENR (RCC_BASE + 0x44)

struct ARRAYGND {
	struct GPIO* A;
	struct GPIO* B;
	struct GPIO* C;
	struct GPIO* E;
	struct GPIO* F;
	struct GPIO* G;
	struct GPIO* H;
	struct GPIO* DOT;
	volatile uint8_t pins_num[7];
};

volatile unsigned int krok_czasowy = 50000;
volatile unsigned int ilosc_wcisniec = 0;
volatile unsigned int ostatnie_wcisniecie;
volatile unsigned int czas_systemu;

int main(void)
{
	volatile unsigned int i;
	*(volatile unsigned int*)RCC_AHB1ENR |= (1 << 0);
	*(volatile unsigned int*)GPIOA_MODER &= ~(1 << 11);
	*(volatile unsigned int*)GPIOA_MODER |= (1 << 10);
	*(volatile unsigned int*)GPIOA_MODER &= ~(3 << 8);
	*(volatile unsigned int*)GPIOA_PUPDR &= ~(1 << 8);
	*(volatile unsigned int*)GPIOA_PUPDR |= (1 << 9);
	*(volatile unsigned int*)RCC_APB2ENR |= (1 << 14);
	*(volatile unsigned int*)SYSCFG_EXTICR2 &= ~(0xF);
	*(volatile unsigned int*)EXTI_IMR |= (1 << 4);
	*(volatile unsigned int*)EXTI_RTSR |= (1 << 4);
	*(volatile unsigned int*)NVIC_ISER0 |= (1 << 10);

	while(1) {
		*(volatile unsigned int*)GPIOA_ODR |= (1 << 5);
		for(i = 0; i < 10000; ++i) {
			;
		}
		*(volatile unsigned int*)GPIOA_ODR &= ~(1 << 5);
		for(i = 0; i < 10000; ++i) {
			;
		}
	}
	return 0;
}	

void change_diod(void)
{
	/* volatile unsigned int i;
	krok_czasowy += 50000;
	if(krok_czasowy == 10000) {
		*(volatile unsigned int*)GPIOA_ODR &= ~(1 << 5);
	}
	else krok_czasowy = 50000;
	for(i = 0; i< 5000000; ++i) {
		;
	}
	*(volatile unsigned int*)EXTI_PR |= (1 << 4);
	for(i =0; i < 5000; ++i) {
		;
	} */
	++ilosc_wcisniec;
	*(volatile unsigned int*)EXTI_PR |= (1 << 4);
}
