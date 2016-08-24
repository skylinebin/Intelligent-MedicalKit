/********************************************************
名称：蓝牙发送模块
功能：按下KEY0键时，开启发送任务，每8秒发送1次，最多发送3次，
     按下KEY1时，强制停止发送任务，（转入语音播报功能）
	 KEY0键可用RTC闹钟中断代替
硬件：KEY0，KEY1作为输入条件，LED灯指示按键是否按下
     串口2 波特率9600 PA3 U2_RX  PA2 U2_TX
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

u8 flagsendon=0;//发送开启标志位
u8 flageat=0;//是否该吃药标志位
u8 flagkeyoff=0;//强制关发送标志位
  	
u8 reclen=0; //接收字符串长度

void HC05_Send(char *str)
{
   u2_printf(str);		//发送到蓝牙模块		   
				 	
}	 

void HC05_TimingSend(char *str)//定时发送字符串
{
	  if(flagsendon==1)
	   {
	      u2_printf(str);		//发送到蓝牙模块		   
		   flagsendon=0;
	   }
}

void HC05_TimingOn(void)   //打开蓝牙定时发送任务
{
	 flageat=1;	
	   	
}


void HC05_TimingOff(void)//关闭蓝牙定时发送任务，并播放语音
{
	  flagkeyoff=1;

	
       /***************************
		此处可添加语音播报任务   		   
       ****************************/
	
}

u8 HC05_GetStr(char *str)//收到指定字符串时置1
{
	   u8 recflag=0;
	
	if(USART2_RX_STA&0X8000)			//接收到一次数据了
	   {
		   
 		reclen=USART2_RX_STA&0X7FFF;	//得到数据长度
		USART2_RX_BUF[reclen]=0;	 	//加入结束符         
 		USART2_RX_STA=0;	     						
		if(strcmp((const char*)USART2_RX_BUF,str)==0)
			recflag=1;	
		
       }
	  return recflag;
}	


		    














