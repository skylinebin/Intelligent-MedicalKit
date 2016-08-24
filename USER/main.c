#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usartgpu.h"
#include "rtc.h"
#include "drugchoose.h"
#include "hc05.h"
#include "usart2.h"
#include "timer.h"
#include "XFS5152CE.h"
#include "uart4.h"
#include "usart3.h"
#include "sim900.h"


vu8 AlmGetHour[3];//�����õ����ӱ�������
vu8 AlmGetMin[3];

vu8 AlmHour[3]={0,0,0};    //����3�����ӱ���������С��������
vu8 AlmMin[3]={0,0,0};	 //3������ֱ�Ϊ17:00,8:30,4:00
   u8 nnday,nnhour,nnmin;    //����ı䷽ʽ����	
vu8 qsmhour;
vu8 qsmmin;
vu8 alarmstate;
void AlarmRank(void);
void AlarmSelect(void);




    char cmd[8];     //������������[]�д���������,��cjs����λ���ۼ��ַ���
	u8 cjs=0;	        //cjs:cmd�������
	u8 iscmd=0;		//==1 ��ʾ����[]�ڲ���cmd��¼��
	u8 iscmdok=0;	//==1 ��ʾ�������
	
	u8 kbuf[16];     //��̬�������뻺��������������������15λ����˳���16
	u8 kjs=0;         //���ڴ洢 kbuf ��¼λ�ã�kbuf�ļ�������
	u8 kcmd=0;      //==1 ��ʾ����{} �ڲ��ļ�¼��
	
	u8 n=0;
	u8 timestate;//��������ʱ��״̬
	u8 inputstate;//�ж��Ƿ��ڼ�������״̬

	u8 phonenum[16];

	u8 voicebegin=0;
	u8 voicecount=0;

void getbn(void)
{
	n=0;
   if(iscmdok==1)
	{
		if ((cmd[0]=='B') & (cmd[1]=='N'))
		{	n=cmd[3]-0x30;
			if ((cmd[4]>=0x30) & (cmd[4]<=0x39))
			{
				n=n*10+cmd[4]-0x30;
			}
		}
		iscmdok=0;
	}
	
}


