#ifndef __DELAY_H
#define __DELAY_H 	
#ifdef __cplusplus
 extern "C" {
#endif 
#include <sys.h>	  
//////////////////////////////////////////////////////////////////////////////////  
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32F407������
//ʹ��SysTick����ͨ����ģʽ���ӳٽ��й���(֧��ucosii��ucosiii)
//����delay_us,delay_ms
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/5/2
//�汾��V1.1
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2014-2024
//All rights reserved
//********************************************************************************
//�޸�˵��
//V1.1�޸�˵��
//�����˶�UCOSIII��֧��
////////////////////////////////////////////////////////////////////////////////// 	 
void delay_init(u8 SYSCLK);
void delay_ms(u16 nms);
void delay_us(u32 nus);

#ifdef __cplusplus
}
#endif 
#endif




























