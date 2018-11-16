//#include <msp430.h>
#include"lcd1602.h"
#include"interrupt.h"


unsigned int width=80;
unsigned int paused=0;


#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
    if(!(P1IN&BIT0)){
        width+=5;
    }else if(!(P1IN&BIT1)){
        width-=5;
    }else{
        P6OUT |= BIT4;//Õý×ª
        P6OUT &=(~BIT6);
        for(paused=0;paused<width;paused++){
            delay_ms(1);
        }
        P6OUT &=(~BIT4);
        P6OUT=0xff;
    }

    P1IFG &= 0;

}

/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clock_Init();
	
	P6DIR=0xff;
	P6OUT=0xff;
	P1DIR=0x00;
	init_1602();
	interrupt_init(1,0b00000111,0b00000111);
	while(1){
	    //Âö³å¿í¶È
	    wc_1602(0x80);
	    wd_1602(width/100+'0');
	    wc_1602(0x81);
	    wd_1602((width%100)/10+'0');
	    wc_1602(0x82);
	    wd_1602(width%10+'0');


	}

	return 0;
}
