#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
extern   u8 flagsendon;
extern   u8 flageat;
extern 	u8 flagkeyoff;//ǿ�ƹط��ͱ�־λ
//�����������ڿ��ƴӻ���״̬

extern u8 voicecount;
extern u8 voicebegin;


void TIM3_Int_Init(u16 arr,u16 psc); 
 
#endif
