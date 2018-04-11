#include "gpiote.h"
#include "ppi.h"



int main(){

	
	GPIO->CONFIG[n] = (1 << 0);
	GPIO->CONFIG[n] = (1 << 1);


	//configure LEDs
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		if (i<13) {
			GPIO->OUTSET = (1 << i);
		} else {
			GPIO->OUTCLR = (1 << i);
		}
	}




}