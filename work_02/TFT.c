/*
 * TFT.c
 *
 *  Created on: 2018年11月1日
 *      Author: Cal
 */

#include"TFT.h"

const char nums[]={
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x42,0x42,0x42,0x42,0x24,0x18,0x00,0x00,//0
0x00,0x00,0x00,0x10,0x70,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x10,0x7C,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x04,0x04,0x08,0x10,0x20,0x42,0x7E,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x04,0x18,0x04,0x02,0x02,0x42,0x44,0x38,0x00,0x00,
0x00,0x00,0x00,0x04,0x0C,0x14,0x24,0x24,0x44,0x44,0x7E,0x04,0x04,0x1E,0x00,0x00,
0x00,0x00,0x00,0x7E,0x40,0x40,0x40,0x58,0x64,0x02,0x02,0x42,0x44,0x38,0x00,0x00,
0x00,0x00,0x00,0x1C,0x24,0x40,0x40,0x58,0x64,0x42,0x42,0x42,0x24,0x18,0x00,0x00,
0x00,0x00,0x00,0x7E,0x44,0x44,0x08,0x08,0x10,0x10,0x10,0x10,0x10,0x10,0x00,0x00,
0x00,0x00,0x00,0x3C,0x42,0x42,0x42,0x24,0x18,0x24,0x42,0x42,0x42,0x3C,0x00,0x00,
0x00,0x00,0x00,0x18,0x24,0x42,0x42,0x42,0x26,0x1A,0x02,0x02,0x24,0x38,0x00,0x00,//9
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x60,0x00,0x00,//.
0x00,0x00,0x00,0xE7,0x42,0x42,0x44,0x24,0x24,0x28,0x28,0x18,0x10,0x10,0x00,0x00,//V
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0x49,0x49,0x49,0x49,0x49,0xED,0x00,0x00,//m
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xC6,0x42,0x42,0x42,0x42,0x46,0x3B,0x00,0x00,//u
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3E,0x42,0x40,0x3C,0x02,0x42,0x7C,0x00,0x00,//s
0x00,0x00,0x01,0x02,0x02,0x04,0x04,0x08,0x08,0x10,0x10,0x20,0x20,0x40,0x40,0x00///
};



unsigned int Device_code=0x9320;
void Write_Data(unsigned char DH,unsigned char DL)
{

    CS_CLR;
    RS_SET;

    //注意：当使用8位数据口驱动16位数据模式时，使用74HC573作为IO扩展，程序如下
    DataPort=DH;            //送低8位数据给573待锁存
    LE_SET;                   //锁存位
    LE_CLR;                   //断开锁存,位选573的Q7~Q0仍保持

    DataPort=DL;            //送高8位数据给TFT

    /*
    //如果使用16位数据口驱动16位数据模式，则无需IO扩展，直接将数据送到数据口即可
    DataPort_L=DL;
    DataPort_H=DH;
    */

    RW_CLR;
    RW_SET;
    CS_SET;
}

void  Write_Data_U16(unsigned int y)
{
  unsigned char m,n;
  m=y>>8;
  n=y;
  Write_Data(m,n);
}

void Write_Cmd(unsigned char DH,unsigned char DL)
{
    CS_CLR;
    RS_CLR;
        RD_SET;
        RW_CLR;

    //注意：当使用8位数据口驱动16位数据模式时，使用74HC573作为IO扩展，程序如下
    DataPort=DH;            //送低8位命令给573待锁存
    LE_SET;                   //锁存位
    LE_CLR;                   //断开锁存,位选573的Q7~Q0仍保持

    DataPort=DL;            //送高8位命令给TFT

    /*
    //如果使用16位数据口驱动16位数据模式，则无需IO扩展，直接将数据送到数据口即可
    DataPort_L=DL;
    DataPort_H=DH;
    */

    RW_SET;
    CS_SET;
}

void  Write_Cmd_Data (unsigned char x,unsigned int y)
{
    unsigned char m,n;
    m=y>>8;
    n=y;
    Write_Cmd(0x00,x);
    Write_Data(m,n);
}

void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{

  Write_Cmd_Data(0x50,x0);  // Horizontal GRAM Start Address
  Write_Cmd_Data(0x51,x1);  // Horizontal GRAM End Address
  Write_Cmd_Data(0x52,y0);  // Vertical GRAM Start Address
  Write_Cmd_Data(0x53,y1);  // Vertical GRAM Start Address
  Write_Cmd_Data(0x20,x0);  // GRAM horizontal Address
  Write_Cmd_Data(0x21,y0);  // GRAM Vertical Address
  Write_Cmd (0x00,0x22);    // 0x0022,Start to Write Data to GRAM
}

void displayNums(unsigned int x,unsigned int y,unsigned char num){
    unsigned char i=0;
    i=num*16;
    unsigned char tmp=0;
    LCD_SetPos(x,x+7,y,y+15);
    for(y=0;y<16;y++){
        tmp=nums[i+y];
        for(x=0;x<8;x++){
            if(tmp&0x80){
                Write_Data(0xf8,0x00);
            }else{
                Write_Data(0x00,0x00);
            }
            tmp<<=1;
        }
    }
}

