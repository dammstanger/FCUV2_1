
//////////////////////////////////////////////////////////////////////////////////	 
//FCU_FPGA_V1 ·É¿Ø°å
//
//dammstanger@qq.com
//20160901
//All rights reserved										  
////////////////////////////////////////////////////////////////////////////////// 	
 

#ifndef __SWITCH_H
#define __SWITCH_H

#ifdef __cplusplus
 extern "C" {
#endif
	 
#include "sys.h"

#define SW1  PEout(2)	
#define SW2  PEout(3)	
	 
void Switch_GPIO_Init(void);//³õÊ¼»¯	

#ifdef __cplusplus
}
#endif

#endif
