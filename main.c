
#include "hardware.h"
#include "synth.h"



int main(void){

	HW_Init();

//	enum LedColours color = RED;
	LED_Off(RED);
	LED_Off(GREEN);
	LED_Off(BLUE);
	
	uint16_t output; 
	uint8_t outL, outH; 
	
	int dir = 30000; 
 
	while(1){
	/*	if ((FPTB->PDIR & 1UL<<SW0) == 0) {
		
			LED_On(RED);
			dir = 3000;
		
		}
		else LED_Off(RED);
		if ((FPTB->PDIR & 1UL<<SW1) == 0) {
		
			LED_On(GREEN);
			dir = 8000;
		}
		else LED_Off(GREEN);
		if ((FPTB->PDIR & 1UL<<SW2) == 0) {
		
			LED_On(BLUE);
			dir = 500;
		}
		else LED_Off(BLUE);*/
	
	///	 output++;
	//	if (output >=4096) output = 0;
		
	//	outL = 0xFF & (uint8_t)output;
	//	outH = 0x0F & (uint8_t)(output>>8);
	//	DAC0->DAT->DATH = outH;
	//	DAC0->DAT->DATL = outL;
	//	int i = dir;
	//	while(0 < i--);
		
	}
}
