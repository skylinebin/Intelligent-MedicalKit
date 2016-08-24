#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途

//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
int USART1_Receive(const char *str);
void recvchar(u8 gc);
extern char cmd[8];     //命令缓冲区，存放[]中传来的命令,靠cjs进行位置累加字符串
extern u8 cjs;	        //cjs:cmd命令计数
extern u8 iscmd;		//==1 表示处于[]内部，cmd记录中
extern u8 iscmdok;	//==1 表示有命令处理
extern u8 kbuf[16];     //组态键盘输入缓冲区，由于最多可以输入15位，因此长度16
extern u8 kjs;         //用于存储 kbuf 记录位置，kbuf的计数变量
extern u8 kcmd;      //==1 表示处在{} 内部的记录中
//extern u8 n;

extern void getbn(void);

#endif


