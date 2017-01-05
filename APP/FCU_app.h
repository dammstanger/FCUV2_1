/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：FCU_app.h
 * 描	述	：应用
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.9.25
 * 最后编辑	：2016.9.25
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __FCU_APP_H_
#define __FCU_APP_H_

/****************************包含头文件*******************************************/
#include <stm32f4xx.h>
#include "includes.h"
/****************************宏定义***********************************************/

/****************************变量定义*********************************************/
static  OS_TCB	LED_TCB;		   //定义任务控制块
static  OS_TCB	START_TCB;		   
static  OS_TCB	SENSOR_PRO_TCB;
static  OS_TCB	DATALOG_TCB;

static	CPU_STK	LED_Stk[TASK_LED_STK_SIZE];	   //定义任务堆栈		最好以8的位数
static	CPU_STK	SENSOR_PRO_Stk[TASK_SENSOR_PRO_STK_SIZE];
static	CPU_STK	START_Stk[TASK_START_STK_SIZE];
static  CPU_STK Datalog_Stk[TASK_DATALOG_STK_SIZE];



/****************************任务函数定义*********************************************/
void Task_Start(void *p_arg);
void Task_SENSOR_PRO(void *p_arg);
void Task_LED(void *p_arg);
void Task_Datalog(void *p_arg);


#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

