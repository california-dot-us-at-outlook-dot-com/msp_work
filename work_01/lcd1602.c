/*
 * lcd1602.c
 *
 *  Created on: 2018Äê11ÔÂ16ÈÕ
 *      Author: Cal
 */

#include"lcd1602.h"


void wd_1602(unsigned char data){
    RS_SET;
    RW_CLR;
    EN_SET;
    DataPort=data;
    delay_ms(5);
    EN_CLR;
}

void wc_1602(unsigned char data){
    RS_CLR;
    RW_CLR;
    EN_SET;
    DataPort=data;
    delay_ms(5);
    EN_CLR;
}

void init_1602(void){
    P5DIR |= (BIT5+BIT6+BIT7);
    P4DIR |=0xff;
    wc_1602(0x38);
    delay_ms(5);
    wc_1602(0x08);
    delay_ms(5);
    wc_1602(0x01);
    delay_ms(5);
    wc_1602(0x06);
    delay_ms(5);
    wc_1602(0x0c);
    delay_ms(5);
}

