
#include "hardware.h"
#include "synth.h"

	int i = 100;
	uint8_t j; 
	uint8_t sw_on = 0;
//	int g = 0;
//uint8_t outL, outH; 
//uint8_t samples[32] = {152, 176, 199, 218, 234, 246, 253, 255, 253, 
//											 246, 234, 218, 199, 176, 152, 128, 103, 79,
//											 56, 37, 21, 9, 2, 0, 2, 9, 21, 37, 56, 79,
//											103, 128};
int main(void){

	HW_Init();

	LED_Off(RED);
	LED_Off(GREEN);
	LED_Off(BLUE);
	
	uint16_t output; 
	
	while(1){
			
	
		
		 if ((FPTB->PDIR & 1UL<<SW0) == 0) {
			sw_on = 1;
			LED_On(RED);
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/C_NOTE;			
		}
		else {
			LED_Off(RED);
			sw_on=0;
		}
		if ((FPTB->PDIR & 1UL<<SW1) == 0) {
		sw_on=0;
			LED_On(GREEN);
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/E_NOTE;	
		}
		else LED_Off(GREEN);
		if ((FPTB->PDIR & 1UL<<SW2) == 0) {
		
			LED_On(BLUE);
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/G_NOTE;	
			
			
		}
		else LED_Off(BLUE);
	

	}
}
