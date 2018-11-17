#include <msp430.h>
#include"timeConfig.h"
#include"Touch.h"
#include"TFT.h"
#include"GUI.h"
/**
 * main.c
 */

    unsigned char pausedNums[8];
    unsigned char Distance=0;
    unsigned char curX=0;
    unsigned char ifPaused=1;
    unsigned char tmpNum=0;


unsigned long pow10(unsigned char pow){
    unsigned char i=0;
    unsigned char result=1;
    for(i=0;i<pow;i++){
        result*=10;
    }
    return result;
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
    }else if(Button_43){//V
        tmpNum=11;
        Button_43=0;
        ifPaused=0;
        unsigned char tmpCurX=curX;
        for(;curX>0;curX--){
            Distance+=pausedNums[curX]*pow10(tmpCurX-curX);
        }
        P6OUT=Distance;
        Distance=0;
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

	start_7843();//´¥ÃþÆÁ
	TFT_Initial();//TFT³õÊ¼»¯
	DisplayDesk();
	while(1){
	    Detect_TP();
	    findNum();
	    if(ifPaused){
	        displayNums(curX*10,30,tmpNum);
	        //Distance+=tmpNum;
	        pausedNums[curX]=tmpNum;

	    }
	}
	return 0;
}
