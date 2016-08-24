#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "drugchoose.h"

 _drugget_obj drug_t1;	//日历结构体
 _drugget_obj drug_t2;	//日历结构体
 _drugget_obj drug_t3;	//日历结构体
 
 _drugget_obj drug_t;	
 
 void Drug_init(_drugget_obj qs)
 {
	 qs.count=0;
	
	 qs.d_one=0;
	 qs.d_two=0;
	 qs.d_three=0;
	 qs.d_four=0;
 
 }
 
 void cleardrug(void)
 {
	 Drug_init(drug_t);//替代药品
	 
	 Drug_init(drug_t1);
	 Drug_init(drug_t2);
	 Drug_init(drug_t3);
 
 
 }
 
 u8 getnonzero(_drugget_obj qm)
 {
	 u8 aqm,aqs;
	 aqs=0;
	 
	 if((qm.d_one|qm.d_two|qm.d_three|qm.d_four)==0)
	 {
		 aqm=0;
	 
	 }
	 else
	 {
		 if(qm.d_one!=0)
			 aqs++;
		 if(qm.d_two!=0)
			 aqs++;
		 if(qm.d_three!=0)
			 aqs++;
		 if(qm.d_four!=0)
			 aqs++;
		 
		 aqm=aqs;
	 

	 }
	return aqm;
 
 }
 
 
 
 