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
 * ���༭	��2016.9.30
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/
#ifndef __BEE_DEBUG__
#define __BEE_DEBUG__

/****************************����ͷ�ļ�*******************************************/


#include "usart.h"
#include "string.h"


#define FCU_DEBUG		//��������

/****************************�궨��*********************************************/

#ifdef FCU_DEBUG
static char debug_buf[128];		//��һ��static�������ڲ�ʹ��

#define Debug_log(format, args...) do{sprintf (debug_buf, format, ##args); USART1_Sendstr("DEBUG:\t");USART1_Sendstr(debug_buf);USART1_Sendstr("\r\n");}while(0);// 
#else
#define Debug_log(...) do{}while(0);
#endif

#endif

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

