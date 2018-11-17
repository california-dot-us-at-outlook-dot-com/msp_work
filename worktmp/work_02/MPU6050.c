/*
 * MPU6050.c
 *
 *  Created on: 2018��11��11��
 *      Author: Cal
 */

#include"MPU6050.h"
#include<msp430.h>
#include"I2C_reg.h"
#include"timeConfig.h"


void MPU6050_Init(unsigned char addr)             //��ʼ������ ����ʵ����д 5���Ĵ���
         {       /*
                 MPU6050_IIC_ByteWrite(0xd0,0x00,MPU6050_RA_PWR_MGMT_1);      // reg107, ���ѣ�8M�ڲ�ʱ��Դ
                 MPU6050_IIC_ByteWrite(0xd0,0x07,MPU6050_RA_SMPLRT_DIV);         //����Ƶ�� 1000
                 MPU6050_IIC_ByteWrite(0xd0,0x06,MPU6050_RA_CONFIG);
                 MPU6050_IIC_ByteWrite(0xd0,0x01,MPU6050_RA_ACCEL_CONFIG);     //���ٶ����� 2g
                 MPU6050_IIC_ByteWrite(0xd0,0x18,MPU6050_RA_GYRO_CONFIG);          //���ٶ����� 2000��/s
                 */
                IIC_init(addr);
                delay_ms(5);
                IICWrite(PWR_MGMT_1,0x00);
                IICWrite(SMPLRT_DIV,0x07);
                IICWrite(CONFIG,0x06);
                IICWrite(ACCEL_CONFIG,0x01);
                IICWrite(GYRO_CONFIG,0x18);
         }

unsigned int readMpu16(unsigned char addr){
    unsigned char i,j;
    i=IICRead(addr);
    j=IICRead(addr+1);
    return (i<<8)+j;
}
