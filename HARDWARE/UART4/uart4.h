#ifndef __UART4_H
#define __UART4_H

#include "stdio.h"	
#include "sys.h" 

#define UART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_UART4_RX 			1		//ʹ�ܣ�1��/��ֹ��0������4����

extern u8  UART_RX_BUF[UART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з�
extern u16 UART_RX_STA;         		//����״̬���	

void uart4_init(u32 bound);

#endif

