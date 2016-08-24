#ifndef _DRUGCHOOSE_H
#define _DRUGCHOOSE_H


typedef struct 
{
	vu8 hour;
	vu8 min;
	vu8 sec;			
	//ʱ����
	vu8 d_one;
	vu8  d_two;
	vu8  d_three;
	vu8 d_four;
	vu8  count;		 
}_drugget_obj;					 
extern _drugget_obj drug_t1;	//ʱ��ҩƷ�ṹ��
extern _drugget_obj drug_t2;	//ʱ��ҩƷ�ṹ��
extern _drugget_obj drug_t3;	//ʱ��ҩƷ�ṹ��

extern _drugget_obj drug_t;	//ʱ��ҩƷ�ṹ��

 void Drug_init(_drugget_obj qs);
 void cleardrug(void);
 u8 getnonzero(_drugget_obj qm);

#endif
