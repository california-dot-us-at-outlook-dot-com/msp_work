/*
 * interrupt.h
 *
 *  Created on: 2018��11��13��
 *      Author: Cal
 */
#include<msp430.h>
#include"Config.h"

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

void interrupt_init(unsigned char PORT,unsigned char port,unsigned char down);//PORT:ѡ��P1����P2; port:0-255(1-8); down:������ʽΪ�½��صĿڣ�0-255��1-8��

/*
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
    P6OUT=~P6OUT;
    P1IFG &= 0;
}


#pragma vector = PORT2_VECTOR
__interrupt void Port2_ISR(void){
    P6OUT=~P6OUT;
    P2IFG &= 0;
}
*/


#endif /* INTERRUPT_H_ */
