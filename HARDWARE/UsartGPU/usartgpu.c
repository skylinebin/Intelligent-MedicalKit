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
			 USART_SendData(USART1, gbuf[i]);  //����һ��byte������
			while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}; //�ȴ����ͽ���
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
	//�����û���ʱ��������ҩ�����������Ԥ��װ�ÿ��Ա�֤ʹ���ߵĽ�����ȫ��
	delay_ms(400);


}
