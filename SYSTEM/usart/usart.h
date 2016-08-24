#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;

//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);
int USART1_Receive(const char *str);
void recvchar(u8 gc);
extern char cmd[8];     //������������[]�д���������,��cjs����λ���ۼ��ַ���
extern u8 cjs;	        //cjs:cmd�������
extern u8 iscmd;		//==1 ��ʾ����[]�ڲ���cmd��¼��
extern u8 iscmdok;	//==1 ��ʾ�������
extern u8 kbuf[16];     //��̬�������뻺��������������������15λ����˳���16
extern u8 kjs;         //���ڴ洢 kbuf ��¼λ�ã�kbuf�ļ�������
extern u8 kcmd;      //==1 ��ʾ����{} �ڲ��ļ�¼��
//extern u8 n;

extern void getbn(void);

#endif


