#ifndef __LED_H
#define __LED_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sys.h"

//////////////////////////////////////////////////////////////////////////////////	 
//FCU_FPGA_V1 �ɿذ�
//
//dammstanger@qq.com
//20160901
//All rights reserved										  
////////////////////////////////////////////////////////////////////////////////// 	
 

//LED�˿ڶ���
#define LED1 PBout(15)	// DS1
#define LED2 PBout(14)	// DS2	 
#define LED3 PBout(13)	// DS3
#define LED4 PBout(12)	// DS4	 
#define LED5 PBout(11)	// DS5

void LED_Init(void);//��ʼ��	

#ifdef __cplusplus
}
#endif

#endif
