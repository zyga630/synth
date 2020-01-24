#include <MKL05Z4.h>

#define RED_LED_PORT 	8
#define GREEN_LED_PORT 9
#define BLUE_LED_PORT 10
// 0 2 3 4 5 6 7 11 13
#define SW0 0
#define SW1 3
#define SW2 4

#define DAC 1
#define REF_FREQ_VALUE 23400 * 32

enum LedColours{
	RED = 8,
	GREEN = 9, 
	BLUE = 10,
};

void Clock_Init(void);

void GPIO_Init(void);

void PIT_Init(void);

void PIT_IRQHandler(void);

void HW_Init(void);

void LED_On(enum LedColours colour);

void LED_Off(enum LedColours colour);

void LED_Toggle(enum LedColours colour);
