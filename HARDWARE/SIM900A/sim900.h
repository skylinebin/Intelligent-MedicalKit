#ifndef __SIM900_H__
#define __SIM900_H__	 
#include "sys.h"
	
  
#define swap16(x) (x&0XFF)<<8|(x&0XFF00)>>8		//�ߵ��ֽڽ����궨��
void sim900a_init(void);
void sim900a_test(void);//sim900a�����Գ��� 
void sim_send_sms(u8*phonenumber,u8*msg);

u8* sim900a_check_cmd(u8 *str);
u8 sim900a_send_cmd(u8 *cmd,u8 *ack,u16 waittime);
u8 sim900a_chr2hex(u8 chr);
u8 sim900a_hex2chr(u8 hex);
void sim900a_unigbk_exchange(u8 *src,u8 *dst);
void sim900a_load_keyboard(u16 x,u16 y,u8 **kbtbl);
void sim900a_key_staset(u16 x,u16 y,u8 keyx,u8 sta);
u8 sim900a_get_keynum(u16 x,u16 y);
u8 sim900a_call_test(void);			//���Ų���
void sim900a_sms_read_test(void);	//�����Ų���
void sim900a_sms_send_test(u8 phonenum[]);	//�����Ų��� 
void sim900a_sms_ui(u16 x,u16 y);	//���Ų���UI���溯��
u8 sim900a_sms_test(void);			//���Ų���
void sim900a_mtest_ui(u16 x,u16 y);	//SIM900A������UI
u8 sim900a_gsminfo_show(u16 x,u16 y);//��ʾGSMģ����Ϣ
void sim900a_test(void);			//SIM900A�����Ժ���

u8 sim900a_send_text(u8 phonenum[]);

#endif
