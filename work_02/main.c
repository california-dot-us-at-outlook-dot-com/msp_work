#include <msp430.h>
#include"timeConfig.h"
#include"Touch.h"
#include"TFT.h"
#include"GUI.h"
#include"Tuoluoyi.h"
#include"interrupt.h"

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
    P3OUT |=(BIT0);
    P1IFG &= 0;
}
/**
 * main.c
 */

    unsigned char pausedNums[8];
    unsigned char Distance=0;
    unsigned char curX=0;
    unsigned char ifPaused=1;
    unsigned char tmpNum=0;
    unsigned char ready=0;
    unsigned char suitAngle=0;


unsigned long pow10(unsigned char pow){
    unsigned char i=0;
    unsigned char result=1;
    for(i=0;i<pow;i++){
        result*=10;
    }
    return result;
}

void DistanceMatch(){

    P6OUT=~P6OUT;
    P3OUT &= (~BIT0);
    delay_ms(1000);
    P3OUT |=(BIT0);
}

void findNum(){
    ifPaused=1;
    if(Button_11){//0
        tmpNum=0;
        Button_11=0;
        curX++;
    }else if(Button_12){//1
        tmpNum=1;
        Button_12=0;
        curX++;
    }else if(Button_13){//2
        tmpNum=2;
        Button_13=0;
        curX++;
    }else if(Button_21){//3
        tmpNum=3;
        Button_21=0;
        curX++;
    }else if(Button_22){//4
        tmpNum=4;
        Button_22=0;
        curX++;
    }else if(Button_23){//5
        tmpNum=5;
        Button_23=0;
        curX++;
    }else if(Button_31){//6
        tmpNum=6;
        Button_31=0;
        curX++;
    }else if(Button_32){//7
        tmpNum=7;
        Button_32=0;
        curX++;
    }else if(Button_33){//8
        tmpNum=8;
        Button_33=0;
        curX++;
    }else if(Button_41){//9
        tmpNum=9;
        Button_41=0;
        curX++;
    }else if(Button_42){//.
        tmpNum=10;
        Button_42=0;
        Distance=0;
        ifPaused=0;
        for(curX=0;curX<16;curX++){
            displayNums(10+curX*10,30,16);
        }
        curX=0;
    }
    /*
    else if(Button_43 && (!ready)){//V
        tmpNum=11;
        Button_43=0;
        ifPaused=0;
        unsigned char tmpCurX=curX;
        for(;curX>0;curX--){
            Distance+=pausedNums[curX]*pow10(tmpCurX-curX);
        }
        P6OUT=Distance;

        displayNums(10,0,18);
        displayNums(20,0,19);
        ready=1;
//        Distance=0;
    }
    */
    else if(Button_43){//V
        DistanceMatch();
        displayNums(10,0,16);
        displayNums(20,0,16);
        Button_43=0;
        ready=0;
        Distance=0;
        ifPaused=0;
        for(curX=0;curX<16;curX++){
            displayNums(10+curX*10,30,16);
        }
        curX=0;
    }else{

        tmpNum=0;
        ifPaused=0;
    }

}



int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer


	P6DIR=0xff;
//	P6OUT=abs(3);

	Clock_Init();
	P3DIR |= BIT0;
	P3OUT |= BIT0;
	UART_Init();                        //串口设置初始化
	interrupt_init(1,0b00000011,0b00000011);//P1.0  P1.1  下降沿
	_EINT();
	start_7843();//触摸屏
	TFT_Initial();//TFT初始化
	DisplayDesk();
	while(1){
	    Detect_TP();
	    findNum();
	    if(ifPaused){
	        displayNums(curX*10,30,tmpNum);
	        //Distance+=tmpNum;
	        pausedNums[curX]=tmpNum;

	    }


	    DecodeIMUData();           //数据转换

//显示陀螺仪的数字
	    int temp=(int)Angle[0];
	    if(temp<0){
	        temp=-temp;
	        displayNums(90,45,17);
	    }
	    displayNums(100,45,temp/100%10);
        displayNums(110,45,temp/10%10);
        displayNums(120,45,temp%10);

        temp=(int)Angle[1];
        if(temp<0){
                    temp=-temp;
                    displayNums(140,45,17);
        }
        displayNums(150,45,temp/100%10);
        displayNums(160,45,temp/10%10);
        displayNums(170,45,temp%10);

        temp=(int)Angle[2];
        if(temp<0){
                    temp=-temp;
                    displayNums(190,45,17);
        }

        displayNums(200,45,temp/100%10);
        displayNums(210,45,temp/10%10);
        displayNums(220,45,temp%10);
	}
	return 0;
}
