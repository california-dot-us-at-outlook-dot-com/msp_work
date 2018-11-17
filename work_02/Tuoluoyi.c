/* Tuoluoyi.c
 * 利用串口0读取陀螺仪JY901的数据，读取 加速度/角速度/角度
 * 连线：JY901 RX-->P3.4，TX-->P3.5，电源可选5V或3.3V
 * 默认波特率为115200
 *  Created on: 2018年11月12日
 *      Author: Administrator
 */
#include <msp430F169.h>
#include "Tuoluoyi.h"

//*************************************************************************
//    串口初始化
//*************************************************************************
void UART_Init()
{
  P3SEL|= BIT4 + BIT5;                //设置IO口为第二功能模式，启用UART功能
  P3DIR|= BIT4;                       //设置TXD0口方向为输出
  U0CTL|=SWRST + CHAR;                //复位SWRST，8位数据模式
  U0TCTL|=SSEL1;                      //SMCLK为串口时钟
  U0BR1=baud_h;                       //BRCLK=8MHZ,Baud=BRCLK/N
  U0BR0=baud_l;                       //N=UBR+(UxMCTL)/8
  U0MCTL=0x00;                        //微调寄存器为0，波特率115200bps
  ME1|=UTXE0;                         //UART0发送使能
  ME1|=URXE0;                         //UART0接收使能
  U0CTL&=~SWRST;
  IE1|=URXIE0;                        //接收中断使能位

  zs=0;
  js=0;
  gs=0;
  flag=1;
}

//*************************************************************************
//    串口0发送数据函数
//*************************************************************************
void Send_Byte(unsigned char data)
{
  while(!(IFG1&UTXIFG0));          //发送寄存器空的时候发送数据
    U0TXBUF=data;
}

//*************************************************************************
//    串口0发送字符串函数
//*************************************************************************
void Print_Str(unsigned char *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}

//*************************************************************************
//   数据转换，计算加速度/角速度/角度
//*************************************************************************
void DecodeIMUData()
{
    if (shuju[0]==0x55 && shuju[1]==0x51)  // 检查帧头 ,计算加速度
    {
        temp=(shuju[3]<<8)+shuju[2];
        Acc[0]=(float)temp*16/32768;       //X轴加速度
        temp=(shuju[5]<<8)+shuju[4];
        Acc[1]=(float)temp*16/32768;       //Y轴加速度
        temp=(shuju[7]<<8)+shuju[6];
        Acc[2]=(float)temp*16/32768;       //Z轴加速度
    }
    if (shuju[11]==0x55 && shuju[12]==0x52)  // 检查帧头,计算角速度
    {
         temp=(shuju[14]<<8)+shuju[13];
         Groy[0]=(float)temp*2000/32768;       //X轴角速度
         temp=(shuju[16]<<8)+shuju[15];
         Groy[1]=(float)temp*2000/32768;       //Y轴角速度
         temp=(shuju[18]<<8)+shuju[17];
         Groy[2]=(float)temp*2000/32768;       //Z轴角速度
    }
    if (shuju[22]==0x55 && shuju[23]==0x53)  // 检查帧头,计算角度
    {
         temp=(shuju[25]<<8)+shuju[24];
         Angle[0]=(float)temp*180/32768;       //X轴角度
         temp=(shuju[27]<<8)+shuju[26];
         Angle[1]=(float)temp*180/32768;       //Y轴角度
         temp=(shuju[29]<<8)+shuju[28];
         Angle[2]=(float)temp*180/32768;       //Z轴角度
    }
    shuju[0] = 0;           //清零，重新开始
    shuju[1] = 0;
}

//*************************************************************************
//   处理来自UART0的接收中断
//*************************************************************************
#pragma vector = USART0RX_VECTOR
__interrupt void UART0_RX_ISR(void)
{
    P6OUT=~P6OUT;
    unsigned char data;
    data = U0RXBUF;

    if (data == 0x55)
    {
        shuju[0] = data;
    }
    if (data == 0x51 && shuju[0] == 0x55)
    {
        shuju[1] = data;
        zs=1;
    }
    if (zs == 1 )         // 如果依次接收到 0x55 和  0x51，则依序接收 33个数据存入数组shuju，否则不接受数据
    {
        gs++;
        shuju[gs]=data;
    }
    if (gs==33)           // 接收完 33个数据时
    {
        zs=0;
        gs=0;             // 重新赋值，准备下一帧数据的接收
        flag=1;
    }
}
