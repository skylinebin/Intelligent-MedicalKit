#include "sim900.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
	 	 	 	 	 
#include "string.h"    		
#include "usart3.h" 



//sim900a���������,�����յ���Ӧ��
//str:�ڴ���Ӧ����
//����ֵ:0,û�еõ��ڴ���Ӧ����
//    ����,�ڴ�Ӧ������λ��(str��λ��)
u8* sim900a_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//���յ�һ��������
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//��ӽ�����
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//��sim900a��������
//cmd:���͵������ַ���(����Ҫ��ӻس���),��cmd<0XFF��ʱ��,��������(���緢��0X1A),���ڵ�ʱ�����ַ���.
//ack:�ڴ���Ӧ����,���Ϊ��,���ʾ����Ҫ�ȴ�Ӧ��
//waittime:�ȴ�ʱ��(��λ:10ms)
//����ֵ:0,���ͳɹ�(�õ����ڴ���Ӧ����)
//       1,����ʧ��
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART3_RX_STA=0;
	if((u32)cmd<=0XFF)
	{
		while((USART3->SR&0X40)==0);//�ȴ���һ�����ݷ������  
		USART3->DR=(u32)cmd;
	}
	else 
	u3_printf("%s\r\n",cmd);//��������
	if(ack&&waittime)		//��Ҫ�ȴ�Ӧ��
	{
		while(--waittime)	//�ȴ�����ʱ
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//���յ��ڴ���Ӧ����
			{
				if(sim900a_check_cmd(ack))break;//�õ���Ч���� 
				USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//��1���ַ�ת��Ϊ16��������
//chr:�ַ�,0~9/A~F/a~F
//����ֵ:chr��Ӧ��16������ֵ
u8 sim900a_chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}
//��1��16��������ת��Ϊ�ַ�
//hex:16��������,0~15;
//����ֵ:�ַ�
u8 sim900a_hex2chr(u8 hex)
{
	if(hex<=9)return hex+'0';
	if(hex>=10&&hex<=15)return (hex-10+'A'); 
	return '0';
}


//unicode gbk ת������
//src:�����ַ���
//dst:���(uni2gbkʱΪgbk����,gbk2uniʱ,Ϊunicode�ַ���)

void sim900a_unigbk_exchange(u8 *src,u8 *dst)
{
//	u8 temp; 
//	u8 buf[2];
		while(*src!=0)
		{
//				src++;
		
			*dst++=sim900a_hex2chr(0);
			*dst++=sim900a_hex2chr(0);
			*dst++=sim900a_hex2chr(3);
			*dst++=*src;
			src++;
		}
	
	*dst=0;//��ӽ�����
} 

//���Զ��ŷ�������(70����[UCS2��ʱ��,1���ַ�/���ֶ���1����])
//const u8* test_msg="662F4E0D662F50BB";//Ԥ�ȴ������Ķ��ŵ�Unicode--�ǲ���ɵ
//const u8* test_phonenum="00310033003000300036003100370030003500300036";//Ԥ����ֻ������Unicode


/***
//SIM900A�����Ų��� 
void sim900a_sms_send_test(u8 phonenum[])
{
	
//	u8 phonenum[]="13006170506";
	u8 phoneunicode[80]="";
	u8 textmsg[]="662F4E0D662F50BB";
	u8 text[80];
	char *p;
//    p=textnum;//pָ��ָ��textnum����
	p=phoneunicode;//pָ��ָ��phoneunicode����
	
    sim900a_unigbk_exchange(phonenum,phoneunicode); //�ֻ�����ת��

	sprintf(text,"AT+CMGS=\"%s\"",p);              //pָ���ֻ������ucode��textΪ���ͺ���ָ��	
	if(sim900a_send_cmd(text,">",200)==0)					//���Ͷ�������+�绰����
	  { 		 				 													 
		u3_printf("%s",textmsg);		 						//���Ͷ�������p1��GSMģ�� 
 		if(sim900a_send_cmd((u8*)0X1A,"+CMGS:",1000)==0)
		  LED0=~LED0;//���ͽ�����,�ȴ��������(��ȴ�10����,��Ϊ���ų��˵Ļ�,�ȴ�ʱ��᳤һЩ)
		  
	  }  
	USART3_RX_STA=0;   
	delay_ms(10);

	
} 

//sim900a���Ų���
//���ڶ����Ż��߷�����
//����ֵ:0,����
//    ����,�������
u8 sim900a_sms_test(void)
{
  
	if(sim900a_send_cmd("AT+CMGF=1","OK",200)) 
		return 1;
//	else 
//		LED1=~LED1;

   if(sim900a_send_cmd("AT+CSMP=17,167,2,25","OK",200)) 
	   return 2;
    //���ö���Ϣ�ı�ģʽ���� 
//   else
//	   LED1=~LED1;

    if(sim900a_send_cmd("AT+CSCS=\"UCS2\"","OK",200)) 
		return 3;
//	else
//		LED1=~LED1;

	sim900a_sms_send_test('13006170506');//�������ã�����ucode
	delay_ms(10);
//	sim900a_send_cmd("AT+CSCS=\"GSM\"","OK",200);				//����Ĭ�ϵ�GSM 7λȱʡ�ַ���
	return 0;
} 
***/

u8 sim900a_send_text(u8 phonenum[])
{

	u8 phoneunicode[80]="";
	u8 textmsg[]="53D1751F7D27602560C551B597008981655163F4";
	u8 text[80];
	char *p;
//    p=textnum;//pָ��ָ��textnum����
	p=phoneunicode;//pָ��ָ��phoneunicode����

	if(sim900a_send_cmd("AT+CMGF=1","OK",200)) 
		return 1;


   if(sim900a_send_cmd("AT+CSMP=17,167,2,25","OK",200)) 
	   return 2;
	//���ö���Ϣ�ı�ģʽ���� 

	if(sim900a_send_cmd("AT+CSCS=\"UCS2\"","OK",200)) 
		return 3;
	
	
	sim900a_unigbk_exchange(phonenum,phoneunicode); //�ֻ�����ת��

	sprintf(text,"AT+CMGS=\"%s\"",p);              //pָ���ֻ������ucode��textΪ���ͺ���ָ��	
	if(sim900a_send_cmd(text,">",200)==0)					//���Ͷ�������+�绰����
	  { 		 				 													 
		u3_printf("%s",textmsg);		 						//���Ͷ�������p1��GSMģ�� 
		if(sim900a_send_cmd((u8*)0X1A,"+CMGS:",1000)==0)
		  LED0=~LED0;//���ͽ�����,�ȴ��������(��ȴ�10����,��Ϊ���ų��˵Ļ�,�ȴ�ʱ��᳤һЩ)
		  
	  }  
	USART3_RX_STA=0;   
	delay_ms(10);
	  
	return 0;


}



void sim900a_init(void)
{
	while(sim900a_send_cmd("AT","OK",100))//����Ƿ�Ӧ��ATָ�� 
	{   

		delay_ms(800);
	} 

//	if(sim900a_send_cmd("ATE0","OK",200)==0)   LED1=~LED1;//�رջ���
		sim900a_send_cmd("ATE0","OK",200)==0;

}
