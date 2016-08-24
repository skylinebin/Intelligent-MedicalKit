#include "usartgpu.h"
#include "sys.h"
#include "usart.h"	
#include "delay.h"
#include "vipcode.h"

void SendGPU_data(char *gbuf)
{

	u8 i=0;
	while(1)
	{
		if(gbuf[i]!=0)
		{
			 USART_SendData(USART1, gbuf[i]);  //发送一个byte到串口
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}; //等待发送结束
			i++;
		}
		else 
		return;
	
	}
}

void usartgpu_init(void)
{
//	delay_ms(800);
//	printf(Welcome);
	delay_ms(5000);
	printf("CLS(7);SPG(1);\r\n");
	//提醒用户定时定量服用药物，并带有智能预警装置可以保证使用者的健康安全。
	delay_ms(400);


}
