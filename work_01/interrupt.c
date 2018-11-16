/*
 * interrupt.c
 *
 *  Created on: 2018年11月13日
 *      Author: Cal
 */
#include"interrupt.h"


void interrupt_init(unsigned char PORT,unsigned char port,unsigned char down){
    if(PORT==1){
        //P1 init
        P1DIR &= (~port);
        P1IES |= down; //0:上升沿；    1：下降沿
        P1IE |= port;  //中断允许，1为允许
        P1IFG &= (~port);  //中断标志，0为可接受中断
        _EINT();    //开启总中断
    }else if(PORT==2){
        //P2 init
                P2DIR &= (~port);
                P2IES |= down; //0:上升沿；    1：下降沿
                P2IE |= port;  //中断允许，1为允许
                P2IFG &= (~port);  //中断标志，0为可接受中断
                _EINT();    //开启总中断
    }
}