int main(void)
 {	
	 
//	 u8 len;
//	 u8 t;
	 u8 sortc;//����ҩƷ�������

	 
	
	vu8 qsm;//���ڶԴ洢ҩƷ����������

	 
	 char getdata[]="";
	 char putsorc[]="";
	 char putsorcqst[]="";
	 char putsorcqss[]="";

	 char besaved[80]="";
	char besavedtwo[80]="";
	char besavedthree[80]="";
	char besavedfour[80]="";
	char besaveds[50]="";
	

	
    char whenone[80]="";
	char whentwo[80]="";
	char whenthree[80]="";
	
	 char QS[40]="";
	

	//����ʱ������
	u16 getyear=2016;
	u8 getmon=2;
	u8 getday=20;
	u8 gethour=12;
	u8 getmin=10;
	u8 getsec=10;
	
	 


	 u8 getnum;
	 u8 timeh0;
	 u8 timeh1;
	 u8 timem0;
	 u8 timem1;
	 
	 u8 timeoh0=0;
	 u8 timeoh1=0;
	 u8 timeom0=0;
	 u8 timeom1=0;
	 u8 timeoh;
	 u8 timeom;
	
	 u8 timeth0=0;
	 u8 timeth1=0;
	 u8 timetm0=0;
	 u8 timetm1=0;
	 u8 timeth;
	 u8 timetm;
	
	 u8 timehh0=0;
	 u8 timehh1=0;
	 u8 timehm0=0;
	 u8 timehm1=0;
	 u8 timehh;
	 u8 timehm;


	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	
	//����������ʱ�ʹ���
	TIM3_Int_Init(4999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	USART2_Init(9600);	//��ʼ������2Ϊ:9600,������. 
	usart3_init(9600);     //��ʼ������3������GSMͨ��
	
	 uart4_init(9600);//һ��Ҫ�ȳ�ʼ��һ�£���ΪҪʹ�ܣ����ܴ����ж�

	 usartgpu_init();
	 delay_ms(2000);

	 inputstate=0;
	 timestate=0;
	 qsm=0;
	 cleardrug();//��ҩƷ�������
	 
	 while(RTC_Init());//RTC init ��must succeed!!	
	 
	 RTC_timechange(2016,2,27,19,19,40);   //���ô˺�����������ϵͳʱ��
	 AlarmRank();//�����3�����ӱ������Ⱥ�˳������
	AlarmSelect();//��ϵͳʱ����3�����ӱȽϣ�׼����һ������    
	RTC_Alarm_Set(calendar.w_year,calendar.w_month,calendar.w_date,nnhour,nnmin,0); 
	

	 
	while(1)
	{
	
		AlarmSelect();//��ϵͳʱ����3�����ӱȽϣ�׼����һ������    
		getyear=calendar.w_year;
		getmon=calendar.w_month;
		getday=calendar.w_date;
		gethour=calendar.hour;
		getmin=calendar.min;
		getsec=calendar.sec;
		
		if(HC05_GetStr("NEEDAID\r\n")==1)
		{
			
		sim900a_init();//�ȴ�SIM900A����ע��ɹ� ���õ�ʱ���ٳ�ʼ��
		sim900a_send_text(phonenum);

		}
		
		
		delay_ms(50);
		 getbn();
		 if(USART_RX_STA&0x8000)
		{	
		

	    USART_RX_STA=0;
		
			
			if(inputstate==0)
			{
				//��ʱ���ڳ�ʼ������
//				getbn();
				if(n==10 | USART1_Receive("[BN:10]"))
				{
					printf("CLS(7);SPG(2);\r\n");//��ת���˵�

					inputstate=1;
				
				}

		   }
			
		   else if(inputstate==1)
		   {
			   //�ڲ˵�������
//			   	getbn();

			   	if(n==3 | USART1_Receive("[BN:3]"))
				{

					//��������ʱ��ѡҩ����
					printf("CLS(7);BPIC(1,0,0,11);PS16(1,5,20,'�밴��ɫ�������ʱ������,��ʱ��ȷ����ֱ�Ӱ�ʱ����ȷ�ϼ�',1);");//�������ҩ�﹦�ܣ��Ƚ������ʱ��
					sprintf(putsorc,"PS24(1,90,84,'ʱ��1:',0);SXY(160,80);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(1,0,0,118,30,1,39);SXY(0,0);PIC(315,60,23);BTN(11,314,60,375,120,0,46);",timeoh0,timeoh1,timeom0,timeom1);
					printf(putsorc);
					sprintf(putsorcqst,"PS24(1,90,164,'ʱ��2:',0);SXY(160,160);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(2,0,0,118,30,1,39);SXY(0,0);PIC(315,140,23);BTN(12,314,140,375,200,0,47);",timeth0,timeth1,timetm0,timetm1);
				    printf(putsorcqst);
					sprintf(putsorcqss,"PS24(1,90,244,'ʱ��3:',0);SXY(160,240);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(3,0,0,118,30,1,41);SXY(0,0);PIC(315,220,23);BTN(13,314,220,375,280,0,46);",timehh0,timehh1,timehm0,timehm1);//timethree[3]-'0'
					printf(putsorcqss);
					printf("TPN(2);SXY(0,0);PIC(13,250,18);BTN(4,13,250,71,309,0,42);\r\n");
					
					inputstate=2;
				}
				else if(n==4 | USART1_Receive("[BN:4]"))
				{

					//����鿴ҩ��Ĺ��ܽ���
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,180,10,'�鿴ҩ��',2);PIC(13,220,18);BTN(2,13,220,71,279,0,130);"); 
					if(qsm>0)
					{
						sprintf(besaveds,"PS24(1,20,60,'����ӵ�ҩ���У�',0);PS16(1,320,60,'����� %d ��ҩ�� ',2);",qsm);
						printf(besaveds);
						if(getnonzero(drug_t1)!=0)
							printf(besaved);
						if(getnonzero(drug_t2)!=0)
							printf(besavedtwo);
						if(getnonzero(drug_t3)!=0)
							printf(besavedthree);	
//							printf(besavedfour);
						
								
					}
					else
					{		
						printf("PS24(1,2,120,'��δ����κ�ҩ����ڲ˵��������ҩ��',1);");

					}
					printf("\r\n");
					inputstate=1;
					
					
				
				}
				else if(n==5|USART1_Receive("[BN:5]"))
				{
					//��������ʱ��Ĺ��ܽ���


						printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'����ʱ��Ϊ��',3);");
						sprintf(putsorc,"SXY(50,60);PS24(1,0,30,'����: %d��%d��%d�� ',0);BTN(1,248,20,396,60,0,39);SXY(0,0);PIC(300,80,22);",calendar.w_year,calendar.w_month,calendar.w_date);
						printf(putsorc);
						sprintf(putsorcqss,"SXY(80,150);PS24(1,0,2,'ʱ��: %d:%d:%d',0);BTN(2,218,0,366,40,0,39);SXY(0,0);PIC(300,150,20);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",calendar.hour,calendar.min,calendar.sec);
						printf(putsorcqss);
						printf("\r\n");
						inputstate=8;
				}
				else if(n==6|USART1_Receive("[BN:6]"))
				{
					//����鿴���ӵĹ��ܽ���
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,180,10,'�鿴����',2);PIC(13,220,18);BTN(2,13,220,71,279,0,130);");
						sprintf(putsorc,"SXY(160,140);PS24(1,0,10,'����һ: %d :%d ',0);SXY(0,0);",AlmHour[0],AlmMin[0]);
					    printf(putsorc);
						
						sprintf(putsorc,"SXY(160,180);PS24(1,0,10,'���Ӷ�: %d :%d ',0);SXY(0,0);",AlmHour[1],AlmMin[1]);
					    printf(putsorc);

						sprintf(putsorc,"SXY(160,220);PS24(1,0,10,'������: %d :%d ',0);SXY(0,0);",AlmHour[2],AlmMin[2]);
					    printf(putsorc);	

					
					   sprintf(putsorc,"SXY(130,80);PS24(1,0,10,'��һ������: %d :%d ',0);SXY(0,0);",nnhour,nnmin);
					   printf(putsorc);	

						printf("\r\n");
						inputstate=1;
					
//					 sim900a_send_text(phonenum);
//					�����ò鿴����ʱ���з��Ͷ��ţ�ʵ���ǽ��յ������Ľ����ַ���ʱ���Ͷ���
				}
				else if(n==7|USART1_Receive("[BN:7]"))
				{
					printf("CLS(7);BPIC(1,0,0,11);");

					if(phonenum[0]==0)
					{
						printf(	"PS24(1,120,60,'Ŀǰδ�󶨺���',0);");
					}
					else
					{
						sprintf(putsorc,"SXY(20,60);PS24(1,0,10,'�Ѱ󶨺���: %s',0);SXY(0,0);",phonenum);
						printf(putsorc);
					}
//PS24(1,15,261,'����',1);BTN(5,13,260,71,289,1,48);	PS24(1,165,120,'ȷ��',1);BTN(11,164,118,210,146,1,46);				
					sprintf(putsorcqss,"PIC(170,140,21);SXY(120,140);BTN(1,50,0,200,40,0,39);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",phonenum);
					printf(putsorcqss);
					printf("\r\n");
					inputstate=13;
				
				}

		   }

		  else if(inputstate==2)
		   {
			   //���ʱ�������
//			   	getbn();
				if(n==1 |USART1_Receive("[BN:1]"))
				{
					timestate=1;
					
					printf("CLS(7);SPG(10);\r\n");
					inputstate=3;
				
				}
				else if(n==2 |USART1_Receive("[BN:2]"))
				{
					timestate=2;
					printf("CLS(7);SPG(10);\r\n");
					inputstate=3;
		
				}
				else if(n==3|USART1_Receive("[BN:3]"))
				{
					timestate=3;
					
					printf("CLS(7);SPG(10);\r\n");
					inputstate=3;

				}
				else if(n==4 |USART1_Receive("[BN:4]"))
				{
					printf("CLS(7);SPG(2);\r\n");
					inputstate=1;
				
				}
				else if(n==11 |USART1_Receive("[BN:11]"))
				{
					timestate=1;
					printf("CLS(7);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timeoh0;
					timeh1=timeoh1;
					timem0=timeom0;
					timem1=timeom1;	
					timeoh=10*timeoh0+timeoh1;
					timeom=10*timeom0+timeom1;
					
					AlmHour[0]=timeoh;
					AlmMin[0]=timeom;
					
					drug_t.hour=timeoh;
					drug_t.min=timeom;
				
				}				
				else if(n==12 |USART1_Receive("[BN:12]"))
				{
					timestate=2;
					printf("CLS(7);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timeth0;
					timeh1=timeth1;
					timem0=timetm0;
					timem1=timetm1;	
					timeth=10*timeth0+timeth1;
					timetm=10*timetm0+timetm1;
					
					AlmHour[1]=timeth;
					AlmMin[1]=timetm;
					drug_t.hour=timeth;
					drug_t.min=timetm;
					
				}
				else if(n==13 |USART1_Receive("[BN:13]"))
				{
					timestate=3;
					printf("CLS(7);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timehh0;
					timeh1=timehh1;
					timem0=timehm0;
					timem1=timehm1;	
					timehh=10*timehh0+timehh1;
					timehm=10*timehm0+timehm1;
					
					AlmHour[2]=timehh;
					AlmMin[2]=timehm;
					drug_t.hour=timehh;
					drug_t.min=timehm;
					
				}
				
				AlarmRank();//�����3�����ӱ������Ⱥ�˳������
				AlarmSelect();//��ϵͳʱ����3�����ӱȽϣ�׼����һ������    
				RTC_Alarm_Set(calendar.w_year,calendar.w_month,calendar.w_date,nnhour,nnmin,0);
				

		   }
		    else if(inputstate==3)
			{

//				getbn();

				if(n==14 |USART1_Receive("[BN:14]"))
					{
						timeh0=kbuf[0]-0x30;
						timeh1=kbuf[1]-0x30;
						timem0=kbuf[2]-0x30;
						timem1=kbuf[3]-0x30;

						
						printf("CLS(7);BPIC(1,0,0,11);PS24(1,130,10,'ѡ���ҩʱ��',0);PS24(1,40,60,'�밴��ɫ�������ʱ������',1);");
						sprintf(putsorc,"PS24(1,40,80,'ʱ�� %d',1);SXY(160,120);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);SXY(0,0);",timestate,timeh0,timeh1,timem0,timem1);
						printf(putsorc);
						printf("PIC(13,220,18);BTN(16,13,220,71,279,0,64);PIC(315,220,23);BTN(18,314,220,375,280,0,69);\r\n");

						inputstate=3;
						
					if(timestate==1)
						{
//							onecount++;//It's wrong ,maybe it selects ȷ�� straightly
							
							timeoh0=timeh0;
							timeoh1=timeh1;
							timeom0=timem0;
							timeom1=timem1;	
							
							timeoh=10*timeoh0+timeoh1;
							timeom=10*timeom0+timeom1;	
							
							AlmHour[0]=timeoh;
							AlmMin[0]=timeom;
							
							drug_t.hour=timeoh;
							drug_t.min=timeom;
//							sprintf(whenone,"%d%d%d%d%d%d%d",onecount,timeh0,timeh1,timem0,timem1,sortc,getnum);
						
						}
						
						else if(timestate==2)
						{
							timeth0=timeh0;
							timeth1=timeh1;
							timetm0=timem0;
							timetm1=timem1;	

							timeth=10*timeth0+timeth1;
							timetm=10*timetm0+timetm1;	
							
							AlmHour[1]=timeth;
							AlmMin[1]=timetm;	
							
							drug_t.hour=timeth;
							drug_t.min=timetm;
							
//							sprintf(whentwo,"t%d%d%d%d%d%d",timeh0,timeh1,timem0,timem1,sortc,getnum);
						
						}
						else if(timestate==3)
						{
							timehh0=timeh0;
							timehh1=timeh1;
							timehm0=timem0;
							timehm1=timem1;	

							timehh=10*timehh0+timehh1;
							timehm=10*timehm0+timehm1;
							
							AlmHour[2]=timehh;
							AlmMin[2]=timehm;
							
							drug_t.hour=timehh;
							drug_t.min=timehm;
//							sprintf(whenthree,"t%d%d%d%d%d%d",timeh0,timeh1,timem0,timem1,sortc,getnum);
						
						}
						
						AlarmRank();//�����3�����ӱ������Ⱥ�˳������
						AlarmSelect();//��ϵͳʱ����3�����ӱȽϣ�׼����һ������    
						RTC_Alarm_Set(calendar.w_year,calendar.w_month,calendar.w_date,nnhour,nnmin,0);
						
					}	
					
			 else if(n==16 | USART1_Receive("[BN:16]"))
				{
				  printf("CLS(7);SPG(2);\r\n");//�������ҩ�﹦�ܣ��Ƚ������ʱ��
				  inputstate=1;

				}
				
				//���ڵڶ���ȷ�������ʱ��
			else if(n==18 |USART1_Receive("[BN:18]"))
				{
				   inputstate=5;
				   printf("CLS(7);SPG(4);\r\n");//�������ҩ�﹦�ܣ��Ƚ������ʱ��
				  
				}
				

			}

		   else if(inputstate==5)
		   {

//				getbn();

			  if(n==6| USART1_Receive("[BN:6]"))
			  {
					sortc=1;
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'�����ÿ�η��ø�ҩƷ�ļ���',0);PS24(1,10,140,'ÿ�η��õļ���Ϊ_____��',0);BTN(3,200,140,266,179,2,45);PIC(13,220,18);BTN(4,13,220,71,279,0,69);TPN(2);");
					sprintf(putsorc,"PIC(160,60,%d);PS24(1,150,100,'ҩƷ %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				  
				   inputstate=6;
				   drug_t.count=1;
//					drug_sort=1;
				
			  
			  }		
		    else if(n==7| USART1_Receive("[BN:7]"))
			  {
					sortc=2;
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'�����ÿ�η��ø�ҩƷ�ļ���',0);PS24(1,10,140,'ÿ�η��õļ���Ϊ_____��',0);BTN(3,200,140,266,179,2,45);PIC(13,220,18);BTN(4,13,220,71,279,0,69);TPN(2);");
					sprintf(putsorc,"PIC(160,60,%d);PS24(1,150,100,'ҩƷ %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				  
				   drug_t.count=2;
				  
				   inputstate=6;
				   
			  
			  }	
			else if(n==8| USART1_Receive("[BN:8]"))
			  {
					sortc=3;
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'�����ÿ�η��ø�ҩƷ�ļ���',0);PS24(1,10,140,'ÿ�η��õļ���Ϊ_____��',0);BTN(3,200,140,266,179,2,45);PIC(13,220,18);BTN(4,13,220,71,279,0,69);TPN(2);");
					sprintf(putsorc,"PIC(160,60,%d);PS24(1,150,100,'ҩƷ %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				  
				    drug_t.count=3;
				  
				    inputstate=6;
				
			  
			  }	
			else if(n==9|USART1_Receive("[BN:9]"))
			  {
				  
					sortc=4;
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'�����ÿ�η��ø�ҩƷ�ļ���',0);PS24(1,10,140,'ÿ�η��õļ���Ϊ_____��',0);BTN(3,200,140,266,179,2,45);PIC(13,220,18);BTN(4,13,220,71,279,0,69);TPN(2);");
					sprintf(putsorc,"PIC(160,60,%d);PS24(1,150,100,'ҩƷ %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				    inputstate=6;
				  drug_t.count=4;
			  
			  }	

			  else if(n==5|USART1_Receive("[BN:5]"))
			  {
			
				printf("CLS(7);BPIC(1,0,0,11);PS24(1,130,10,'ѡ���ҩʱ��',0);PS24(1,40,60,'�밴��ɫ�������ʱ������',1);");
				sprintf(putsorc,"PS24(1,40,80,'ʱ��%d',1);SXY(160,120);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);SXY(0,0);",timestate,timeh0,timeh1,timem0,timem1);
				printf(putsorc);
				printf("PIC(13,220,18);BTN(16,13,220,71,279,0,64);PIC(315,220,23);BTN(18,314,220,375,280,0,69);\r\n");
				
				inputstate=3;
			  
			  }
		   
		   }
		   
		   else if(inputstate==6)
		   {
//			 getbn();
			   
		     if(n==3 | USART1_Receive("[BN:3]"))
			 {
				 inputstate=7;
				 
				printf("CLS(7);SPG(6);\r\n");//�������ҩ����� 
				 
				 if(sortc==1)
				 {
					  drug_t.count=1;
					 
				 }else if(sortc==2)
				 {
					 drug_t.count=2;
					 
				 }else if(sortc==3)
				 {
					 drug_t.count=3;
				 }else if(sortc==4)
				 {
					 drug_t.count=4;			 
				 
				 }
			 
			 
			 }
			 else if(n==4 | USART1_Receive("[BN:4]"))
			 {
				 inputstate=5;
				  printf("CLS(7);SPG(4);\r\n");

			 }
		   }
		   else if(inputstate==7)
			  {
//				  getbn();
	
				if(n==14|USART1_Receive("[BN:14]"))
				{
					 getnum=kbuf[0]-0x30;
					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'�����ÿ�η��ø�ҩƷ�ļ���',0);");
					sprintf(putsorcqst,"PIC(160,60,%d);PS24(1,150,100,'ҩƷ %d ',1);",drug_t.count,drug_t.count);
					printf(putsorcqst);
					sprintf(getdata,"PS24(1,40,140,'ÿ�η��õļ���Ϊ %d ��',0);",getnum);
					printf(getdata);
					printf("PIC(13,220,18);BTN(17,13,220,71,279,0,54);PIC(315,220,23);BTN(18,314,220,375,280,0,52);\r\n");
					
					
					
					if(timestate==1)
					{
						drug_t1.hour=drug_t.hour;
						drug_t1.min=drug_t.min;
						
						switch(drug_t.count)
						{
							case 1 : drug_t1.d_one=getnum;break;
							case 2 : drug_t1.d_two=getnum;break;
							case 3 : drug_t1.d_three=getnum;break;
							case 4 : drug_t1.d_four=getnum;break;
							default: break;
						
						}
						
						sprintf(whenone,"%d%d%d%d%d%d",drug_t1.hour,drug_t1.min,drug_t1.d_one,drug_t1.d_two,drug_t1.d_three,drug_t1.d_four);
					}
					else if(timestate==2)
					{
						drug_t2.hour=drug_t.hour;
						drug_t2.min=drug_t.min;
						switch(drug_t.count)
						{
							case 1 : drug_t2.d_one=getnum;break;
							case 2 : drug_t2.d_two=getnum;break;
							case 3 : drug_t2.d_three=getnum;break;
							case 4 : drug_t2.d_four=getnum;break;
							default: break;
						
						}
							sprintf(whentwo,"%d%d%d%d%d%d",drug_t2.hour,drug_t2.min,drug_t2.d_one,drug_t2.d_two,drug_t2.d_three,drug_t2.d_four);
					}else if(timestate==3)
					{
						drug_t3.hour=drug_t.hour;
						drug_t3.min=drug_t.min;
						switch(drug_t.count)
						{
							case 1 : drug_t3.d_one=getnum;break;
							case 2 : drug_t3.d_two=getnum;break;
							case 3 : drug_t3.d_three=getnum;break;
							case 4 : drug_t3.d_four=getnum;break;
							default: break;
						
						}
					sprintf(whenthree,"%d%d%d%d%d%d",drug_t3.hour,drug_t3.min,drug_t3.d_one,drug_t3.d_two,drug_t3.d_three,drug_t3.d_four);
					}

					inputstate=7;

				}	
				else if(n==16|USART1_Receive("[BN:16]"))
				{
				  inputstate=5;
				  printf("CLS(7);SPG(4);\r\n");
				
				}
				
				else if(n==18 |USART1_Receive("[BN:18]"))
				{
	
					printf("CLS(7);SPG(2);\r\n");
					
					sprintf(besaved,"PS16(1,20,100,'ʱ��1: %d:%d,ҩƷa:%d��,ҩƷb:%d��,ҩƷc:%d��,ҩƷd:%d�� ',0);",drug_t1.hour,drug_t1.min,drug_t1.d_one,drug_t1.d_two,drug_t1.d_three,drug_t1.d_four);
	
					 sprintf(besavedtwo,"PS16(1,20,130,'ʱ��2: %d:%d,ҩƷa:%d��,ҩƷb:%d��,ҩƷc:%d��,ҩƷd:%d�� ',0);",drug_t2.hour,drug_t2.min,drug_t2.d_one,drug_t2.d_two,drug_t2.d_three,drug_t2.d_four);
				
			
				     sprintf(besavedthree,"PS16(1,20,160,'ʱ��3: %d:%d,ҩƷa:%d��,ҩƷb:%d��,ҩƷc:%d��,ҩƷd:%d�� ',0);",drug_t3.hour,drug_t3.min,drug_t3.d_one,drug_t3.d_two,drug_t3.d_three,drug_t3.d_four);

				
				
					n=0;
					
					inputstate=1;
	


				}

				
				else if(n==17 |USART1_Receive("[BN:17]"))
				{
				  inputstate=5;
				  printf("CLS(7);SPG(4);\r\n");

				}
	  
			 }
			   else if(inputstate==8)
			   {
//				     getbn();

	  
				   
				if(n==1|USART1_Receive("[BN:1]"))
				   {
					   inputstate=9;
					  printf("CLS(7);SPG(12);\r\n");  

				   }
				  else if(n==2|USART1_Receive("[BN:2]"))
				   {
					   inputstate=10;
					  printf("CLS(7);SPG(13);\r\n");  
				   
				   }
				   
				   else if(n==5|USART1_Receive("[BN:5]"))
				   {
				      
					   printf("CLS(7);SPG(2);\r\n");
					   inputstate=1;
//					   

				   }
				   else if(n==11|USART1_Receive("[BN:11]"))
				   {
					   
					   printf("CLS(7);SPG(2);\r\n");
					   inputstate=1;

				   }
				   
			   }
			   else if(inputstate==9)
			   {
//				   getbn();

				   if(n==14|USART1_Receive("[BN:14]"))
				   {
					   getyear=(kbuf[0]-0x30)*1000+(kbuf[1]-0x30)*100+(kbuf[2]-0x30)*10+(kbuf[3]-0x30);
					   getmon=(kbuf[4]-0x30)*10+(kbuf[5]-0x30);
					   getday=(kbuf[6]-0x30)*10+(kbuf[7]-0x30);
					   
					   RTC_timechange(getyear,getmon,getday,gethour,getmin,getsec);
					   
						printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'����ʱ��Ϊ��',3);");
						sprintf(putsorc,"SXY(50,60);PS24(1,0,30,'����: %d��%d��%d�� ',0);BTN(1,248,20,396,60,0,39);SXY(0,0);PIC(300,80,22);",getyear,getmon,getday);
						printf(putsorc);
						sprintf(putsorcqss,"SXY(80,150);PS24(1,0,2,'ʱ��: %d:%d:%d',0);BTN(2,218,0,366,40,0,39);SXY(0,0);PIC(300,150,20);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",gethour,getmin,getsec);
						printf(putsorcqss);
						printf("\r\n");
						inputstate=8;
					   
					   
				   }
				 else if(n==16|USART1_Receive("[BN:16]"))
					{
						printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'����ʱ��Ϊ��',3);");
						sprintf(putsorc,"SXY(50,60);PS24(1,0,30,'����: %d��%d��%d�� ',0);BTN(1,248,20,396,60,0,39);SXY(0,0);PIC(300,80,22);",calendar.w_year,calendar.w_month,calendar.w_date);
						printf(putsorc);
						sprintf(putsorcqss,"SXY(80,150);PS24(1,0,2,'ʱ��: %d:%d:%d',0);BTN(2,218,0,366,40,0,39);SXY(0,0);PIC(300,150,20);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",calendar.hour,calendar.min,calendar.sec);
						printf(putsorcqss);
						printf("\r\n");
						inputstate=8;
					
					}
			   
			   
			   
			   }
			   else if(inputstate==10)
			   {
//				   getbn();
	
				    if(n==14|USART1_Receive("[BN:14]"))
					{
					   gethour=(kbuf[0]-0x30)*10+(kbuf[1]-0x30);
					   getmin=(kbuf[2]-0x30)*10+(kbuf[3]-0x30);
					   getsec=(kbuf[4]-0x30)*10+(kbuf[5]-0x30);
						
						RTC_timechange(getyear,getmon,getday,gethour,getmin,getsec);
						
						printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'����ʱ��Ϊ��',3);");
						sprintf(putsorc,"SXY(50,60);PS24(1,0,30,'����: %d��%d��%d�� ',0);BTN(1,248,20,396,60,0,39);SXY(0,0);PIC(300,80,22);",getyear,getmon,getday);
						printf(putsorc);
						sprintf(putsorcqss,"SXY(80,150);PS24(1,0,2,'ʱ��: %d:%d:%d',0);BTN(2,218,0,366,40,0,39);SXY(0,0);PIC(300,150,20);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",gethour,getmin,getsec);
						printf(putsorcqss);
						printf("\r\n");
					
						
						AlarmRank();//�����3�����ӱ������Ⱥ�˳������
						AlarmSelect();//��ϵͳʱ����3�����ӱȽϣ�׼����һ������    
						RTC_Alarm_Set(calendar.w_year,calendar.w_month,calendar.w_date,nnhour,nnmin,0);

						inputstate=8;
					
					
					}		
					else if(n==16|USART1_Receive("[BN:16]"))
					{
						printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'����ʱ��Ϊ��',3);");
						sprintf(putsorc,"SXY(50,60);PS24(1,0,30,'����: %d��%d��%d�� ',0);BTN(1,248,20,396,60,0,39);SXY(0,0);PIC(300,80,22);",calendar.w_year,calendar.w_month,calendar.w_date);
						printf(putsorc);
						sprintf(putsorcqss,"SXY(80,150);PS24(1,0,2,'ʱ��: %d:%d:%d',0);BTN(2,218,0,366,40,0,39);SXY(0,0);PIC(300,150,20);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",calendar.hour,calendar.min,calendar.sec);
						printf(putsorcqss);
						printf("\r\n");
						inputstate=8;
					}

			   }
			   else if(inputstate==11)
			   {
				   getbn();
				   
				 if(n==1 | USART1_Receive("[BN:1]"))
				 {

					  HC05_TimingOff( );
					 inputstate=1;
					 printf("CLS(7);SPG(2);\r\n");//�������˵� 
					 alarmstate=0;
					 voicebegin=0;
					 voicecount=0;
					 voice_sy("�Ѿ���ɱ��γ�ҩ��ף�����彡����������");
					 LED1=1;
					 LED2=1;
					 LED3=1;
					 LED4=1;
				 
				 }
				 else if(n==2 | USART1_Receive("[BN:2]"))
				 {
					 
					 HC05_TimingOff( );
					  inputstate=11;
					  alarmstate=0;
					  voicebegin=0;
					  voicecount=0;
					
					 

					 
					 if(qsmhour==drug_t1.hour && qsmmin ==drug_t1.min)
					 {
						 if(drug_t1.d_one!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��aҩ%d��",drug_t1.d_one);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED1=0;

						 }
						 if(drug_t1.d_two!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��bҩ%d��",drug_t1.d_two);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED2=0;

						 }
						 if(drug_t1.d_three!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��cҩ%d��",drug_t1.d_three);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED3=0;

						 }
						 if(drug_t1.d_four!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��dҩ%d��",drug_t1.d_four);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED4=0;

						 }
					 
					 }else if(qsmhour==drug_t2.hour && qsmmin ==drug_t2.min)
					 {
						 if(drug_t2.d_one!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��aҩ%d��",drug_t2.d_one);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED1=0;

						 }
						 if(drug_t2.d_two!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��bҩ%d��",drug_t2.d_two);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED2=0;

						 }
						 if(drug_t2.d_three!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��cҩ%d��",drug_t2.d_three);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED3=0;

						 }
						 if(drug_t2.d_four!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��dҩ%d��",drug_t2.d_four);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED4=0;

						 }
					 
					 }else if(qsmhour==drug_t3.hour && qsmmin ==drug_t3.min)
					 {
						 if(drug_t3.d_one!=0)
						 {
//							 char QS[40];
							 sprintf(QS,"��Ҫ��aҩ%d��",drug_t3.d_one);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED1=0;

						 }
						 if(drug_t3.d_two!=0)
						 {
							 sprintf(QS,"��Ҫ��bҩ%d��",drug_t3.d_two);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED2=0;

						 }
						 if(drug_t3.d_three!=0)
						 {

							 sprintf(QS,"��Ҫ��cҩ%d��",drug_t3.d_three);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED3=0;

						 }
						 if(drug_t3.d_four!=0)
						 {

							 sprintf(QS,"��Ҫ��dҩ%d��",drug_t3.d_four);
							 voice_sy(QS);
							 delay_ms(1000);
							 LED4=0;

						 }
					 
					 }
					 
					  inputstate=11;
 


				 }
 
			   }
			    else if(inputstate==12)
			  {
				  getbn();
	
				if(n==14|USART1_Receive("[BN:14]"))
				{
					u8 ip;
					for(ip=0;kbuf[ip]!=0;ip++)
					{
						phonenum[ip]=kbuf[ip];
					}

					printf("CLS(7);BPIC(1,0,0,11);PS24(1,40,20,'��ȷ�Ͻ������Ⱥ��룺',0);");
					sprintf(putsorcqst,"PS24(1,100,150,'call: %s ',1);",phonenum);
					printf(putsorcqst);

					printf("PIC(13,220,18);BTN(17,13,220,71,279,0,54);PIC(315,220,23);BTN(18,314,220,375,280,0,52);\r\n");
					inputstate=12;
				}
				else if(n==16|USART1_Receive("[BN:16]"))
				{
				  inputstate=1;
				  printf("CLS(7);SPG(2);\r\n");
				
				}
				else if(n==17|USART1_Receive("[BN:17]"))
				{
				  inputstate=12;
				  printf("CLS(7);SPG(14);\r\n");
				
				}
				else if(n==18|USART1_Receive("[BN:18]"))
				{
					printf("CLS(7);BPIC(1,0,0,11);");

					if(phonenum[0]==0)
					{
						printf(	"PS24(1,120,60,'Ŀǰδ�󶨺���',0);");
					}
					else
					{
						sprintf(putsorc,"SXY(20,60);PS24(1,0,10,'�Ѱ󶨺���: %s',0);SXY(0,0);",phonenum);
						printf(putsorc);
					}
					
					sprintf(putsorcqss,"PIC(170,140,21);SXY(120,140);BTN(1,50,0,200,40,0,39);SXY(0,0);PIC(13,220,18);BTN(5,13,220,71,279,0,48);",phonenum);
					printf(putsorcqss);
					printf("\r\n");
					inputstate=13;
				
				
				}
			}
			  else if(inputstate==13)
			  {
				 getbn();

				if(n==1|USART1_Receive("[BN:1]"))
				   {
					   inputstate=12;
					  printf("CLS(7);SPG(14);\r\n");  

				   }
				   else if(n==5|USART1_Receive("[BN:5]"))
				   {
				      
					   printf("CLS(7);SPG(2);\r\n");
					   inputstate=1;				   

				   }
				   else if(n==11|USART1_Receive("[BN:11]"))
				   {
					   
					   printf("CLS(7);SPG(2);\r\n");
					   inputstate=1;

				   }
				  
			  
			  
			  }
			   
			   


		}
		
		qsm=getnonzero(drug_t1)+getnonzero(drug_t2)+getnonzero(drug_t3);
		
		if(voicebegin==1)
		{
			voice_sy("    ��ʼ��ҩ��    ");
			delay_ms(1000);

		}else if(voicebegin==2)
		{
		  voicebegin=0;
		  printf("CLS(7);SPG(2);\r\n");
		   inputstate=1;
			voicecount=0;
			 HC05_TimingOff();

		}
		
		HC05_TimingSend("SHAKE\r\n");//��ʱ�����ַ���
		
	
	}

 
 
}
 

