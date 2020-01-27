#include <MKL05Z4.h>

#define RED_LED_PORT 	8
#define GREEN_LED_PORT 9
#define BLUE_LED_PORT 10
// 0 2 3 4 5 6 7 11 13
#define SW0 0
#define SW1 2
#define SW2 3
#define SW3 4
#define SW4 5
#define SW5 6
#define SW6 7
#define SW7 11
#define SW8 9
#define SW9 5
#define SW10 6
#define SW11 11
#define SEL_EFF_SW 10
#define SEL_SND_SW 8


#define ADC 0
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

void Touch_Init(void);

void PIT_IRQHandler(void);

void HW_Init(void);

int Touch_Scan_LH(void);

int Touch_Scan_HL(void);

void LED_On(enum LedColours colour);

void LED_Off(enum LedColours colour);

void LED_Toggle(enum LedColours colour);

void ADC_Init(void);