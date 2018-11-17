/*
 * Touch.h
 *
 *  Created on: 2018��11��15��
 *      Author: Cal
 */

#ifndef TOUCH_H_
#define TOUCH_H_

#include"timeConfig.h"


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


struct struct1                          //����һ��������Ϊstruct1�Ľṹ,����������Աx��y
{
    unsigned int x;                         //��Աx
    unsigned int y;                         //��Աy
};

#define Xmin           0x0133
#define Xmax           0x0EDA
#define Ymin           0x00D0
#define Ymax           0x0E2F

extern struct struct1 coordinate;      //����һ����ΪTp_pix�Ľṹ����,���ڴ�Ŵ����Ĵ����������
//extern unsigned int  ltx,lty;

void start_7843();
void Write_7843(unsigned char temp);          //SPIд8λ�����������IC
unsigned int Read_7843();                     //SPI ������
struct struct1 AD7843() ;
unsigned char pix_filter(struct struct1 pix1,struct struct1 pix2);
unsigned char Getpix();
void Detect_TP(void);

unsigned int  ltx,lty;            //���ݲɼ����Ĳ���ת��ΪTFT�ϵ�ʵ������ֵ
unsigned int LCD_X,LCD_Y;

/*������ť��״̬��־λ*/
unsigned char   Button_Flag;          //�������±�־

unsigned char   Button_11;                    //��һ�е�һ�а�ť
unsigned char   Button_12;
unsigned char   Button_13;

unsigned char   Button_21;                //�ڶ��е�һ�а�ť
unsigned char   Button_22;
unsigned char   Button_23;

unsigned char   Button_31;                //�����е�һ�а�ť
unsigned char   Button_32;
unsigned char   Button_33;

unsigned char   Button_41;                    //�����е�һ�а�ť
unsigned char   Button_42;
unsigned char   Button_43;

unsigned char   Button_Back;                  //�˸�ť
unsigned char   Button_Clear;                 //�����ť



#define xs(j)   (j*60+15*j+15)                    //��ť���������
#define ys(i)   (80+i*50+10*i)                                      //��ť���������
#define xe(j)   (j*60+15*j+15+60)                 //��ť�������յ�
#define ye(i)   (80+i*50+10*i+50)                //��ť�������յ�


#endif /* TOUCH_H_ */
