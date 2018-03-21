#include "uart.h"
#include <stdio.h>

int main() {
    printf("mainfil start");

    // Configure LED Matrix
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		if (i<13) {
			GPIO->OUTSET = (1 << i);
		} else {
			GPIO->OUTCLR = (1 << i);
		}
	}

	int buttonPinA = 17;
	int buttonPinB = 26;
	
	// Configure buttons
	GPIO->PIN_CNF[buttonPinA] = 0;
	GPIO->PIN_CNF[buttonPinB] = 0;


	uart_init();


	while(1){

		int buttonA = !((GPIO->IN)&(1<<buttonPinA));
		int buttonB = !((GPIO->IN)&(1<<buttonPinB));

		if(buttonA){
            uart_send('A');
        }
        if(buttonB){
            uart_send('B');
        }
	}
	return 0;

}