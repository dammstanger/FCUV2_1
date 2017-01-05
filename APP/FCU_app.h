/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��FCU_app.h
 * ��	��	��Ӧ��
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.9.25
 * ���༭	��2016.9.25
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

#ifndef __FCU_APP_H_
#define __FCU_APP_H_

/****************************����ͷ�ļ�*******************************************/
#include <stm32f4xx.h>
#include "includes.h"
/****************************�궨��***********************************************/

/****************************��������*********************************************/
static  OS_TCB	LED_TCB;		   //����������ƿ�
static  OS_TCB	START_TCB;		   
static  OS_TCB	SENSOR_PRO_TCB;
static  OS_TCB	DATALOG_TCB;

static	CPU_STK	LED_Stk[TASK_LED_STK_SIZE];	   //���������ջ		�����8��λ��
static	CPU_STK	SENSOR_PRO_Stk[TASK_SENSOR_PRO_STK_SIZE];
static	CPU_STK	START_Stk[TASK_START_STK_SIZE];
static  CPU_STK Datalog_Stk[TASK_DATALOG_STK_SIZE];



/****************************����������*********************************************/
void Task_Start(void *p_arg);
void Task_SENSOR_PRO(void *p_arg);
void Task_LED(void *p_arg);
void Task_Datalog(void *p_arg);


#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

