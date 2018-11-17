/*
 * Touch.c
 *
 *  Created on: 2018��11��15��
 *      Author: Cal
 */




/*===================================================================================================
�ļ�����������320x240TFT��������Ƴ���ʵ�ִ���λ������ɼ���
====================================================================================================*/

//#define unsigned int ;
#include<msp430.h>
#include"Touch.h"
#include"GUI.h"
//#include"Config.h"
struct struct1 coordinate;      //����һ����ΪTp_pix�Ľṹ����,���ڴ�Ŵ�����������

//Xmin��max��Ymin��Ymax�ֱ��Ǵ����������������С/���ֵ,���ƫ���ʱ���û������±궨

//================================================================================================
//  ʵ�ֹ��ܣ���ʱ
//================================================================================================
void delay(unsigned int i)
{
    while(i--);
}
//================================================================================================
//  ʵ�ֹ��ܣ�   ADS7843����
//================================================================================================
void start_7843()
{
    P2DIR |= BIT3 + BIT4 + BIT5 + BIT6;
    //P3DIR |= 0xff;
    //P4DIR |=0xff;
    TPCLK_CLR;
    TPCS_SET;
    TPDI_SET;
    TPCLK_SET;
    TPCS_CLR;

}

//================================================================================================
//  ʵ�ֹ��ܣ�   д8λ�����������IC
//  ���������  temp ��Ҫд���8λ��������
//================================================================================================
void Write_7843(unsigned char temp)                         //SPIд8λ�����������IC
{
    unsigned char i=0;

    for(i=0;i<8;i++)                                    //ѭ��8��д��һ�ֽ�
        {
            if(temp&0x80)TPDI_SET;else TPDI_CLR;    //�ж����λ�Ƿ�Ϊ1,Ϊ1��������λд1
            TPCLK_CLR; delay(1);                //��һ�����壬��������Ч����DINλ�������뵽IC
            TPCLK_SET; delay(1);
            temp<<=1;                           //��д��������1λ��׼����д��һλ����
        }
}

//================================================================================================
//  ʵ�ֹ��ܣ�   �Ӵ�������IC��8λ���ݵ�������
//  ���ز�����  temp ��Ҫд���8λ��������
//================================================================================================
unsigned int Read_7843()                          //SPI ������
{
    unsigned char i=0;
    unsigned int temp=0;

    for(i=0;i<12;i++)                         //ѭ��12�ζ�ȡ12λ���
     {
       temp<<=1;                                  //temp����һλ��׼����ȡ��һλ
       TPCLK_SET; delay(1);                   //�½�����Ч
       TPCLK_CLR; delay(1);
       if(TPDOUT) temp++;                     //�жϿ���IC�ͳ���һλ�����Ƿ�Ϊ1,���Ϊ1,����temp�����λ
     }
    return(temp);                                 //���ؽ��
}

//================================================================================================
//  ʵ�ֹ��ܣ���ȡ������X���Y���ѹֵ
//  ���ز�����pix ��ȡ���Ĵ������ѹֵ
//================================================================================================
struct struct1 AD7843()
{
    struct struct1 pix;
    TPCS_CLR;

    Write_7843(0x90);                 //�Ϳ����� 10010000 ���ò�ַ�ʽ��X���꣬��ϸ����й�����
    TPCLK_SET; delay(1);
    TPCLK_CLR; delay(1);
    pix.y=Read_7843();

    Write_7843(0xD0);                 //�Ϳ����� 11010000 ���ò�ַ�ʽ��Y���� ��ϸ����й�����
    TPCLK_SET; delay(1);
    TPCLK_CLR; delay(1);
    pix.x=Read_7843();

    TPCS_SET;
    return pix;
}

//================================================================================================
//  ʵ�ֹ��ܣ�����˲����˵���������Ĳ�����
//  ���ز�����flag �ɼ������Ƿ���Ч��־,flag=1;��������Ч
//================================================================================================
unsigned char pix_filter(struct struct1 pix1,struct struct1 pix2)
{
    unsigned char flag=0;
    int x=pix1.x>pix2.x?pix1.x-pix2.x:pix2.x-pix1.x;  //X�����β�������ֵ
    int y=pix1.y>pix2.y?pix1.y-pix2.y:pix2.y-pix1.y;  //Y�����β�������ֵ
    if(x<10&&y<10)                                    //����˲���2��ȡ����ֵ���̫�����Ϊ����
    {
        flag=1;
        coordinate.x=(pix1.x+pix2.x)/2;           //�����β���ƽ��ֵ
        coordinate.y=(pix1.y+pix2.y)/2;
    }
    return flag;
}

//================================================================================================
//  ʵ�ֹ��ܣ���ȡ�ɼ����,����ȡ��ֵ
//================================================================================================
unsigned char Getpix() //ȡ����ֵ���˴�ʹ������˲���2��ȡ����ֵ���̫�����Ϊ����
{
    unsigned char flag=0;
    struct struct1 pix1;
    struct struct1 pix2;
    if (PEN==0)
        {
            pix1=AD7843();
            pix2=AD7843();

            if(pix_filter(pix1,pix2)==1) //�õ���ǰTP��ȡ��ֵ���˴�ʹ������˲���2��ȡ����ֵ���̫�����Ϊ����
                {
                  if((coordinate.x>Xmin)&&(coordinate.y>Ymin))
                   {
                    ltx=(unsigned int)(240.0*(coordinate.x-Xmin)/(Xmax-Xmin));       //����ת���������ݲ���ֵ����ʵ������ֵ
                    lty=(unsigned int)(320.0*(coordinate.y-Ymin)/(Ymax-Ymin));   //Xmin��max��Ymin��Ymax�ֱ��Ǵ����������������С/���ֵ
                    flag=1;
                    LCD_X=ltx;
                    LCD_Y=lty;
                   }
                }
        }

    return flag;

}


