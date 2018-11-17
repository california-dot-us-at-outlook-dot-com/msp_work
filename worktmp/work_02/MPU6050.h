/*
 * MPU6050.h
 *
 *  Created on: 2018��11��11��
 *      Author: Cal
 */

#ifndef MPU6050_H_
#define MPU6050_H_
#include<msp430.h>
#include"I2C_reg.h"
#include"timeConfig.h"
#define SMPLRT_DIV  0x19    //�����ʷ�Ƶ������ֵ��0x07(125Hz) */
#define CONFIG   0x1A       // ��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz) */
#define GYRO_CONFIG  0x1B   // �������Լ켰������Χ������ֵ��0x18(���Լ죬 2000deg/s) */
#define ACCEL_CONFIG 0x1C  // ���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(�� �Լ죬2G��5Hz) */
#define ACCEL_XOUT_H 0x3B  // �洢����� X �ᡢY �ᡢZ ����ٶȸ�Ӧ���Ĳ���ֵ */
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H  0x41   // �洢������¶ȴ������Ĳ���ֵ */
#define TEMP_OUT_L  0x42
#define GYRO_XOUT_H  0x43 // �洢����� X �ᡢY �ᡢZ �������Ǹ�Ӧ���Ĳ���ֵ */
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
#define PWR_MGMT_1  0x6B // ��Դ��������ֵ��0x00(��������) */
#define WHO_AM_I  0x75 //IIC ��ַ�Ĵ���(Ĭ����ֵ 0x68��ֻ��) */

#define XGH  0x43 // �洢����� X �ᡢY �ᡢZ �������Ǹ�Ӧ���Ĳ���ֵ */
#define XGL  0x44
#define YGH  0x45
#define YGL  0x46
#define ZGH  0x47
#define ZGL  0x48

#define XAH 0x3B  // �洢����� X �ᡢY �ᡢZ ����ٶȸ�Ӧ���Ĳ���ֵ */
#define XAL 0x3C
#define YAH 0x3D
#define YAL 0x3E
#define ZAH 0x3F
#define ZAL 0x40

void MPU6050_Init(unsigned char addr);             //��ʼ������ ����ʵ����д 5���Ĵ���
unsigned int readMpu16(unsigned char addr);//��ȡ16λint������


#endif /* MPU6050_H_ */
