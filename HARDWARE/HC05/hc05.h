#ifndef __HC05_H
#define __HC05_H	 
#include "sys.h" 


void HC05_Send(char *str); //����һ���ַ���������С��200  
void HC05_TimingSend(char *str);//��ʱ�����ַ���
void HC05_TimingOn(void);//��������ʱ��������
void HC05_TimingOff(void);//�ر�������ʱ��������

u8 HC05_GetStr(char *str);//�յ�ָ���ַ���ʱ����1
   
#endif  
















