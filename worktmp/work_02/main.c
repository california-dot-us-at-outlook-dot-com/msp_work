#include <msp430.h>
#include"timeConfig.h"
#include"Touch.h"
#include"TFT.h"
#include"GUI.h"
#include"MPU6050.h"
#include"interrupt.h"

#pragma vector = PORT1_VECTOR
__interrupt void Port1_ISR(void){
    P3OUT |=(BIT0);
    P1IFG &= 0;
}
/**
 * main.c
 */

unsigned char angle90[6]={
                          0b01000001,0b11000001,
                          0b00111111,0b10111110,
                          0b00111100,0b10111001,

};

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


//预存数据
//最远长度为6米，
//数组长度为11，第一个为0cm,第二个为60cm，第三个为120cm。。。。
unsigned char startAngle[11];
unsigned char endAngle[11];
unsigned char type[11];
unsigned char deep[11];
unsigned char X_s[11];//向前还是向后
unsigned char X_e[11];

unsigned char tmpStartAngle;
unsigned char tmpEndAngle;
unsigned char tmpType;
unsigned char tmpDeep;
unsigned char tmpX_s;
unsigned char tmpX_e;

void Init_Data(){
    startAngle[0]=0;
    endAngle[0]=0;
    type[0]=0;
    deep[0]=0;
    X_s[0]=0;
    X_e[0]=0;

    startAngle[1]=45;
    endAngle[1]=0;
    type[1]=0;
    deep[1]=0;
    X_s[1]=21;
    X_e[1]=0;

    startAngle[2]=0;
    endAngle[2]=0;
    type[2]=0;
    deep[2]=0;
    X_s[2]=0;
    X_e[2]=0;

    startAngle[3]=0;
    endAngle[3]=0;
    type[3]=0;
    deep[3]=0;
    X_s[3]=0;
    X_e[3]=0;

    startAngle[4]=0;
    endAngle[4]=0;
    type[4]=0;
    deep[4]=0;
    X_s[4]=0;
    X_e[4]=0;

    startAngle[5]=0;
    endAngle[5]=0;
    type[5]=0;
    deep[5]=0;
    X_s[5]=0;
    X_e[5]=0;

    startAngle[6]=0;
    endAngle[6]=0;
    type[6]=0;
    deep[6]=0;
    X_s[6]=0;
    X_e[6]=0;

    startAngle[7]=0;
    endAngle[7]=0;
    type[7]=0;
    deep[7]=0;
    X_s[7]=0;
    X_e[7]=0;

    startAngle[8]=0;
    endAngle[8]=0;
    type[8]=0;
    deep[8]=0;
    X_s[8]=0;
    X_e[8]=0;

    startAngle[9]=0;
    endAngle[9]=0;
    type[9]=0;
    deep[9]=0;
    X_s[9]=0;
    X_e[9]=0;

    startAngle[10]=0;
    endAngle[10]=0;
    type[10]=0;
    deep[10]=0;
    X_s[10]=0;
    X_e[10]=0;
/*
    startAngle[11]=0;
    endAngle[11]=0;
    type[11]=0;
    deep[11]=0;
    X_s[11]=0;
*/
}

//判断距离，选择数据
void selectData(){
    unsigned char i,j;
    i=Distance/6;//Distance 单位为分米
    j=(Distance%6)/3;
    //j=if(j);
    tmpStartAngle=startAngle[i+j];
    tmpEndAngle=endAngle[i+j];
    tmpType=type[i+j];
    tmpDeep=deep[i+j];
    tmpX_s=X_s[i+j];
    tmpX_e=X_e[i+j];
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
    }else if(Button_43 && (!ready)){//V
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
        selectData();
        displayNums(40,0,tmpX_s);
        displayNums(50,0,tmpStartAngle/10);
        displayNums(60,0,tmpStartAngle%10);

        displayNums(80,0,tmpX_e);
        displayNums(90,0,tmpEndAngle/10);
        displayNums(100,0,tmpEndAngle%10);

        displayNums(120,0,tmpDeep/10);
        displayNums(130,0,tmpDeep%10);

        displayNums(150,0,tmpType);



        ready=1;
//        Distance=0;
    }

    else if(Button_43 && ready){//V
        DistanceMatch();
        displayNums(10,0,16);
        displayNums(20,0,16);
        Button_43=0;
        ready=0;
        Distance=0;
        ifPaused=0;
        displayNums(40,0,16);
        displayNums(50,0,16);
        displayNums(60,0,16);

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

	//i2c_init();
	MPU6050_Init(0xd0);


	P3DIR |= BIT0;
	P3OUT |= BIT0;
//	UART_Init();                        //串口设置初始化
	interrupt_init(1,0b00000011,0b00000011);//P1.0  P1.1  下降沿
	_EINT();
	start_7843();//触摸屏
	TFT_Initial();//TFT初始化
	DisplayDesk();


    unsigned char i,j,k;
    unsigned char rx=0,ry=0,rz=0;

    Init_Data();

	while(1){
	    Detect_TP();
	    findNum();
	    if(ifPaused){
	        displayNums(curX*10,30,tmpNum);
	        //Distance+=tmpNum;
	        pausedNums[curX]=tmpNum;

	    }



        i=(readMpu16(XAH)>>8);
        j=(readMpu16(YAH)>>8);
        //k=(readMpu16(ZAH)>>8);
        if(i&0x80){
            rx=((255-i)*90/(255-angle90[1]));
            i=20;
        }else{
            rx=i*90/angle90[0];
            i=21;
        }
        if(j&0x80){
            ry=((255-j)*90/(255-angle90[3]));
            j=20;
        }else{
            ry=j*90/angle90[2];
            j=21;
        }
        /*
        if(k&0x80){
            rz=((255-k)*90/(255-angle90[5]));
            k='<';
        }else{
            rz=k*90/angle90[4];
            k='>';
        }
*/

        //displayNums(100,45,);
        //displayNums(110,45,rx/10);
        //displayNums(120,45,rx%10);

        displayNums(130,45,i);
        displayNums(140,45,ry/10);
        displayNums(150,45,ry%10);


        //displayNums(170,45,rz/10);
        //displayNums(180,45,rz%10);

/*
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
	*/


	}
	return 0;
}
