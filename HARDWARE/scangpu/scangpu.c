#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "usartgpu.h"






void scangpu(void)
{
		 if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度

			for(t=0;t<len;t++)
			{
				getdata[t]=USART_RX_BUF[t];
			}

			USART_RX_STA=0;
			
			if(inputstate==0)
			{
				//此时处于初始化界面
				getbn();
				if(n==1 | USART1_Receive("[BN:1]"))
				{
					printf("CLS(0);SPG(2);\r\n");//跳转到菜单
					inputstate=1;
				
				}

		   }
			
		   if(inputstate==1)
		   {
			   //在菜单界面下
			   	getbn();
				if(n==3 | USART1_Receive("[BN:3]"))
				{
					printf("CLS(0);BPIC(1,0,0,11);PS32(1,130,10,'选择服药时间',0);PS16(1,5,50,'请按红色方框进行时间设置,若时间确定可直接按时间后的确认键',1);");//进入添加药物功能，先进入添加时间
					sprintf(putsorc,"PS24(1,50,80,'时间1:',0);SXY(160,80);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(1,0,0,118,30,1,39);PS24(1,155,0,'确认',1);BTN(11,155,0,200,25,1,46);SXY(0,0);",timeoh0,timeoh1,timeom0,timeom1);
					printf(putsorc);
					sprintf(putsorcqst,"PS24(1,50,140,'时间2:',0);SXY(160,140);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(2,0,0,118,30,1,39);PS24(1,155,0,'确认',1);BTN(12,155,0,200,25,1,47);SXY(0,0);",timeth0,timeth1,timetm0,timetm1);
				    printf(putsorcqst);
					sprintf(putsorcqss,"PS24(1,50,200,'时间3:',0);SXY(160,200);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);BTN(3,0,0,118,30,1,41);PS24(1,155,0,'确认',1);BTN(13,155,0,200,25,1,46);SXY(0,0);",timehh0,timehh1,timehm0,timehm1);//timethree[3]-'0'
					printf(putsorcqss);
					printf("TPN(2);SXY(0,0);PS24(1,15,241,'返回',1);BTN(4,13,240,71,269,1,42);\r\n");
					
					inputstate=2;
				}
				if(n==4 | USART1_Receive("[BN:4]"))
				{
					printf("CLS(0);BPIC(1,0,0,9);PS32(1,180,10,'查看药物',2);PS24(1,20,60,'已添加的药物有：',15);PS24(1,15,261,'返回',1);BTN(2,13,260,71,289,1,130);"); 
					if(qsm!=0)
					{
					//	sprintf(besavedo,"PS16(1,20,100,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeoh0,timeoh1,timeom0,timeom1,sortc,getnum);
						printf(besavedo);
						if(qsm==2)
						{
							 sprintf(besavedt,"PS16(1,20,140,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);
							 printf(besavedt);
						}			
						if(qsm==3)
						{
							 sprintf(besavedh,"PS16(1,20,140,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);
							 printf(besavedh);
						}
						
						
								
					}
					printf("\r\n");
					inputstate=1;
				
				}
				if(n==5|USART1_Receive("[BN:5]"))
				{
					printf("CLS(0);SPG(8);\r\n");
				
				}

		   }
		  if(inputstate==2)
		   {
			   //添加时间界面下
			   	getbn();
				if(n==1 |USART1_Receive("[BN:1]"))
				{
					timestate=1;
					printf("CLS(0);SPG(10);\r\n");
					inputstate=3;
				
				}
				if(n==2 |USART1_Receive("[BN:2]"))
				{
					timestate=2;
					printf("CLS(0);SPG(10);\r\n");
					inputstate=3;
				
				}
				if(n==3|USART1_Receive("[BN:3]"))
				{
					timestate=3;
					printf("CLS(0);SPG(10);\r\n");
					inputstate=3;
				
				}
				if(n==4 |USART1_Receive("[BN:4]"))
				{
					printf("CLS(0);SPG(2);\r\n");
					inputstate=1;
				
				}
				
				if(n==11 |USART1_Receive("[BN:11]"))
				{
					timestate=1;
					printf("CLS(0);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timeoh0;
					timeh1=timeoh1;
					timem0=timeom0;
					timem1=timeom1;	
				
				}				
				if(n==12 |USART1_Receive("[BN:12]"))
				{
					timestate=2;
					printf("CLS(0);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timeth0;
					timeh1=timeth1;
					timem0=timetm0;
					timem1=timetm1;	
				}
				if(n==13 |USART1_Receive("[BN:13]"))
				{
					timestate=3;
					printf("CLS(0);SPG(4);\r\n");
					inputstate=5;
					
					timeh0=timehh0;
					timeh1=timehh1;
					timem0=timehm0;
					timem1=timehm1;	
				}

		   }
		    if(inputstate==3)
			{
				getbn();
				if(n==16)
				{
				  printf("CLS(0);SPG(2);\r\n");//进入添加药物功能，先进入添加时间
				  inputstate=1;
				}
				
				if(n==18)
				{
				   inputstate=5;
				   printf("CLS(0);SPG(4);\r\n");//进入添加药物功能，先进入添加时间
				  
				}
//				if(n==18)
//				{
//					 inputstate=5;
//				}
				
				
				if(n==14)
					{
						timeh0=kbuf[0]-0x30;
						timeh1=kbuf[1]-0x30;
						timem0=kbuf[2]-0x30;
						timem1=kbuf[3]-0x30;

						


						printf("CLS(0);BPIC(1,0,0,11);PS32(1,130,10,'选择服药时间',0);PS24(1,40,60,'请按红色方框进行时间设置',1);");
						sprintf(putsorc,"PS24(1,40,80,'时间%d',1);SXY(160,120);ICON(2,0,13,11,1,%d);ICON(25,0,13,11,1,%d);ICON(50,0,13,11,1,10);ICON(75,0,13,11,1,%d);ICON(100,0,13,11,1,%d);SXY(0,0);",timestate,timeh0,timeh1,timem0,timem1);
						printf(putsorc);
						printf("PS24(1,15,241,'返回',1);BTN(16,13,240,71,269,1,64);PS24(1,305,241,'确认',1);BTN(18,303,240,361,269,1,69);\r\n");
						
						 inputstate=3;
						if(timestate==1)
						{
							timeoh0=timeh0;
							timeoh1=timeh1;
							timeom0=timem0;
							timeom1=timem1;						
						
						}
						
						if(timestate==2)
						{
							timeth0=timeh0;
							timeth1=timeh1;
							timetm0=timem0;
							timetm1=timem1;						
						
						}
						if(timestate==3)
						{
							timehh0=timeh0;
							timehh1=timeh1;
							timehm0=timem0;
							timehm1=timem1;						
						
						}
						
						
					}	

		}

		   if(inputstate==5)
		   {
//			  	getbn( );
			  // USART1_Receive("[BN:6]")
			 u8 gsix;
			 gsix=getbn();
			   
			   

			  if(gsix==6| USART1_Receive("[BN:6]"))
			  {
					sortc=1;
					printf("CLS(0);DS24(40,20,'请添加每次服用该药品的剂量',15);DS32(10,140,'每次服用的剂量为_____粒',15);BTN(3,265,140,320,179,2,45);PS24(1,15,241,'返回',1);BTN(4,13,240,71,269,1,69);");
					sprintf(putsorc,"PIC(160,60,%d);DS24(150,100,'药品 %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				   inputstate=6;
				
			  
			  }		
			if(gsix==7| USART1_Receive("[BN:7]"))
			  {
					sortc=2;
					printf("CLS(0);DS24(40,20,'请添加每次服用该药品的剂量',15);DS32(10,140,'每次服用的剂量为_____粒',15);BTN(3,265,140,320,179,2,45);PS24(1,15,241,'返回',1);BTN(4,13,240,71,269,1,69);");
					sprintf(putsorc,"PIC(160,60,%d);DS24(150,100,'药品 %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				   inputstate=6;
				   
			  
			  }	
			if(gsix==8| USART1_Receive("[BN:8]"))
			  {
					sortc=3;
					printf("CLS(0);DS24(40,20,'请添加每次服用该药品的剂量',15);DS32(10,140,'每次服用的剂量为_____粒',15);BTN(3,265,140,320,179,2,45);PS24(1,15,241,'返回',1);BTN(4,13,240,71,269,1,69);");
					sprintf(putsorc,"PIC(160,60,%d);DS24(150,100,'药品 %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				    inputstate=6;
				
			  
			  }	
			if( gsix==9|USART1_Receive("[BN:9]"))
			  {
					sortc=4;
					printf("CLS(0);DS24(40,20,'请添加每次服用该药品的剂量',15);DS32(10,140,'每次服用的剂量为_____粒',15);BTN(3,265,140,320,179,2,45);PS24(1,15,241,'返回',1);BTN(4,13,240,71,269,1,69);");
					sprintf(putsorc,"PIC(160,60,%d);DS24(150,100,'药品 %c ',1);\r\n",sortc,sortc+'0');
					printf(putsorc);
				    inputstate=6;
				  
			  
			  }	
			  
			  if(gsix>=6&&gsix<=9)
			  {
				 inputstate=6;

			  }
			  
			  if(gsix==5|USART1_Receive("[BN:5]"))
			  {
				inputstate=4;
				printf("CLS(0);SPG(4);\r\n");//进入添加药物功能，先进入添加时间 
			  
			  
			  }
		   
		   }
		   
		   if(inputstate==6)
		   {
			   u8 gsix;
			 gsix=getbn();
		     if(gsix==3|USART1_Receive("[BN:3]"))
			 {
				 inputstate=7;
				printf("CLS(0);SPG(6);\r\n");//进入添加药物功能，先进入添加时间 
			 
			 }
			 if(gsix==4)
			 {
				 inputstate=5;
				  printf("CLS(0);SPG(4);\r\n");

			 
			 }
		   }
		      if(inputstate==7)
			  {
					if(iscmdok==1)
					{	if ((cmd[0]=='B') & (cmd[1]=='N'))
						{	n=cmd[3]-0x30;
							if ((cmd[4]>=0x30) & (cmd[4]<=0x39))
							{	n=n*10+cmd[4]-0x30;
							}
						//此时n为键码,在此写对应的按键处理程序

						}
						iscmdok=0;
						
					}
					
				if(n==14)
				{
					 getnum=kbuf[0]-0x30;
//					inputstate=0;
					printf("CLS(0);DS24(40,20,'请添加每次服用该药品的剂量',15);");
					sprintf(putsorc,"PIC(160,60,%d);DS24(150,100,'药品 %c ',1);",sortc,sortc+'0');
					printf(putsorc);
					sprintf(getdata,"DS32(40,140,'每次服用的剂量为 %d 粒',15);PS24(1,15,241,'返回',1);BTN(17,13,240,71,269,1,54);",getnum);
					printf(getdata);
					printf("PS24(1,305,241,'确认',1);BTN(18,303,240,361,269,1,52);\r\n");
					inputstate=7;

				}	
				
				if(n==18)
				{
	
					printf("CLS(0);SPG(2);\r\n");
				     if(qsm>2)
					{
						qsm=0;
					}
					qsm++;
					
					if(qsm==1)
					{
						sprintf(besavedo,"PS16(1,20,100,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);
					}
					if(qsm==2)
					{
					     sprintf(besavedt,"PS16(1,20,140,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);
					}
					if(qsm==3)
					{
				    	 sprintf(besavedh,"PS16(1,20,180,'时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d 粒 ',15);",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);

					}

				
					n=0;
					inputstate=1;


				}
				if(n==18)
				{
				 inputstate=1;
				
				}
				
				if(n==17)
				{
				  inputstate=5;
				  printf("CLS(0);SPG(4);\r\n");

				}
	  
			 }
			   if(inputstate==8)
			   {
			   
			   
			   
			   
			   
			   
			   }

		  	
			
		 //to voice module
//sprintf(besavedget,"时间%d :%d %d : %d %d ,药品 %d ,服用剂量 %d ",timestate,timeh0,timeh1,timem0,timem1,sortc,getnum);


		}





}