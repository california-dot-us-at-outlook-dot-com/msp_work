/****************************************************************************************************  
�ļ�����������GUI��ͼ�����������Ը����Լ����������ӻ�ͼ���������л��㡢ʵ�ߡ����ߡ�������䡢�����СԲ�κ���
****************************************************************************************************/
/*
#ifndef unsigned char
#define unsigned char unsigned char
#endif

#ifndef unsigned int
#define unsigned int unsigned int
#endif

*/

#include "math.h"
#include "GUI.h"
//void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
//void  Write_Data_U16(unsigned int y);

/****************************************************************************************************
//  ʵ�ֹ��ܣ�	����
//  ��������� x��y ��Ҫ��������
//            color �����ɫ
****************************************************************************************************/
void GUIpoint(unsigned int x,unsigned int y,unsigned int color)
{
	LCD_SetPos(x,x,y,y);												//��������Ҫ��������任���������������ֱ����x0,x1,y0,y1������

	Write_Data_U16(color);      												//��ָ����д����ɫ����
}

//***********************************************************************
//         ����GUI���ߺ�������x0,y0��Ϊ��ʼ����,��x1,y1��Ϊ�յ�����
//		   line_color �ߵ���ɫ
//***********************************************************************

void GUIline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color)   //���ߺ���
{
    int temp; 
    int dx,dy;               			//������㵽�յ�ĺᡢ����������ֵ 
    int s1,s2,status,i; 
    int Dx,Dy,sub; 
	
	  dx = x1 - x0; 
    if(dx >= 0)                 	//X�ķ��������ӵ� 
        s1 = 1; 
    else                     			//X�ķ����ǽ��͵� 
        s1 = -1;      
    dy = y1 - y0;               	//�ж�Y�ķ��������ӻ��ǽ����� 
    if(dy >= 0) 
        s2 = 1; 
    else 
        s2 =- 1; 
   
    Dx = abs(x1-x0);             	//����ᡢ�ݱ�־����ֵ�ľ���ֵ 
    Dy = abs(y1-y0); 
        
    if(Dy > Dx)                               
    {                     				//��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0  
        temp = Dx; 
        Dx = Dy; 
        Dy = temp; 
    status = 1; 
    }  
    else 
        status = 0; 

/*********Bresenham�㷨������������ֱ��********/  
    sub = Dy + Dy - Dx;                 //��1���ж��¸����λ�� 
    for(i = 0;i < Dx;i ++) 
    {  
        GUIpoint(x0,y0,line_color);           //����  
        if(sub >= 0)                                
        {  
            if(status == 1)               //�ڿ���Y������xֵ��1 
                x0 += s1;  
            else                     //�ڿ���X������yֵ��1                
                y0 += s2;  
            sub -= (Dx + Dx);                 //�ж����¸����λ��  
        }  
        if(status == 1) 
            y0 += s2;  
        else        
            x0 += s1;  
        sub += Dy + Dy;  
         
    }  
} 

//***********************************************************************
//         ����GUI�����ߺ�������x0,y0��Ϊ��ʼ����,��x1,y1��Ϊ�յ�����
//		   line_color �ߵ���ɫ
//***********************************************************************

void GUIDotline(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int line_color)   //�����ߺ���
{
    int temp; 
    int dx,dy;               	//������㵽�յ�ĺᡢ����������ֵ 
    int s1,s2,status,i; 
    int Dx,Dy,sub; 
	
	  dx = x1 - x0; 
    if(dx >= 0)                 //X�ķ��������ӵ� 
        s1 = 1; 
    else                     	  //X�ķ����ǽ��͵� 
        s1 = -1;      
    dy = y1 - y0;               //�ж�Y�ķ��������ӻ��ǽ����� 
    if(dy >= 0) 
        s2 = 1; 
    else 
        s2 =- 1; 
   
    Dx = abs(x1-x0);             //����ᡢ�ݱ�־����ֵ�ľ���ֵ 
    Dy = abs(y1-y0); 
        
    if(Dy > Dx)                               
    {                     				//��45�Ƚ�Ϊ�ֽ��ߣ�����Y����status=1,����X����status=0  
        temp = Dx; 
        Dx = Dy; 
        Dy = temp; 
    status = 1; 
    }  
    else 
        status = 0; 

/*********Bresenham�㷨������������ֱ��********/  
    sub = Dy + Dy - Dx;                									 //��1���ж��¸����λ�� 
    for(i = 0;i < Dx;i ++) 
    {  
        if((i%10)<=4) GUIpoint(x0,y0,line_color);       //���㣬���߼���С������������ڣ����ò�ͬ���ж����� 
        if(sub >= 0)                                
        {  
            if(status == 1)               							//�ڿ���Y������xֵ��1 
                x0 += s1;  
            else                     										//�ڿ���X������yֵ��1                
                y0 += s2;  
            sub -= (Dx + Dx);                 					//�ж����¸����λ��  
        }  
        if(status == 1) 
            y0 += s2;  
        else        
            x0 += s1;  
        sub += Dy + Dy;  
				
         
    }  
} 

