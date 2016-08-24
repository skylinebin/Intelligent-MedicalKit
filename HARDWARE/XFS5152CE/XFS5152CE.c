#include "sys.h"
#include "delay.h"
#include "string.h"
#include "uart4.h"
#include "XFS5152CE.h"
#include "LED.h"



void voice_sy(char data[])
{
    u16 len;
	u16 t;
	u8  UART_TX_BUFER[50]={0};
	
	len=strlen(data);
	
	delay_ms(3000);
	
//	UART_TX_BUFER[0] = 0xFD ;
//	UART_TX_BUFER[1] = 0xFD ; 			//����֡ͷFD
//	UART_TX_BUFER[2] = 0x00 ; 			//�������������ȵĸ��ֽ�
//	UART_TX_BUFER[3] = len+2; 	    //�������������ȵĵ��ֽ�
//	UART_TX_BUFER[4] = 0x01 ; 			//���������֣��ϳɲ�������		 		 
//	UART_TX_BUFER[5] = 0x01;           //�ı������ʽ��GBK
	
	UART_TX_BUFER[0] = 0xFD ; 			//����֡ͷFD
	UART_TX_BUFER[1] = 0x00 ; 			//�������������ȵĸ��ֽ�
	UART_TX_BUFER[2] = len+2; 	    //�������������ȵĵ��ֽ�
	UART_TX_BUFER[3] = 0x01 ; 			//���������֣��ϳɲ�������		 		 
	UART_TX_BUFER[4] = 0x01;           //�ı������ʽ��GBK
	memcpy(&UART_TX_BUFER[5], data, len);
	
	for(t=0;t<(len+6);t++)
	{
		USART_SendData(UART4,UART_TX_BUFER[t]);
		while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);		       
	}
}

void voice_sy1(char data[7])        //ʹ�ý����ж�ʱ��ʹ���������
{

			u16 len;
			u16 t;
			//u8 i;
			char s[40];
			//u8 data1t[4];
//			char data1a=data[4];
//			char data1b=data[5];
//			char data1c=data[6];
	
			char  UART_TX_BUFER[50]={0};
			
//			for(i=0;i<4;i++)
//			{
//			    data1t[i]=data[i];
//			}
			
			sprintf((char*)s,"����Ҫ��aҩ%d�ţ�bҩ%d�ţ�cҩ%d��",data[4]-48,(int)data[5]-48,(int)data[6]-48);
			
			len=strlen(s);
			
			
			UART_TX_BUFER[0] = 0xFD ; 			//����֡ͷFD
			UART_TX_BUFER[1] = 0x00 ; 			//�������������ȵĸ��ֽ�
			UART_TX_BUFER[2] = len+2; 	    //�������������ȵĵ��ֽ�
			UART_TX_BUFER[3] = 0x01 ; 			//���������֣��ϳɲ�������		 		 
			UART_TX_BUFER[4] = 0x01;           //�ı������ʽ��GBK
			memcpy(&UART_TX_BUFER[5], s, len);
			for(t=0;t<(len+5);t++)
			{
				USART_SendData(UART4,UART_TX_BUFER[t]);
				while(USART_GetFlagStatus(UART4,USART_FLAG_TC)!=SET);			
			}
			
		
}
