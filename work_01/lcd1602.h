/*
 * lcd1602.h
 *
 *  Created on: 2018��11��16��
 *      Author: Cal
 */
#include"Config.h"

#ifndef LCD1602_H_
#define LCD1602_H_


//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�

//12864/1602Һ�����ƹܽ�
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define EN_CLR          P5OUT &= ~BIT7           //E�õ�
#define EN_SET          P5OUT |=  BIT7           //E�ø�

#define PSB_CLR         P5OUT &= ~BIT0            //PSB�õͣ����ڷ�ʽ
#define PSB_SET         P5OUT |=  BIT0            //PSB�øߣ����ڷ�ʽ

#define RST_CLR         P5OUT &= ~BIT1            //RST�õ�
#define RST_SET         P5OUT |= BIT1             //RST�ø�

void init_1602();
void wc_1602(unsigned char );
void wd_1602(unsigned char);



#endif /* LCD1602_H_ */
