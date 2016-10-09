/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：debug.cpp
 * 描	述	：调试
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.9.30
 * 最后编辑	：2016.9.30
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/
#ifndef __BEE_DEBUG__
#define __BEE_DEBUG__

/****************************包含头文件*******************************************/


#include "usart.h"
#include "string.h"


#define FCU_DEBUG		//开启调试

/****************************宏定义*********************************************/

#ifdef FCU_DEBUG
static char debug_buf[128];		//加一个static即可在内部使用

#define Debug_log(format, args...) do{sprintf (debug_buf, format, ##args); USART1_Sendstr("DEBUG:\t");USART1_Sendstr(debug_buf);USART1_Sendstr("\r\n");}while(0);// 
#else
#define Debug_log(...) do{}while(0);
#endif

#endif

/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

