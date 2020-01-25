#include "hardware.h"

uint8_t state = 0;
#define PIT_IRQn (IRQn_Type) 22
int g=0;
extern uint8_t sw_on;

uint8_t outL, outH; 
uint8_t samples[32] = {152, 176, 199, 218, 234, 246, 253, 255, 253, 
											 246, 234, 218, 199, 176, 152, 128, 103, 79,
											 56, 37, 21, 9, 2, 0, 2, 9, 21, 37, 56, 79,
											103, 128};

void Clock_Init(){
	SystemCoreClockUpdate();
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK ; 	
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

void GPIO_Init(){
	
	//outputs
	PORTB->PCR[RED_LED_PORT] = PORT_PCR_MUX(1UL);
	PORTB->PCR[GREEN_LED_PORT] = PORT_PCR_MUX(1UL);	
	PORTB->PCR[BLUE_LED_PORT] = PORT_PCR_MUX(1UL);
	
	//inputs
	PORTB->PCR[SW0] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW2] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW4] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW5] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
	PORTB->PCR[SW6] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW7] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW8] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW9] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW10] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW11] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	//DAC
	PORTB->PCR[DAC] = PORT_PCR_MUX(1);
	
	PTB->PDDR |= 1UL<<RED_LED_PORT;
	PTB->PDDR |= 1UL<<GREEN_LED_PORT;
	PTB->PDDR |= 1UL<<BLUE_LED_PORT;
	
	#include "hardware.h"

uint8_t state = 0;
#define PIT_IRQn (IRQn_Type) 22
int g=0;
extern uint8_t sw_on;

uint8_t outL, outH; 
uint8_t samples[32] = {152, 176, 199, 218, 234, 246, 253, 255, 253, 
											 246, 234, 218, 199, 176, 152, 128, 103, 79,
											 56, 37, 21, 9, 2, 0, 2, 9, 21, 37, 56, 79,
											103, 128};

void Clock_Init(){
	SystemCoreClockUpdate();
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK ; 	
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK | SIM_SCGC6_ADC0_MASK;
	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;
}

void GPIO_Init(){
	
	//outputs
	PORTB->PCR[RED_LED_PORT] = PORT_PCR_MUX(1UL);
	PORTB->PCR[GREEN_LED_PORT] = PORT_PCR_MUX(1UL);	
	PORTB->PCR[BLUE_LED_PORT] = PORT_PCR_MUX(1UL);
	PORTA->PCR[ADC]= PORT_PCR_MUX(0);
	
	//inputs
	PORTB->PCR[SW0] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW1] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW2] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW3] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW4] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW5] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;	
	PORTB->PCR[SW6] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTB->PCR[SW7] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW8] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW9] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW10] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	PORTA->PCR[SW11] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK;
	
	//DAC
	PORTB->PCR[DAC] = PORT_PCR_MUX(1);
	
	PTB->PDDR |= 1UL<<RED_LED_PORT;
	PTB->PDDR |= 1UL<<GREEN_LED_PORT;
	PTB->PDDR |= 1UL<<BLUE_LED_PORT;
	
	//ADC
	PTA->PDDR |= 1UL<<ADC;
	
}
void DAC_Init(){
	//Enable DAC, Set Reference Voltage
	DAC0->C0 |= DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;		
}

void PIT_Init(){
	PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/1000;										//
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);

	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;	
	PIT->MCR = 0x00;
	
}

void PIT_IRQHandler(){
	
	if (g == 32) g = 0;
	
		outL = 0xFF & (uint8_t)samples[g++];
		outH = 0;//0x0F & (uint8_t)(output>>8);
		
	
	DAC0->DAT->DATH = outH * sw_on;
	DAC0->DAT->DATL = outL * sw_on;
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;  //clear interrupt	
}

void HW_Init(){
	Clock_Init();
	GPIO_Init();
	PIT_Init();
	DAC_Init();	
}

void ADC_Init()
{
	ADC0->CFG1 |= ADC_CFG1_ADICLK_MASK | ADC_CFG1_ADIV(3) |ADC_CFG1_ADLSMP_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADLPC_MASK;
	ADC0->SC2 |=ADC_SC2_REFSEL_MASK;
	ADC0->SC3|=ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);

	ADC0->SC3|=ADC_SC3_CAL_MASK;
	
	while (ADC_SC3_CAL_MASK==0);
	
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

}
void DAC_Init(){
	//Enable DAC, Set Reference Voltage
	DAC0->C0 |= DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;		
}

void PIT_Init(){
	PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/1000;										//
	
	NVIC_ClearPendingIRQ(PIT_IRQn);
	NVIC_EnableIRQ(PIT_IRQn);

	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK | PIT_TCTRL_TEN_MASK;	
	PIT->MCR = 0x00;
	
}

void PIT_IRQHandler(){
	
	if (g == 32) g = 0;
	
		outL = 0xFF & (uint8_t)samples[g++];
		outH = 0;//0x0F & (uint8_t)(output>>8);
		
	
	DAC0->DAT->DATH = outH * sw_on;
	DAC0->DAT->DATL = outL * sw_on;
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
