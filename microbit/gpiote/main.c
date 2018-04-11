#include "gpiote.h"
#include "ppi.h"
#include "gpio.h"



int main(){

	//configure LEDs
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure A-button event
	GPIOTE->CONFIG[0] = (2 << 16) | (17 << 8) | 1; // POLARITY = HiToLo | PSEL = 17 | MODE = Event
	
	// Configure led-pin tasks
	GPIOTE->CONFIG[1] = (1 << 20) | (3 << 16) | (13 << 8) | 3; // OUTINIT = 1 | POLARITY = Toggle | PSEL = 13 | MODE = Task
    GPIOTE->CONFIG[2] = (1 << 20) | (3 << 16) | (14 << 8) | 3; // OUTINIT = 1 | POLARITY = Toggle | PSEL = 14 | MODE = Task
   	GPIOTE->CONFIG[3] = (1 << 20) | (3 << 16) | (15 << 8) | 3; // OUTINIT = 1 | POLARITY = Toggle | PSEL = 15 | MODE = Task


	PPI->PPI_CH[0].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[0].TEP = (uint32_t)&(GPIOTE->OUT[1]);

	PPI->PPI_CH[1].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[1].TEP = (uint32_t)&(GPIOTE->OUT[2]);

	PPI->PPI_CH[2].EEP = (uint32_t)&(GPIOTE->IN[0]);
	PPI->PPI_CH[2].TEP = (uint32_t)&(GPIOTE->OUT[3]);

	PPI->CHENSET = 1 | (1 << 1) | (1 << 2);

	while(1);
	return 0;
}