
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
	
 uint32_t input;	
 uint16_t button;
	while(1){
		
		if (sw_on == 1) {LED_On(GREEN);}
		else LED_Off(GREEN);
		
		if ((FPTB->PDIR & 1UL<<SW0) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/C_NOTE;	
		}
		
		else if ((FPTB->PDIR & 1UL<<SW1) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/C_SHARP_NOTE;	
		}
				
		else if ((FPTB->PDIR & 1UL<<SW2) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/D_NOTE;	
		}
	
		else if ((FPTB->PDIR & 1UL<<SW3) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/D_SHARP_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW4) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/E_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW5) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/F_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW6) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/F_SHARP_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW7) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/G_NOTE;			
		}
			
		else if ((FPTA->PDIR & 1UL<<SW8) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/G_SHARP_NOTE;			
		}
			
	 else if ((FPTA->PDIR & 1UL<<SW9) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/A_NOTE;			
		}
		
		else if ((FPTA->PDIR & 1UL<<SW10) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/A_SHARP_NOTE;			
		}
		
		else if ((FPTA->PDIR & 1UL<<SW11) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = REF_FREQ_VALUE/B_NOTE;			
		}
		else sw_on=0;

	}
}
