//#include <msp430.h>
#include"lcd1602.h"
#include"interrupt.h"
#include"inf.h"

unsigned int width=80;
unsigned int paused=0;

/*
#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
    if(!(P1IN&BIT0)){
        width+=5;
    }else if(!(P1IN&BIT1)){
        width-=5;
    }else{
        P6OUT |= BIT4;//��ת
        P6OUT &=(~BIT6);
        for(paused=0;paused<width;paused++){
            delay_ms(1);
        }
        P6OUT &=(~BIT4);
        P6OUT=0xff;
    }

    P1IFG &= 0;

}
*/
unsigned int count;              //TIMERA�ж��б���
unsigned char a;                 //TIMERA�ж��б���
unsigned char BIT;               //��������λ��
unsigned char RECV_FLAG;         //���յ����ݵı�־λ
unsigned char CUR=0;
unsigned char curX=0;
unsigned char nums[10];
unsigned int sum=0;

unsigned char data[33];          //һλ������+32λ���ݵ�����
unsigned char ircode[4];         //�洢�����û��롢һ�������롢һ��������ķ���
unsigned char VALUE;             //ȫ�ּ�ֵ

#pragma vector=PORT1_VECTOR      //�˿�P1�ж�
__interrupt void Port1_ISR(void)
{
    //P6OUT |= ((P6OUT&BIT0)?0:1);
    //P6OUT=~P6OUT;
    if(count>32)                 //��һ�ν���ʱ�ж�count������>32Ϊ�����룬
    {
        BIT=0;
    }
    data[BIT] = count;           //ÿ�δ洢ÿλ���ݳ�����count������һ��countΪ8*33=264us����ӻ���½���ʱ����
    count = 0;                   //��������count����
    BIT++;
    if(BIT==33)                  //����33�κ󣨼�33���½��ش����󣩣���������BIT������start��־��λ
    {
        BIT=0;
        RECV_FLAG=1;
    }
    P1IFG = 0;                   //����жϱ�־λ
}

#pragma vector=TIMERA0_VECTOR     //TIMERA�жϣ��ڴﵽ��ʱҪ��ʱ�Ż�����ж�
__interrupt void Timer_A(void)    //�˴�����CCR0Ϊ33����1MHz�£�ԼΪ33us����һ���ж�
{
    P6OUT=~P6OUT;
    a++;                          //һ���жϣ�a����һ��
    if(a == 8)                    //a����8�Σ�������Լ33*8=264us�����㣬count++
    {
        a = 0;
        count++;
    }
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
	//interrupt_init(1,0b00000111,0b00000111);
	interrupt_init(1,0b00000001,0b00000001);
	init_device();
	nums[9]='\0';
	while(1){
	    //������
	    wc_1602(0x80);
	    wd_1602(width/100+'0');
	    wc_1602(0x81);
	    wd_1602((width%100)/10+'0');
	    wc_1602(0x82);
	    wd_1602(width%10+'0');


	    infrared_decode();       //�������
	    //set_value(ircode[2]);    //���ø��������ļ�ֵ


	}

	return 0;
}
