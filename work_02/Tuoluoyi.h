/* Tuoluoyi.h
 * 利用串口0读取陀螺仪JY901的数据，读取 加速度/角速度/角度
 * 连线：JY901 RX-->P3.4，TX-->P3.5，电源可选5V或3.3V
 * 默认波特率为115200，可更改baud的值来改变波特率
 *  Created on: 2018年11月12日
 *      Author: Administrator
 */

#ifndef TUOLUOYI_H_
#define TUOLUOYI_H_

//串口波特率计算，当BRCLK=CPU_F时用下面的公式可以计算，否则要根据设置加入分频系数
#define CPU_F ((double)8000000)   //外部高频晶振8MHZ
#define baud           115200                                //设置波特率的大小
#define baud_setting   (unsigned int)((unsigned long)CPU_F/((unsigned long)baud))  //波特率计算公式
#define baud_h         (unsigned char)(baud_setting>>8)            //提取高位
#define baud_l         (unsigned char)(baud_setting)               //低位

unsigned char js;
unsigned char zs;
unsigned char shuju[33];        //读取11个数据
unsigned char gs;
unsigned char flag;
int temp;
float Acc[3],Groy[3],Angle[3];  //加速度/角速度/角度

//*************************************************************************
//    串口初始化
//*************************************************************************
void UART_Init();

//*************************************************************************
//    串口0发送数据函数
//*************************************************************************
void Send_Byte(unsigned char data);

//*************************************************************************
//    串口0发送字符串函数
//*************************************************************************
void Print_Str(unsigned char *s);

//*************************************************************************
//   数据转换，计算加速度/角速度/角度
//*************************************************************************
void DecodeIMUData();


#endif /* TUOLUOYI_H_ */
