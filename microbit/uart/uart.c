#include "uart.h"
#include "gpio.h"
#include <stdint.h>

#define UART ((NRF_UART_REG*)0x40002000)

typedef struct {
    volatile uint32_t STARTRX;
    volatile uint32_t STOPRX;
    volatile uint32_t STARTTX;
    volatile uint32_t STOPTX;
    volatile uint32_t RESERVED0[3];
    volatile uint32_t SUSPEND;
    volatile uint32_t RESERVED1[56];
    volatile uint32_t CTS;
    volatile uint32_t NCTS;
    volatile uint32_t RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t TXDRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t RXTO;
    volatile uint32_t RESERVED5[110];
    volatile uint32_t INTEN;
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED6[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED7[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED8[1];
    volatile uint32_t PSELRTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD;
    volatile uint32_t RESERVED9[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED10[17];
    volatile uint32_t CONFIG;
} NRF_UART_REG;

void uart_init(){
    int TXD_pin = 24;
    int RXD_pin = 25;
    GPIO->PIN_CNF[TXD_pin] = 1; //output
	GPIO->PIN_CNF[RXD_pin] = 0; //input
    UART->BAUDRATE = 0x00275000;
    UART->CONFIG = (1 << 0);

    UART->ENABLE = 0x4;
    UART->STARTRX = (1 << 0);
}

void uart_send(char letter){
    //noe med TXDRDY 
    //while noe med TXD? <4?
}