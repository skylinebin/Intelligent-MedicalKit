#ifndef __HC05_H
#define __HC05_H	 
#include "sys.h" 


void HC05_Send(char *str); //发送一个字符串，长度小于200  
void HC05_TimingSend(char *str);//定时发送字符串
void HC05_TimingOn(void);//打开蓝牙定时发送任务
void HC05_TimingOff(void);//关闭蓝牙定时发送任务

u8 HC05_GetStr(char *str);//收到指定字符串时返回1
   
#endif  
















