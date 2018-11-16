/*
 * interrupt.c
 *
 *  Created on: 2018��11��13��
 *      Author: Cal
 */
#include"interrupt.h"


void interrupt_init(unsigned char PORT,unsigned char port,unsigned char down){
    if(PORT==1){
        //P1 init
        P1DIR &= (~port);
        P1IES |= down; //0:�����أ�    1���½���
        P1IE |= port;  //�ж�����1Ϊ����
        P1IFG &= (~port);  //�жϱ�־��0Ϊ�ɽ����ж�
        _EINT();    //�������ж�
    }else if(PORT==2){
        //P2 init
                P2DIR &= (~port);
                P2IES |= down; //0:�����أ�    1���½���
                P2IE |= port;  //�ж�����1Ϊ����
                P2IFG &= (~port);  //�жϱ�־��0Ϊ�ɽ����ж�
                _EINT();    //�������ж�
    }
}
