/*
 * TFT.h
 *
 *  Created on: 2018��11��1��
 *      Author: Cal
 */

#ifndef TFT_H_
#define TFT_H_
#include <msp430f169.h>
#include"timeConfig.h"

//2.8��TFT������ʾ�������Ӳ������
#define RS_CLR          P5OUT &= ~BIT5           //RS�õ�
#define RS_SET          P5OUT |=  BIT5           //RS�ø�

#define RW_CLR          P5OUT &= ~BIT6           //RW�õ�
#define RW_SET          P5OUT |=  BIT6           //RW�ø�

#define RD_CLR          P5OUT &= ~BIT7           //E�õ�
#define RD_SET          P5OUT |=  BIT7           //E�ø�

#define CS_CLR          P5OUT &= ~BIT0            //CS�õ�
#define CS_SET          P5OUT |=  BIT0            //CS�ø�

#define RST_CLR         P5OUT &= ~BIT3            //RST�õ�
#define RST_SET         P5OUT |=  BIT3            //RST�ø�

#define LE_CLR          P5OUT &= ~BIT1            //LE�õ�
#define LE_SET          P5OUT |=  BIT1            //LE�ø�

//2.8��TFT�����������������Ӳ������
#define PEN_CLR         P2OUT &= ~BIT0           //PEN�õ�,����������ʱ��Penirq������δ����ʱ�ĸߵ�ƽ��Ϊ�͵�ƽ
#define PEN_SET         P2OUT |=  BIT0           //PEN�ø�
#define PEN             (P2IN & 0x01)            //P2.0�����ֵ

#define TPDO_CLR    P2OUT &= ~BIT1           //TPDO�õ�
#define TPDO_SET    P2OUT |=  BIT1           //TPDO�ø�
#define TPDOUT          ((P2IN>>1)&0x01)         //P2.1�����ֵ

#define BUSY_CLR    P2OUT &= ~BIT3           //BUSY�õ�
#define BUSY_SET    P2OUT |=  BIT3           //BUSY�ø�

#define TPDI_CLR    P2OUT &= ~BIT4            //TPDI�õ�
#define TPDI_SET    P2OUT |=  BIT4            //TPDI�ø�

#define TPCS_CLR    P2OUT &= ~BIT5            //TPCS�õ�
#define TPCS_SET    P2OUT |=  BIT5            //TPCS�ø�

#define TPCLK_CLR   P2OUT &= ~BIT6            //TPCLK�õ�
#define TPCLK_SET   P2OUT |=  BIT6            //TPCLK�ø�

//����/12864Һ��/1602Һ�������ݿڣ���Һ������
#define DataDIR         P4DIR                     //���ݿڷ���
#define DataPort        P4OUT                     //P4��Ϊ���ݿ�




void Write_Data(unsigned char,unsigned char);
void  Write_Data_U16(unsigned int y);
void Write_Cmd(unsigned char ,unsigned char);
void Write_Cmd_Data(unsigned char,unsigned int );
void LCD_SetPos(unsigned int ,unsigned int,unsigned int,unsigned int);
void TFT_Initial();

void displayNums(unsigned int ,unsigned int,unsigned char);
void clearNums(unsigned int ,unsigned int,unsigned char);

//��ɫ���룬TFT��ʾ��
#define White          0xFFFF                                                               //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


#endif /* TFT_H_ */
