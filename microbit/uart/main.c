#include "uart.h"
#include "gpio.h"
#include <stdio.h>


void toggle_leds(){
	static int ledsOn;
	if(ledsOn){ //turn off leds
		for(int i = 4; i <= 12; i++){
			for(int j = 13; j<= 15;j++){
				GPIO->OUTSET = (1 << i);
				GPIO->OUTCLR = (1 << j);
			}
		}
		ledsOn = 0;
	}
	else{ //turn on leds
		for(int i = 4; i <= 12; i++){
			for(int j = 13; j<= 15;j++){
				GPIO->OUTCLR = (1 << i);
				GPIO->OUTSET = (1 << j);
			}
		}
		ledsOn = 1;
	}
}

//funksjon gitt av oppgavetekst
ssize_t _write(int fd, const void *buf, size_t count){
	char * letter = (char *)(buf);
	for(int i = 0; i < count; i++){
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main() {
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

	//skriver bare ut i det vi kjører make flash, 
	//så blir ikke skrevet ut når vi kjører picocom 
	//fordi da har vi allerede sendt alt til microbiten for "lenge" siden
	iprintf("Norway has %d counties.\n\r", 18); 


	while(1){

		int buttonA = !((GPIO->IN)&(1<<buttonPinA));
		int buttonB = !((GPIO->IN)&(1<<buttonPinB));

		if(uart_read() != '\0'){
			toggle_leds();
			
		}


		if(buttonA){
            uart_send('A');
        }
        if(buttonB){
            uart_send('B');
        }
	}
	return 0;

}