#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

 

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define WKUP_PRES   3	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