/*
 *
 *
 *
 * ��������
 */
/*
void GUIsquare2pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{
    unsigned int i,j;

    for(i=0;i<2;i++)
            {
                GUIline(x0+i,y0,x0+i,y1,full_colour);
                GUIline(x0,y0+i,x1,y0+i,full_colour);
                GUIline(x0,y1-i,x1,y1-i,full_colour);
                GUIline(x1-i,y0,x1-i,y1,full_colour);
            }
}
*/

/*
 *
 *
 *
 * ʶ�𰴼�
 *
 */

void Detect_TP(void)
{

     if(Getpix()==1)
      {
       /*��һ��4����ť11,21,31,41*/
    if((LCD_X>=xs(0))&& (LCD_X<=xe(0)))     //���ݹ�ʽ�ο��������ʱ�Ĺ�ʽ��main�����У�xs��xe�������������յ�
    {
    if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //���ݹ�ʽ��ys��ye�������������յ�
    {
      Button_11=1;
      GUIsquare2pix(xs(0),ys(0),xe(0),ye(0),Red);
      delay_ms(1);
      delay_ms(1);
      delay_ms(1);
      while(PEN==0);
      GUIsquare2pix(xs(0),ys(0),xe(0),ye(0),Black);
    }

        else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))

        {

          Button_21=1;

          GUIsquare2pix(xs(0),ys(1),xe(0),ye(1),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(0),ys(1),xe(0),ye(1),Black);

        }

        else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))

        {

          Button_31=1;

          GUIsquare2pix(xs(0),ys(2),xe(0),ye(2),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(0),ys(2),xe(0),ye(2),Black);

        }

        else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))

        {

          Button_41=1;

          GUIsquare2pix(xs(0),ys(3),xe(0),ye(3),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(0),ys(3),xe(0),ye(3),Black);

        }

        }
      /*�ڶ���4����ť12,22,32,42*/
        if((LCD_X>=xs(1))&& (LCD_X<=xe(1)))     //���ݹ�ʽ�ο��������ʱ�Ĺ�ʽ��main�����У�xs��xe�������������յ�

        {

          if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //���ݹ�ʽ��ys��ye�������������յ�

          {

            Button_12=1;

            GUIsquare2pix(xs(1),ys(0),xe(1),ye(0),Red);

            delay_ms(1);

            delay_ms(1);

            delay_ms(1);

            while(PEN==0);

            GUIsquare2pix(xs(1),ys(0),xe(1),ye(0),Black);

          }


          else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))

          {

            Button_22=1;

            GUIsquare2pix(xs(1),ys(1),xe(1),ye(1),Red);

            delay_ms(1);

            delay_ms(1);

            delay_ms(1);

            while(PEN==0);

            GUIsquare2pix(xs(1),ys(1),xe(1),ye(1),Black);

          }

          else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))

          {
            Button_32=1;

            GUIsquare2pix(xs(1),ys(2),xe(1),ye(2),Red);

            delay_ms(1);

            delay_ms(1);

            delay_ms(1);

            while(PEN==0);

            GUIsquare2pix(xs(1),ys(2),xe(1),ye(2),Black);

          }
          else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))

          {
            Button_42=1;

            GUIsquare2pix(xs(1),ys(3),xe(1),ye(3),Red);

            delay_ms(1);

            delay_ms(1);

            delay_ms(1);

            while(PEN==0);

            GUIsquare2pix(xs(1),ys(3),xe(1),ye(3),Black);

          }

        }

        /*������4����ť13,23,33,43*/
      if((LCD_X>=xs(2))&& (LCD_X<=xe(2)))     //���ݹ�ʽ�ο��������ʱ�Ĺ�ʽ��main�����У�xs��xe�������������յ�

      {

        if((LCD_Y>=ys(0)) &&(LCD_Y<=ye(0)))  //���ݹ�ʽ��ys��ye�������������յ�

        {

          Button_13=1;

          GUIsquare2pix(xs(2),ys(0),xe(2),ye(0),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(2),ys(0),xe(2),ye(0),Black);

        }

        else if((LCD_Y>=ys(1)) &&(LCD_Y<=ye(1)))

        {

          Button_23=1;

          GUIsquare2pix(xs(2),ys(1),xe(2),ye(1),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(2),ys(1),xe(2),ye(1),Black);

        }

        else if((LCD_Y>=ys(2)) &&(LCD_Y<=ye(2)))

        {

          Button_33=1;

          GUIsquare2pix(xs(2),ys(2),xe(2),ye(2),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(2),ys(2),xe(2),ye(2),Black);

        }
        else if((LCD_Y>=ys(3)) &&(LCD_Y<=ye(3)))

        {

          Button_43=1;

          GUIsquare2pix(xs(2),ys(3),xe(2),ye(3),Red);

          delay_ms(1);

          delay_ms(1);

          delay_ms(1);

          while(PEN==0);

          GUIsquare2pix(xs(2),ys(3),xe(2),ye(3),Black);

        }

      }


      }

}