/**************************************************************************** 
* ���ƣ�GUI_Full(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour) 
* ���ܣ��û�ͼ�ķ������һ������ 
* ��ڲ�����x0 			��ʼ������� 
*          y0    		��ʼ�������� 
*          x1 			��ֹ������� 
*          y1      	��ֹ�������� 
*          full_color      	��ʾ��ɫ 
* ���ڲ������� 
****************************************************************************/ 
void GUIfull(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{ 
    unsigned int i,j;
for(j = y0;j <= y1;j ++) 
    for(i = x0;i <= x1;i ++) 
    GUIpoint(i,j,full_colour); 
} 

/**************************************************************************** 
* ���ƣ�GUIsquare1pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour) 
* ���ܣ��û�ͼ�ķ�������һ�����α߿�,1�����ص��
* ��ڲ�����x0 			��ʼ������� 
*          y0    		��ʼ�������� 
*          x1 			��ֹ������� 
*          y1      	��ֹ�������� 
*          full_color      	��ʾ��ɫ 
* ���ڲ������� 
****************************************************************************/ 
void GUIsquare1pix(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1,unsigned int full_colour)
{ 
    unsigned int i,j;

    GUIline(x0,y0,x0,y1,full_colour);
		GUIline(x0,y0,x1,y0,full_colour); 
		GUIline(x0,y1,x1,y1,full_colour); 
		GUIline(x1,y0,x1,y1,full_colour); 	
} 

/**************************************************************************** 
* ���ƣ�GUIsquare2pix(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char full_colour) 
* ���ܣ��û�ͼ�ķ�������һ�����α߿�,2�����ص��
* ��ڲ�����x0 			��ʼ������� 
*          y0    		��ʼ�������� 
*          x1 			��ֹ������� 
*          y1      	��ֹ�������� 
*          full_color      	��ʾ��ɫ 
* ���ڲ������� 
****************************************************************************/ 
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
/**************************************************************************** 
* ���ƣ�plotC(int x,int y,int xc,int yc,unsigned char yc_colour) 
* ���ܣ��˷ֵ㻭Բ���� 
* ��ڲ�����x    		ָ������������е�λ�� 
*           y    		ָ������������е�λ�� 
*          yc_color 	��ʾ��ɫ,���ݲ�ɫ�����趨 
* ���ڲ������� 
****************************************************************************/ 
void plotC(unsigned int x,unsigned int y,unsigned int xc,int yc,unsigned int yc_colour)
{ 
    GUIpoint(xc+x,yc+y,yc_colour); 
    GUIpoint(xc+x,yc-y,yc_colour); 
    GUIpoint(xc-x,yc+y,yc_colour); 
    GUIpoint(xc-x,yc-y,yc_colour); 
    GUIpoint(xc+y,yc+x,yc_colour); 
    GUIpoint(xc+y,yc-x,yc_colour); 
    GUIpoint(xc-y,yc+x,yc_colour); 
    GUIpoint(xc-y,yc-x,yc_colour); 
} 

/**************************************************************************** 
* ���ƣ�GUI_Circle(int xc,int yc,int r,unsigned char circle_colour) 
* ���ܣ���Բ 
* ��ڲ�����xc 				Բ�ĵ������� 
*           yc    		Բ�ĵ������� 
*           r 				�뾶 
*          circle_color     ��ʾ��ɫ 
* ���ڲ������� 
****************************************************************************/ 
void GUIcircle(unsigned int xc,unsigned int yc,unsigned int r,unsigned int circle_colour)
{ 
    int x,y,d; 
    y = r; 
    d = 3 - (r + r); 
    x = 0; 
    while(x <= y) 
    { 
        plotC(x,y,xc,yc,circle_colour); 
        if(d < 0) 
            d += (x + x + x + x) + 6; 
        else 
        { 
            d+=((x - y) + (x - y) + (x - y) + (x - y)) + 10; 
            y = y - 1; 
        } 
        x = x + 1; 
    } 
}


//��ɫ���룬TFT��ʾ��
#define White          0xFFFF                                                               //��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0


void CLR_Screen(unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(0,240,0,320);//320x240
 for (i=0;i<320;i++)
    {
       for (j=0;j<240;j++)
           Write_Data_U16(bColor);
    }
}
/*
 *
 *
 *
 * ������ĺ���
 */
extern unsigned char nums[];
void DisplayDesk(void)
{
  unsigned int i,j,xs,ys,xe,ye;

  CLR_Screen(Black);
  //LCD_PutString24(72,0,"��������",Yellow,Black);
  GUIline(1,25,240,25,Yellow);
  GUIline(1,70,240,70,Yellow);
  GUIline(1,319,240,319,Yellow);
  GUIline(1,25,1,319,Yellow);
  GUIline(239,25,239,319,Yellow);

  for(i=0;i<4;i++)

  {
    for(j=0;j<3;j++)
    {
      xs=j*60+15*j+15;
      ys=80+i*50+10*i;
      xe=j*60+15*j+15+60;
      ye=80+i*50+10*i+50;

      displayNums(xs+26,ys+17,nums[i*3+j]);
//      LCD_Full(xs,xe,ys,ye,White);
//      LCD_PutString(xs+26,ys+17,Tab[i*3+j],Black,White);  //��ťֵ��ʾ
    }
  }
}