void clearNums(unsigned int x,unsigned int y,unsigned char num){
    unsigned char i=0;
    i=num*16;
    unsigned char tmp=0;
    LCD_SetPos(x,x+7,y,y+15);
    for(y=0;y<16;y++){
        tmp=nums[i+y];
        for(x=0;x<8;x++){
            if(tmp&0x80){
                Write_Data(0x00,0x00);
            }else{
                Write_Data(0xf8,0x00);
            }
            tmp<<=1;
        }
    }
}

void TFT_Initial(void)
{
    P4DIR=0xff;
    P5DIR=0xff;
    P3DIR=0xff;

    RST_SET;
    delay_ms(1);                    // Delay 1ms
    RST_CLR;
    delay_ms(10);                   // Delay 10ms
    RST_SET;
    delay_ms(50);                   // Delay 50 ms

    if(Device_code==0x9320)
     {
        P6OUT=0xf0;
    //************* Start Initial Sequence **********//
    Write_Cmd_Data(0x00,0x0001);   //Set the OSC bit as ‘1’ to start the internal oscillator
    Write_Cmd_Data(0x01,0x0100);   // set SS and SM bit
    Write_Cmd_Data(0x02,0x0700);   // set 1 line inversion
    Write_Cmd_Data(0x03,0x1030);   //set GRAM Write direction and BGR=1
    Write_Cmd_Data(0x04,0x0000);   // Resize register
    Write_Cmd_Data(0x08,0x0202);   // set the back porch and front porch
    Write_Cmd_Data(0x09,0x0000);   // set non-display area refresh cycle ISC[3:0]
    Write_Cmd_Data(0x0A,0x0000);   // FMARK function
    Write_Cmd_Data(0x0C,0x0000);   // RGB interface setting
    Write_Cmd_Data(0x0D,0x0000);   // Frame marker Position
    Write_Cmd_Data(0x0F,0x0000);   // RGB interface polarity
    delay_ms(30);
    //*************Power On sequence ****************//
    Write_Cmd_Data(0x10, 0x16b0);   // SAP, BT[3:0], AP, DSTB, SLP, STB
    delay_ms(30);
    Write_Cmd_Data(0x11, 0x0007);   //Write final user’s setting values to VC bit
    Write_Cmd_Data(0x12, 0x013a);   // set Internal reference voltage
    Write_Cmd_Data(0x13, 0x1a00);   // VDV[4:0] for VCOM amplitude
    delay_ms(30);
    Write_Cmd_Data(0x29, 0x000c);   // Set VCM[5:0] for VCOMH
    delay_ms(30); // Delay 50ms

    // ----------- Adjust the Gamma Curve ----------//
    Write_Cmd_Data(0x0030, 0x0000);
    Write_Cmd_Data(0x0031, 0x0505);
    Write_Cmd_Data(0x0032, 0x0304);
    Write_Cmd_Data(0x0035, 0x0006);
    Write_Cmd_Data(0x0036, 0x0707);
    Write_Cmd_Data(0x0037, 0x0105);
    Write_Cmd_Data(0x0038, 0x0002);
    Write_Cmd_Data(0x0039, 0x0707);
    Write_Cmd_Data(0x003C, 0x0704);
    Write_Cmd_Data(0x003D, 0x0807);

    //------------------ Set GRAM area ---------------//
    Write_Cmd_Data(0x0050, 0x0000); // Horizontal GRAM Start Address
    Write_Cmd_Data(0x0051, 0x00EF); // Horizontal GRAM End Address
    Write_Cmd_Data(0x0052, 0x0000); // Vertical GRAM Start Address
    Write_Cmd_Data(0x0053, 0x013F); // Vertical GRAM Start Address
    Write_Cmd_Data(0x0060, 0x2700); // Gate Scan Line
    Write_Cmd_Data(0x0061, 0x0001); // NDL,VLE, REV
    Write_Cmd_Data(0x006A, 0x0000); // set scrolling line
    Write_Cmd_Data(0x20, 0x0000);   // GRAM horizontal Address
    Write_Cmd_Data(0x21, 0x0000);   // GRAM Vertical Address

    //-------------- Partial Display Control ---------//
    Write_Cmd_Data(0x0080, 0x0000);
    Write_Cmd_Data(0x0081, 0x0000);
    Write_Cmd_Data(0x0082, 0x0000);
    Write_Cmd_Data(0x0083, 0x0000);
    Write_Cmd_Data(0x0084, 0x0000);
    Write_Cmd_Data(0x0085, 0x0000);

    //-------------- Panel Control ---------//
    Write_Cmd_Data(0x90,0x0010);   //Frame Cycle Contral
    Write_Cmd_Data(0x92,0x0000);   //Panel Interface Contral
    Write_Cmd_Data(0x93,0x0003);   //Panel Interface Contral 3.
    Write_Cmd_Data(0x95,0x0110);   //Frame Cycle Contral
    Write_Cmd_Data(0x97,0x0000);   //
    Write_Cmd_Data(0x98,0x0000);   //Frame Cycle Contral.

    //-------------- Display on ---------//
    Write_Cmd_Data(0x07,0x0173);

    }

}


