
#include "hardware.h"
#include "synth.h"

uint16_t adc=0; 
uint8_t sw_on = 0;
int freq_shift = 1;
int snd_n = 0;
	
int main(void){

	HW_Init();

	while(1){
			
		if (sw_on == 1) {LED_On(GREEN);}
		else LED_Off(GREEN);
		
		if ((FPTB->PDIR & 1UL<<SW0) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/C_NOTE;	
		}
		
		else if ((FPTB->PDIR & 1UL<<SW1) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/C_SHARP_NOTE;	
		}
				
		else if ((FPTB->PDIR & 1UL<<SW2) == 0) {
			sw_on=1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/D_NOTE;	
		}
	
		else if ((FPTB->PDIR & 1UL<<SW3) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/D_SHARP_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW4) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/E_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW5) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/F_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW6) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/F_SHARP_NOTE;			
		}
		
		else if ((FPTB->PDIR & 1UL<<SW7) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/G_NOTE;			
		}
			
		else if ((FPTA->PDIR & 1UL<<SW8) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/G_SHARP_NOTE;			
		}
			
	 else if ((FPTA->PDIR & 1UL<<SW9) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/A_NOTE;			
		}
		
		else if ((FPTA->PDIR & 1UL<<SW10) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/A_SHARP_NOTE;			
		}
		
		else if ((FPTA->PDIR & 1UL<<SW11) == 0) {
			sw_on = 1;
			PIT->CHANNEL[0].LDVAL = freq_shift*REF_FREQ_VALUE/B_NOTE;			
		}
		else sw_on=0;
		
		if ((FPTA->PDIR & 1UL<<SEL_EFF_SW) == 0){
			 if(freq_shift == 1) freq_shift = 2;
			 else freq_shift = 1;
				LED_Toggle(RED);
		}
		
		
		if ((FPTA->PDIR & 1UL<<SEL_SND_SW)==0){
			 snd_n++;
			LED_Toggle(BLUE);
		}	
		
		if (snd_n == 3) snd_n = 0;
		
	}
}