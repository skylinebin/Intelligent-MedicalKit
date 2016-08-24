/********************************************************
���ƣ���������ģ��
���ܣ�����KEY0��ʱ��������������ÿ8�뷢��1�Σ���෢��3�Σ�
     ����KEY1ʱ��ǿ��ֹͣ�������񣬣�ת�������������ܣ�
	 KEY0������RTC�����жϴ���
Ӳ����KEY0��KEY1��Ϊ����������LED��ָʾ�����Ƿ���
     ����2 ������9600 PA3 U2_RX  PA2 U2_TX
********************************************************/

#include "delay.h" 			 
#include "usart.h" 			 
#include "usart2.h" 			 
#include "hc05.h" 
#include "led.h" 
#include "string.h"	 
#include "math.h"
//#include "key.h"
#include "timer.h"

u8 flagsendon=0;//���Ϳ�����־λ
u8 flageat=0;//�Ƿ�ó�ҩ��־λ
u8 flagkeyoff=0;//ǿ�ƹط��ͱ�־λ
  	
u8 reclen=0; //�����ַ�������

void HC05_Send(char *str)
{
   u2_printf(str);		//���͵�����ģ��		   
				 	
}	 

void HC05_TimingSend(char *str)//��ʱ�����ַ���
{
	  if(flagsendon==1)
	   {
	      u2_printf(str);		//���͵�����ģ��		   
		   flagsendon=0;
	   }
}

void HC05_TimingOn(void)   //��������ʱ��������
{
	 flageat=1;	
	   	
}


void HC05_TimingOff(void)//�ر�������ʱ�������񣬲���������
{
	  flagkeyoff=1;

	
       /***************************
		�˴������������������   		   
       ****************************/
	
}

u8 HC05_GetStr(char *str)//�յ�ָ���ַ���ʱ��1
{
	   u8 recflag=0;
	
	if(USART2_RX_STA&0X8000)			//���յ�һ��������
	   {
		   
 		reclen=USART2_RX_STA&0X7FFF;	//�õ����ݳ���
		USART2_RX_BUF[reclen]=0;	 	//���������         
 		USART2_RX_STA=0;	     						
		if(strcmp((const char*)USART2_RX_BUF,str)==0)
			recflag=1;	
		
       }
	  return recflag;
}	


		    














