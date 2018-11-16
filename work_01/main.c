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
        P6OUT |= BIT4;//正转
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
unsigned int count;              //TIMERA中断中变量
unsigned char a;                 //TIMERA中断中变量
unsigned char BIT;               //接收数据位数
unsigned char RECV_FLAG;         //接收到数据的标志位
unsigned char CUR=0;
unsigned char curX=0;
unsigned char nums[10];
unsigned int sum=0;

unsigned char data[33];          //一位引导码+32位数据的数组
unsigned char ircode[4];         //存储两个用户码、一个数据码、一个数据码的反码
unsigned char VALUE;             //全局键值

#pragma vector=PORT1_VECTOR      //端口P1中断
__interrupt void Port1_ISR(void)
{
    //P6OUT |= ((P6OUT&BIT0)?0:1);
    //P6OUT=~P6OUT;
    if(count>32)                 //第一次接收时判断count数量，>32为引导码，
    {
        BIT=0;
    }
    data[BIT] = count;           //每次存储每位数据持续的count个数，一个count为8*33=264us，间接获得下降沿时间间隔
    count = 0;                   //存完清零count个数
    BIT++;
    if(BIT==33)                  //接收33次后（即33个下降沿触发后），清零索引BIT，并将start标志置位
    {
        BIT=0;
        RECV_FLAG=1;
    }
    P1IFG = 0;                   //清除中断标志位
}

#pragma vector=TIMERA0_VECTOR     //TIMERA中断，在达到定时要求时才会产生中断
__interrupt void Timer_A(void)    //此次设置CCR0为33，在1MHz下，约为33us产生一次中断
{
    P6OUT=~P6OUT;
    a++;                          //一次中断，a自增一次
    if(a == 8)                    //a自增8次，即经过约33*8=264us，清零，count++
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
	    //脉冲宽度
	    wc_1602(0x80);
	    wd_1602(width/100+'0');
	    wc_1602(0x81);
	    wd_1602((width%100)/10+'0');
	    wc_1602(0x82);
	    wd_1602(width%10+'0');


	    infrared_decode();       //红外解码
	    //set_value(ircode[2]);    //配置各个按键的键值


	}

	return 0;
}
