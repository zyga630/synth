#include "hardware.h"
#

uint8_t state = 0;
#define PIT_IRQn (IRQn_Type) 22
int g=0;
extern uint16_t adc;
extern uint8_t sw_on;
extern uint8_t snd_n;

uint8_t outL, outH; 
uint8_t samples[96]= {152, 176, 199, 218, 234, 246, 253, 255, 253, 
											 246, 234, 218, 199, 176, 152, 128, 103, 79, 56, 
												37, 21, 9, 2, 0, 2, 9, 21, 37, 56, 79, 103, 128,
											144, 160, 176, 192, 208, 224, 240, 255, 240, 224,
											208, 192, 176, 160, 144, 128, 112, 96, 80, 64, 48,
											32, 16, 0, 16, 32, 48, 64, 80, 96, 112, 128,
											169, 193, 211, 224, 235, 244, 252, 255, 252, 244, 
											235, 224, 211, 193, 169, 128, 86, 62, 44, 31, 20, 
											11, 3, 0, 41, 65, 83, 96, 107, 116, 124, 131};

									
void Clock_Init(){
	SystemCoreClockUpdate();
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK ; 	
//	SIM->SCGC5 |= SIM_SCGC5_TSI_MASK;
	
	SIM->SCGC6 |= SIM_SCGC6_DAC0_MASK | SIM_SCGC6_ADC0_MASK;
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
	PORTA->PCR[SEL_SND_SW] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK;
	PORTA->PCR[SEL_EFF_SW] = PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK | PORT_PCR_PFE_MASK;
	
	//DAC
	PORTB->PCR[DAC] = PORT_PCR_MUX(1);
	
	//ADC
	//PORTA->PCR[ADC] |= PORT_PCR_MUX(0);
	
	//TSI
	//PORTA->PCR[13] = PORT_PCR_MUX(0);
//	PORTB->PCR[12] = PORT_PCR_MUX(0);
	
	PTB->PDDR |= 1UL<<RED_LED_PORT;
	PTB->PDDR |= 1UL<<GREEN_LED_PORT;
	PTB->PDDR |= 1UL<<BLUE_LED_PORT;
	
	
	PTB->PSOR |= 1UL << RED;
	PTB->PSOR |= 1UL << GREEN;
	PTB->PSOR |= 1UL << BLUE;
		
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
	
	outL = 0xFF & (uint8_t)samples[32*snd_n + g++];
	outH = 0;//0x0F & (uint8_t)(output>>8);
	
	DAC0->DAT->DATH = outH * sw_on;
	DAC0->DAT->DATL = outL * sw_on;
	PIT->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;  //clear interrupt	
}
/*
void adc_Calibration(void){
	
	uint32_t temp_sum_p;
	uint32_t temp_sum_m;
		
	temp_sum_p = ADC0->CLPD + ADC0->CLPS + ADC0->CLP0 + ADC0->CLP1 + ADC0->CLP2 + ADC0->CLP3 + ADC0->CLP4;
	temp_sum_p /= 2;
	temp_sum_p |= (1UL << 15);
	ADC0->PG = ADC_PG_PG(temp_sum_p);
	
	ADC0->CFG1 |= ADC_CFG1_ADIV(0);																		//divider /1
	ADC0->CFG1 |= ADC_CFG1_MODE(1);																		//12 bit resolution
	NVIC_ClearPendingIRQ(ADC0_IRQn); 	/* Clear any pending interrupt */
/*	NVIC_EnableIRQ(ADC0_IRQn);
	ADC0->SC1[0] |= ADC_SC1_AIEN_MASK | ADC_SC1_ADCH(11);																//active interrupt
	

}


void ADC_Init()
{&/
	/*ADC0->CFG1 |= ADC_CFG1_ADICLK_MASK | ADC_CFG1_ADIV(3) |ADC_CFG1_ADLSMP_MASK;
	ADC0->CFG1 |= ADC_CFG1_ADLPC_MASK;
	ADC0->SC2 |=ADC_SC2_REFSEL_MASK;
	ADC0->SC3|=ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(3);

	ADC0->SC3|=ADC_SC3_CAL_MASK;
*//*
	ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;																//	long sample time
	ADC0->CFG1 |= ADC_CFG1_ADICLK(1);																	//  clk/2 
	ADC0->CFG1 |= ADC_CFG1_ADIV(2);																		//	clk/4 
	
	ADC0->CFG2 |= ADC_CFG2_ADHSC_MASK;																// high f
	ADC0->CFG2 |= ADC_CFG2_ADLSTS(0);																	

	ADC0->SC2 |= ADC_SC2_REFSEL(0);																		//ref clk
	ADC0->SC3 |= ADC_SC3_AVGE_MASK;																		//hardware averaging
	ADC0->SC3 |= ADC_SC3_AVGS(3);																			//hardware averaging max value 32
  ADC0->SC3 |= ADC_SC3_CAL_MASK;																		//clearing calf
	
	while (ADC_SC3_CAL_MASK == (ADC0->SC3 & ADC_SC3_CAL_MASK)){}
		
	if (0 == (ADC0->SC3 & ADC_SC3_CALF_MASK)){
		adc_Calibration();
		}
	else{	// calibration failed
		LED_On(RED);
		while(1);
	}	
}


void ADC0_IRQHandler(void){
		
	adc = ADC0->R[0];
	if(adc>3800) LED_On(RED);
	else LED_Off(RED);
	
}*/

void HW_Init(){
	Clock_Init();
	GPIO_Init();
	PIT_Init();
	DAC_Init();	
//	ADC_Init();
	
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
		

