#ifndef __UART4_H
#define __UART4_H

#include "stdio.h"	
#include "sys.h" 

#define UART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_UART4_RX 			1		//使能（1）/禁止（0）串口4接收

extern u8  UART_RX_BUF[UART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符
extern u16 UART_RX_STA;         		//接收状态标记	

void uart4_init(u32 bound);

#endif

