/*
 * MPU6050.h
 *
 *  Created on: 2018年11月11日
 *      Author: Cal
 */

#ifndef MPU6050_H_
#define MPU6050_H_
#include<msp430.h>
#include"I2C_reg.h"
#include"timeConfig.h"
#define SMPLRT_DIV  0x19    //采样率分频，典型值：0x07(125Hz) */
#define CONFIG   0x1A       // 低通滤波频率，典型值：0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // 陀螺仪自检及测量范围，典型值：0x18(不自检， 2000deg/s) */
#define ACCEL_CONFIG 0x1C  // 加速计自检、测量范围及高通滤波频率，典型值：0x01(不 自检，2G，5Hz) */
#define ACCEL_XOUT_H 0x3B  // 存储最近的 X 轴、Y 轴、Z 轴加速度感应器的测量值 */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H  0x41   // 存储的最近温度传感器的测量值 */
#define TEMP_OUT_L  0x42
#define GYRO_XOUT_H  0x43 // 存储最近的 X 轴、Y 轴、Z 轴陀螺仪感应器的测量值 */
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
#define PWR_MGMT_1  0x6B // 电源管理，典型值：0x00(正常启用) */
#define WHO_AM_I  0x75 //IIC 地址寄存器(默认数值 0x68，只读) */

#define XGH  0x43 // 存储最近的 X 轴、Y 轴、Z 轴陀螺仪感应器的测量值 */
#define XGL  0x44
#define YGH  0x45
#define YGL  0x46
#define ZGH  0x47
#define ZGL  0x48

#define XAH 0x3B  // 存储最近的 X 轴、Y 轴、Z 轴加速度感应器的测量值 */
#define XAL 0x3C
#define YAH 0x3D
#define YAL 0x3E
#define ZAH 0x3F
#define ZAL 0x40

void MPU6050_Init(unsigned char addr);             //初始化过程 ，其实就是写 5个寄存器
unsigned int readMpu16(unsigned char addr);//读取16位int型数据


#endif /* MPU6050_H_ */
