/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��exti.cpp
 * ��	��	���ж�
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.10.03
 * ���༭	��2016.10.04
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "exti.h"
#include "Sensor.h"

#if SYSTEM_SUPPORT_UCOS
#include "os.h"					//ucos ʹ��	  
#endif
/****************************��������*********************************************/
extern OS_SEM g_sem_sensor_rdy;
/****************************��������*********************************************/
//void (*EXTI1_UserHandle_Ptr)(void)=NULL;
/****************************�������*********************************************/

/****************************��������*********************************************/

//void EXTI1_UserHook(void)
//{
//	if(EXTI1_UserHandle_Ptr!=NULL)
//	{
//		(*EXTI1_UserHandle_Ptr)();				//
//	}
//}

//�ⲿ�ж�1�������
void EXTI1_IRQHandler(void)
{	 
//	OS_ERR err;	
	
	OSIntEnter();    
    sensor.Update();
//	if(sensor.Update())
//	{
//		OSSemPost ((OS_SEM  *)&g_sem_sensor_rdy,
//				   (OS_OPT   )OS_OPT_POST_ALL,
//				   (OS_ERR  *)&err);
//	}
	EXTI_ClearITPendingBit(EXTI_Line1);//���LINE1�ϵ��жϱ�־λ 
	
	OSIntExit();  	
}
	   
//�ⲿ�жϳ�ʼ������
//��ʼ��PB1Ϊ�ж�����.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
	
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);//PB1 ���ӵ��ж���1
	
	/* ����EXTI_Line1 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//�ж��¼�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//�ж���ʹ��
	EXTI_Init(&EXTI_InitStructure);							//����

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//�ⲿ�ж�1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure);//����

}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










