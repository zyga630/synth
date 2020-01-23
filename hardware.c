#include "hardware.h"

uint8_t state = 0;
#define PIT_IRQn (IRQn_Type) 22

void Clock_Init(){
	SystemCoreClockUpdate();
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 	
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

void GPIO_Init(){
	
	//outputs
	PORTB->PCR[RED_LED_PORT] = PORT_PCR_MUX(1UL);
	PORTB->PCR[GREEN_LED_PORT] = PORT_PCR_MUX(1UL);	
	PORTB->PCR[BLUE_LED_PORT] = PORT_PCR_MUX(1UL);
	
	//inputs
	PORTB->PCR[SW0] = PORT_PCR_MUX(1);
	PORTB->PCR[SW1] = PORT_PCR_MUX(1);
	PORTB->PCR[SW2] = PORT_PCR_MUX(1);
	
	//DAC
	PORTB->PCR[DAC] = PORT_PCR_MUX(1);
	
	PTB->PDDR |= 1UL<<RED_LED_PORT;
	PTB->PDDR |= 1UL<<GREEN_LED_PORT;
	PTB->PDDR |= 1UL<<BLUE_LED_PORT;
}
void DAC_Init(){
	//Enable DAC, Set Reference Voltage
	DAC0->C0 |= DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;		
}

void PIT_Init(){
	PIT->CHANNEL[0].LDVAL = 11990000;										//interrupt after ~500ms
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);


	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;	
	PIT->MCR = 0x00;
	
}

void PIT_IRQHandler(){
	switch(state){
		case 0:
			LED_On(RED);
			state = 1;
		break;
		case 1:
			LED_Off(RED);
			state = 0;
		break;					
	}
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;  //clear interrupt	
}

void HW_Init(){
	Clock_Init();
	GPIO_Init();
	PIT_Init();
	DAC_Init();	
}

void LED_On(enum LedColours colour){
	PTB->PCOR |= 1UL << colour;
}

void LED_Off(enum LedColours colour){
	PTB->PSOR |= 1UL << colour;
}

void LED_Toggle(enum LedColours colour){
	PTB->PTOR |= 1UL << colour;
}
