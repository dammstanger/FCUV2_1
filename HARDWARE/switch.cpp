/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��switch.cpp
 * ��	��	��������
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.10.20
 * ���༭	��2016.10.20
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "switch.h"

//#if SYSTEM_SUPPORT_UCOS
//#include "os.h"					//ucos ʹ��	  
//#endif
/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�������*********************************************/

/****************************��������*********************************************/


void Switch_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��

	//GPIOF2 3��ʼ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//100MHz
	//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3); 

}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/





