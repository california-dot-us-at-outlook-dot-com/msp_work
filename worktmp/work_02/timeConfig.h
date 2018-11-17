/*
 * timeConfig.h
 *
 *  Created on: 2018��10��31��
 *      Author: Cal
 */
#include<msp430f169.h>
#ifndef TIMECONFIG_H_
#define TIMECONFIG_H_

#define CPU_F ((double)8000000)   //�ⲿ��Ƶ����8MHZ
//#define CPU_F ((double)32768)   //�ⲿ��Ƶ����32.768KHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))

void Clock_Init();


#endif /* TIMECONFIG_H_ */
