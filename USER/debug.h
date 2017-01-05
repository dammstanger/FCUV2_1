/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��debug.cpp
 * ��	��	������
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.9.30
 * ���༭	��2016.11.26
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/
#ifndef __BEE_DEBUG__
#define __BEE_DEBUG__

/****************************����ͷ�ļ�*******************************************/


#include "usart.h"
#include "string.h"
#include "stdio.h"
#include <stdarg.h>


#ifdef __cplusplus
 extern "C" {
#endif
	 
#define PRF_ASCII		1u
#define PRF_DATA		2u

#define FCU_DEBUG		PRF_ASCII//��������

/****************************�궨��*********************************************/
//���Է�ʽ1����ӡASCII���ַ��� 
#if FCU_DEBUG==PRF_ASCII
//static char debug_buf[128];		//��һ��static�������ڲ�ʹ��

//#define Debug_log(format, args...) do{sprintf (debug_buf, format, ##args); USART1_Sendstr("DEBUG:\t");USART1_Sendstr(debug_buf);USART1_Sendstr("\r\n");}while(0);// 
#define Debug_log(format, args...) do{USART1_Sendstr("DEBUG:\t");printf(format, ##args);USART1_Sendstr("\r\n");}while(0)
#define Debug_dat(...) do{}while(0)

//���Է�ʽ2����ASCII������	
#elif FCU_DEBUG==PRF_DATA
extern void Dbg_printf_dat(const int num,...);
#define Debug_dat(num,args...) do{Dbg_printf_dat(num,##args);}while(0)		//��ӡ��ASCII���ݵĺ�
#define Debug_log(...) do{}while(0)
	
#else
#define Debug_log(...) do{}while(0)
#define Debug_dat(...) do{}while(0)

#endif

	
#ifdef __cplusplus
}
#endif
	
#endif

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

