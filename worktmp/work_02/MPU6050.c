/*
 * MPU6050.c
 *
 *  Created on: 2018年11月11日
 *      Author: Cal
 */

#include"MPU6050.h"
#include<msp430.h>
#include"I2C_reg.h"
#include"timeConfig.h"


void MPU6050_Init(unsigned char addr)             //初始化过程 ，其实就是写 5个寄存器
         {       /*
                 MPU6050_IIC_ByteWrite(0xd0,0x00,MPU6050_RA_PWR_MGMT_1);      // reg107, 唤醒，8M内部时钟源
                 MPU6050_IIC_ByteWrite(0xd0,0x07,MPU6050_RA_SMPLRT_DIV);         //采用频率 1000
                 MPU6050_IIC_ByteWrite(0xd0,0x06,MPU6050_RA_CONFIG);
                 MPU6050_IIC_ByteWrite(0xd0,0x01,MPU6050_RA_ACCEL_CONFIG);     //加速度量程 2g
                 MPU6050_IIC_ByteWrite(0xd0,0x18,MPU6050_RA_GYRO_CONFIG);          //角速度量程 2000度/s
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
