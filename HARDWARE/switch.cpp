/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：switch.cpp
 * 描	述	：蜂鸣器
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.10.20
 * 最后编辑	：2016.10.20
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

/****************************包含头文件*******************************************/
#include "switch.h"

//#if SYSTEM_SUPPORT_UCOS
//#include "os.h"					//ucos 使用	  
//#endif
/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类对象定义*********************************************/

/****************************函数声明*********************************************/


void Switch_GPIO_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOE时钟

	//GPIOF2 3初始化设置
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_25MHz;//25MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化
	
	GPIO_ResetBits(GPIOE,GPIO_Pin_2|GPIO_Pin_3); 

}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/





