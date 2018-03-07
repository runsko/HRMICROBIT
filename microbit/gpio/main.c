#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;



void setLED(int col, int row){
	GPIO->OUTCLR = (1 << col);
	GPIO->OUTSET = (1 << row);
}

void resetLED(int col, int row){
	GPIO->OUTSET = (1 << col);
	GPIO->OUTCLR = (1 << row);
}

int main(){
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

	int sleep = 0;



	while(1){

		int buttonA = !((GPIO->IN)&(1<<buttonPinA));
		int buttonB = !((GPIO->IN)&(1<<buttonPinB));

		/* Check if button B is pressed;
		 * turn on LED matrix if it is. */
		if(buttonB){
			for(int i = 4; i <= 12; i++){
				for(int j = 13; j<= 15;j++){
					setLED(i,j);
				}
			}
		} else if (buttonA){
			for(int i = 4; i <= 12; i++){
				for(int j = 13; j<= 15;j++){
					resetLED(i,j);
				}
			}
		}


		/* Check if button A is pressed;
		 * turn off LED matrix if it is. */

		sleep = 10000;
		while(--sleep);
	}
	return 0;
}