void AlarmRank(void)   //�����3�����ӱ������Ⱥ�˳������
 {
	   u8 i,j,k,temp1,temp2;
	 for(i=0;i<3;i++)
		 {
			AlmGetHour[i]=AlmHour[i];
			AlmGetMin[i]=AlmMin[i]; 
		 }
	for(i=0;i<3;i++)  //��ʱ���С��������
	   {
		 k=i;
		   for(j=i+1;j<3;j++)
		   {
			   if(AlmGetHour[k]>AlmGetHour[j])
				   k=j;
		   }
		   if(k!=i)
		   {
			temp1=AlmGetHour[i];
			AlmGetHour[i]=AlmGetHour[k];
			AlmGetHour[k]=temp1;	
			   
			temp2=AlmGetMin[i];
			AlmGetMin[i]=AlmGetMin[k];
			AlmGetMin[k]=temp2;      
			   }
	   }	
   
   
   
 }

 void AlarmSelect(void)   //��ϵͳʱ����3�����ӱȽϣ�׼����һ������
 {
		if(calendar.hour<AlmGetHour[0]||(calendar.hour==AlmGetHour[0]&&calendar.min<AlmGetMin[0]))
		{
			
			nnhour = AlmGetHour[0];
			nnmin = AlmGetMin[0];        //ϵͳʱ���ڵ�һ������ǰ����������1
			nnday =calendar.w_date;
		}
		else if(calendar.hour<AlmGetHour[1]||(calendar.hour==AlmGetHour[1]&&calendar.min<AlmGetMin[1]))
		{
				nnhour = AlmGetHour[1];
			    nnmin = AlmGetMin[1];        //ϵͳʱ���ڵ�2������ǰ����������2	
		        nnday =calendar.w_date;
		}
		else if(calendar.hour<AlmGetHour[2]||(calendar.hour==AlmGetHour[2]&&calendar.min<AlmGetMin[2]))
		{
				nnhour = AlmGetHour[2];
			    nnmin = AlmGetMin[2];        //ϵͳʱ���ڵ�3������ǰ����������3
			    nnday =calendar.w_date;
		}
		else
		{
			nnhour = AlmGetHour[0];
			nnmin = AlmGetMin[0];        //ϵͳʱ���ڵ�3�����Ӻ���������1
			nnday =calendar.w_date+1;
		} 

 }
 
 

 




