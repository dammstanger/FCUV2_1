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
	CPU_SR_ALLOC();			//存放中断的变量
	
	delay_init(168);  		//初始化延时函数
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	
	Driver_Init();
    
	
	INTX_DISABLE();		//关中断,防止滴答定时器对外设初始化的打扰
	LED_Init();         //LED初始化
	INTX_ENABLE();		//开中断

	
	 /* 初始化"uC/OS-III"内核 */  
	OSInit(&err);
	OS_CRITICAL_ENTER();//进入临界区
	/*创建任务*/
	OSTaskCreate((OS_TCB     *)&START_TCB,                    	// 任务控制块指针          
               (CPU_CHAR   *)"START",		                    // 任务名称
               (OS_TASK_PTR )Task_Start, 	                  	// 任务代码指针
               (void       *)0,			                      	// 传递给任务的参数parg
               (OS_PRIO     )TASK_START_PRIO,			     	// 任务优先级
               (CPU_STK    *)&START_Stk[0],	                	// 任务堆栈基地址
               (CPU_STK_SIZE)TASK_START_STK_SIZE_LIMIT,			// 堆栈剩余警戒线
               (CPU_STK_SIZE)TASK_START_STK_SIZE,			    // 堆栈大小
               (OS_MSG_QTY  )0,			                      	// 可接收的最大消息队列数
               (OS_TICK     )0,			                      	// 时间片轮转时间
               (void       *)0,			                      	// 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// 任务选项
               (OS_ERR     *)&err);		                    	// 返回值
	  
	OS_CRITICAL_EXIT();	//退出临界区	 
	/* 启动多任务系统，控制权交给uC/OS-III */
	OSStart(&err);     
}



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
