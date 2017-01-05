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
 * 最后编辑	：2016.11.26
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/
#ifndef __BEE_DEBUG__
#define __BEE_DEBUG__

/****************************包含头文件*******************************************/


#include "usart.h"
#include "string.h"
#include "stdio.h"
#include <stdarg.h>


#ifdef __cplusplus
 extern "C" {
#endif
	 
#define PRF_ASCII		1u
#define PRF_DATA		2u

#define FCU_DEBUG		PRF_ASCII//开启调试

/****************************宏定义*********************************************/
//调试方式1：打印ASCII码字符串 
#if FCU_DEBUG==PRF_ASCII
//static char debug_buf[128];		//加一个static即可在内部使用

//#define Debug_log(format, args...) do{sprintf (debug_buf, format, ##args); USART1_Sendstr("DEBUG:\t");USART1_Sendstr(debug_buf);USART1_Sendstr("\r\n");}while(0);// 
#define Debug_log(format, args...) do{USART1_Sendstr("DEBUG:\t");printf(format, ##args);USART1_Sendstr("\r\n");}while(0)
#define Debug_dat(...) do{}while(0)

//调试方式2：非ASCII码数据	
#elif FCU_DEBUG==PRF_DATA
extern void Dbg_printf_dat(const int num,...);
#define Debug_dat(num,args...) do{Dbg_printf_dat(num,##args);}while(0)		//打印非ASCII数据的宏
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

