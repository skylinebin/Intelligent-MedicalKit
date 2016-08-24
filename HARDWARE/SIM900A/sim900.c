#include "sim900.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"   	 
	 	 	 	 	 
#include "string.h"    		
#include "usart3.h" 



//sim900a发送命令后,检测接收到的应答
//str:期待的应答结果
//返回值:0,没有得到期待的应答结果
//    其他,期待应答结果的位置(str的位置)
u8* sim900a_check_cmd(u8 *str)
{
	char *strx=0;
	if(USART3_RX_STA&0X8000)		//接收到一次数据了
	{ 
		USART3_RX_BUF[USART3_RX_STA&0X7FFF]=0;//添加结束符
		strx=strstr((const char*)USART3_RX_BUF,(const char*)str);
	} 
	return (u8*)strx;
}
//向sim900a发送命令
//cmd:发送的命令字符串(不需要添加回车了),当cmd<0XFF的时候,发送数字(比如发送0X1A),大于的时候发送字符串.
//ack:期待的应答结果,如果为空,则表示不需要等待应答
//waittime:等待时间(单位:10ms)
//返回值:0,发送成功(得到了期待的应答结果)
//       1,发送失败
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u16 waittime)
{
	u8 res=0; 
	USART3_RX_STA=0;
	if((u32)cmd<=0XFF)
	{
		while((USART3->SR&0X40)==0);//等待上一次数据发送完成  
		USART3->DR=(u32)cmd;
	}
	else 
	u3_printf("%s\r\n",cmd);//发送命令
	if(ack&&waittime)		//需要等待应答
	{
		while(--waittime)	//等待倒计时
		{
			delay_ms(10);
			if(USART3_RX_STA&0X8000)//接收到期待的应答结果
			{
				if(sim900a_check_cmd(ack))break;//得到有效数据 
				USART3_RX_STA=0;
			} 
		}
		if(waittime==0)res=1; 
	}
	return res;
} 
//将1个字符转换为16进制数字
//chr:字符,0~9/A~F/a~F
//返回值:chr对应的16进制数值
u8 sim900a_chr2hex(u8 chr)
{
	if(chr>='0'&&chr<='9')return chr-'0';
	if(chr>='A'&&chr<='F')return (chr-'A'+10);
	if(chr>='a'&&chr<='f')return (chr-'a'+10); 
	return 0;
}
//将1个16进制数字转换为字符
//hex:16进制数字,0~15;
//返回值:字符
u8 sim900a_hex2chr(u8 hex)
{
	if(hex<=9)return hex+'0';
	if(hex>=10&&hex<=15)return (hex-10+'A'); 
	return '0';
}


//unicode gbk 转换函数
//src:输入字符串
//dst:输出(uni2gbk时为gbk内码,gbk2uni时,为unicode字符串)

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
	
	*dst=0;//添加结束符
} 

//测试短信发送内容(70个字[UCS2的时候,1个字符/数字都算1个字])
//const u8* test_msg="662F4E0D662F50BB";//预先存入中文短信的Unicode--是不是傻
//const u8* test_phonenum="00310033003000300036003100370030003500300036";//预存的手机号码的Unicode


/***
//SIM900A发短信测试 
void sim900a_sms_send_test(u8 phonenum[])
{
	
//	u8 phonenum[]="13006170506";
	u8 phoneunicode[80]="";
	u8 textmsg[]="662F4E0D662F50BB";
	u8 text[80];
	char *p;
//    p=textnum;//p指针指向textnum数组
	p=phoneunicode;//p指针指向phoneunicode数组
	
    sim900a_unigbk_exchange(phonenum,phoneunicode); //手机号码转码

	sprintf(text,"AT+CMGS=\"%s\"",p);              //p指向手机号码的ucode，text为发送号码指令	
	if(sim900a_send_cmd(text,">",200)==0)					//发送短信命令+电话号码
	  { 		 				 													 
		u3_printf("%s",textmsg);		 						//发送短信内容p1到GSM模块 
 		if(sim900a_send_cmd((u8*)0X1A,"+CMGS:",1000)==0)
		  LED0=~LED0;//发送结束符,等待发送完成(最长等待10秒钟,因为短信长了的话,等待时间会长一些)
		  
	  }  
	USART3_RX_STA=0;   
	delay_ms(10);

	
} 

//sim900a短信测试
//用于读短信或者发短信
//返回值:0,正常
//    其他,错误代码
u8 sim900a_sms_test(void)
{
  
	if(sim900a_send_cmd("AT+CMGF=1","OK",200)) 
		return 1;
//	else 
//		LED1=~LED1;

   if(sim900a_send_cmd("AT+CSMP=17,167,2,25","OK",200)) 
	   return 2;
    //设置短消息文本模式参数 
//   else
//	   LED1=~LED1;

    if(sim900a_send_cmd("AT+CSCS=\"UCS2\"","OK",200)) 
		return 3;
//	else
//		LED1=~LED1;

	sim900a_sms_send_test('13006170506');//号码设置，发送ucode
	delay_ms(10);
//	sim900a_send_cmd("AT+CSCS=\"GSM\"","OK",200);				//设置默认的GSM 7位缺省字符集
	return 0;
} 
***/

u8 sim900a_send_text(u8 phonenum[])
{

	u8 phoneunicode[80]="";
	u8 textmsg[]="53D1751F7D27602560C551B597008981655163F4";
	u8 text[80];
	char *p;
//    p=textnum;//p指针指向textnum数组
	p=phoneunicode;//p指针指向phoneunicode数组

	if(sim900a_send_cmd("AT+CMGF=1","OK",200)) 
		return 1;


   if(sim900a_send_cmd("AT+CSMP=17,167,2,25","OK",200)) 
	   return 2;
	//设置短消息文本模式参数 

	if(sim900a_send_cmd("AT+CSCS=\"UCS2\"","OK",200)) 
		return 3;
	
	
	sim900a_unigbk_exchange(phonenum,phoneunicode); //手机号码转码

	sprintf(text,"AT+CMGS=\"%s\"",p);              //p指向手机号码的ucode，text为发送号码指令	
	if(sim900a_send_cmd(text,">",200)==0)					//发送短信命令+电话号码
	  { 		 				 													 
		u3_printf("%s",textmsg);		 						//发送短信内容p1到GSM模块 
		if(sim900a_send_cmd((u8*)0X1A,"+CMGS:",1000)==0)
		  LED0=~LED0;//发送结束符,等待发送完成(最长等待10秒钟,因为短信长了的话,等待时间会长一些)
		  
	  }  
	USART3_RX_STA=0;   
	delay_ms(10);
	  
	return 0;


}



void sim900a_init(void)
{
	while(sim900a_send_cmd("AT","OK",100))//检测是否应答AT指令 
	{   

		delay_ms(800);
	} 

//	if(sim900a_send_cmd("ATE0","OK",200)==0)   LED1=~LED1;//关闭回显
		sim900a_send_cmd("ATE0","OK",200)==0;

}
