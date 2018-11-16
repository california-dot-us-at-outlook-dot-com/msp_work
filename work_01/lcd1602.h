/*
 * lcd1602.h
 *
 *  Created on: 2018年11月16日
 *      Author: Cal
 */
#include"Config.h"

#ifndef LCD1602_H_
#define LCD1602_H_


//彩屏/12864液晶/1602液晶的数据口，三液晶共用
#define DataDIR         P4DIR                     //数据口方向
#define DataPort        P4OUT                     //P4口为数据口

//12864/1602液晶控制管脚
#define RS_CLR          P5OUT &= ~BIT5           //RS置低
#define RS_SET          P5OUT |=  BIT5           //RS置高

#define RW_CLR          P5OUT &= ~BIT6           //RW置低
#define RW_SET          P5OUT |=  BIT6           //RW置高

#define EN_CLR          P5OUT &= ~BIT7           //E置低
#define EN_SET          P5OUT |=  BIT7           //E置高

#define PSB_CLR         P5OUT &= ~BIT0            //PSB置低，串口方式
#define PSB_SET         P5OUT |=  BIT0            //PSB置高，并口方式

#define RST_CLR         P5OUT &= ~BIT1            //RST置低
#define RST_SET         P5OUT |= BIT1             //RST置高

void init_1602();
void wc_1602(unsigned char );
void wd_1602(unsigned char);



#endif /* LCD1602_H_ */
