/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/main.c 
  * @author  dammstanger
  * @version V1.4.0
  * @date    06-Setp-2016
  * @brief   Main program body
  *******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "driver_init.h"
#include "includes.h"
#include "FCU_app.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	OS_ERR err;	
	CPU_SR_ALLOC();			//����жϵı���
	
	delay_init(168);  		//��ʼ����ʱ����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	
	Driver_Init();
    
	
	INTX_DISABLE();		//���ж�,��ֹ�δ�ʱ���������ʼ���Ĵ���
	LED_Init();         //LED��ʼ��
	INTX_ENABLE();		//���ж�

	
	 /* ��ʼ��"uC/OS-III"�ں� */  
	OSInit(&err);
	OS_CRITICAL_ENTER();//�����ٽ���
	/*��������*/
	OSTaskCreate((OS_TCB     *)&START_TCB,                    	// ������ƿ�ָ��          
               (CPU_CHAR   *)"START",		                    // ��������
               (OS_TASK_PTR )Task_Start, 	                  	// �������ָ��
               (void       *)0,			                      	// ���ݸ�����Ĳ���parg
               (OS_PRIO     )TASK_START_PRIO,			     	// �������ȼ�
               (CPU_STK    *)&START_Stk[0],	                	// �����ջ����ַ
               (CPU_STK_SIZE)TASK_START_STK_SIZE_LIMIT,			// ��ջʣ�ྯ����
               (CPU_STK_SIZE)TASK_START_STK_SIZE,			    // ��ջ��С
               (OS_MSG_QTY  )0,			                      	// �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      	// ʱ��Ƭ��תʱ��
               (void       *)0,			                      	// ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// ����ѡ��
               (OS_ERR     *)&err);		                    	// ����ֵ
	  
	OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	/* ����������ϵͳ������Ȩ����uC/OS-III */
	OSStart(&err);     
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
