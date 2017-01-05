/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：exti.cpp
 * 描	述	：中断
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.10.03
 * 最后编辑	：2016.10.04
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

/****************************包含头文件*******************************************/
#include "exti.h"
#include "Sensor.h"
#include "switch.h"

#if SYSTEM_SUPPORT_UCOS
#include "os.h"					//ucos 使用	  
#endif
/****************************变量声明*********************************************/
extern OS_SEM g_sem_sensor_rdy;
/****************************变量定义*********************************************/

/****************************类对象定义*********************************************/

/****************************函数声明*********************************************/

//外部中断1服务程序
void EXTI1_IRQHandler(void)
{	 
	OS_ERR err;	
	u8 sta_1period ;
	
	OSIntEnter();    
	
	
    sta_1period = sensor.Update();
	if(sta_1period&IMU_RDY)					   //以IMU数据周期为最小单位，IMU更新期间如有其它数据更新则先读取，不发送处理消息
	{
		OSSemPost ((OS_SEM  *)&g_sem_sensor_rdy,
				   (OS_OPT   )OS_OPT_POST_ALL,
				   (OS_ERR  *)&err);
	}
	EXTI_ClearITPendingBit(EXTI_Line1);//清除LINE1上的中断标志位 
	
	OSIntExit();  	
}

////外部中断2服务程序
//void EXTI2_IRQHandler(void)
//{	 

//	OSIntEnter();    
//	
//	
//	
//	EXTI_ClearITPendingBit(EXTI_Line2);//清除LINE2上的中断标志位 
//	
//	OSIntExit();  	
//}
	   
//外部中断初始化程序
//初始化PB1，PE2 PE3为中断输入.
void EXTIX_Init(void)
{
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//使能SYSCFG时钟
	
	/* 配置EXTI_Line1 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource1);//PB1 连接到中断线1
		
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		//中断事件
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				//中断线使能
	EXTI_Init(&EXTI_InitStructure);							//配置

	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;//外部中断1
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
	NVIC_Init(&NVIC_InitStructure);//配置

//	/* 配置EXTI_Line2 */
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);//PE2 连接到中断线2
//		
//	EXTI_InitStructure.EXTI_Line = EXTI_Line2;
//	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;				//中断事件
//	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; 	//上下降沿触发
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;						//中断线使能
//	EXTI_Init(&EXTI_InitStructure);									//配置

//	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;//外部中断2
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x03;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;//子优先级1
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;//使能外部中断通道
//	NVIC_Init(&NVIC_InitStructure);//配置

}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










