/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：FCU_app.cpp
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

/****************************包含头文件*******************************************/
#include "includes.h"
#include "FCU_app.h"
#include "usart.h"
#include "FSMC.h"
#include "led.h"
#include "cpp_Math.h"
#include "Sensor.h"
/****************************变量定义*********************************************/
OS_SEM g_sem_sensor_rdy;



//  函数名：Task_Start
//	功  能：启动任务，启动系统的各个模块。
void Task_Start(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();			//存放中断的变量
	p_arg = p_arg;
	
	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	

	//创建信号量
	OSSemCreate(&g_sem_sensor_rdy,(CPU_CHAR*)"SENS_RDY",0,&err);
	//进入临界区
	OS_CRITICAL_ENTER();	
	//创建LED任务
	OSTaskCreate((OS_TCB     *)&LED_TCB,                    	// 任务控制块指针          
               (CPU_CHAR   *)"LED",		                    	// 任务名称
               (OS_TASK_PTR )Task_LED, 	                  		// 任务代码指针
               (void       *)0,			                      	// 传递给任务的参数parg
               (OS_PRIO     )TASK_LED_PRIO,			     		// 任务优先级
               (CPU_STK    *)&LED_Stk[0],	                	// 任务堆栈基地址
               (CPU_STK_SIZE)TASK_LED_STK_SIZE_LIMIT,			// 堆栈剩余警戒线
               (CPU_STK_SIZE)TASK_LED_STK_SIZE,			    	// 堆栈大小
               (OS_MSG_QTY  )0,			                      	// 可接收的最大消息队列数
               (OS_TICK     )0,			                      	// 时间片轮转时间
               (void       *)0,			                      	// 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// 任务选项
               (OS_ERR     *)&err);		                    	// 返回值
//	//创建Sensor_Process任务
	OSTaskCreate((OS_TCB     *)&SENSOR_PRO_TCB,                 // 任务控制块指针          
               (CPU_CHAR   *)"SENSOR_PRO",		                // 任务名称
               (OS_TASK_PTR )Task_SENSOR_PRO, 	                // 任务代码指针
               (void       *)0,			                      	// 传递给任务的参数parg
               (OS_PRIO     )TASK_SENSOR_PRO_PRIO,			    // 任务优先级
               (CPU_STK    *)&SENSOR_PRO_Stk[0],	            // 任务堆栈基地址
               (CPU_STK_SIZE)TASK_SENSOR_PRO_STK_SIZE_LIMIT,	// 堆栈剩余警戒线
               (CPU_STK_SIZE)TASK_SENSOR_PRO_STK_SIZE,			// 堆栈大小
               (OS_MSG_QTY  )0,			                      	// 可接收的最大消息队列数
               (OS_TICK     )0,			                      	// 时间片轮转时间
               (void       *)0,			                      	// 任务控制块扩展信息
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// 任务选项
               (OS_ERR     *)&err);		                    	// 返回值
	//退出临界区
	OS_CRITICAL_EXIT();	
	//任务删除自己	
	OSTaskDel(&START_TCB,&err);							 
}



/*  函数名：Task_LED
	功  能：LED控制
*/
void Task_LED(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
//		for(ts=0;ts<10;ts++)
//		{				
////			tmp = fsmc.Read32b(ts);
////			USART1_Sendbyte(tmp>>8);
////			USART1_Sendbyte(tmp);         					//向串口1发送数据
//		}		
	static u16 pwm=0;
	float dat[]={1.0f,1.0f,1.0f};

	math::Vector3 t(dat);
	
	while(1)
	{
		t.normalize();
//		sensor.MPU_AccTempGyro_Read();
//		sensor.MPU_Mag_Read();
//		sensor.MS5611_Press_Read();
//		sensor.Update();
		OPTFLW opt = sensor.Get_Optflw_Raw();
		float imu_tmp = sensor.Get_IMUTemp();
		float press = sensor.Get_AbsAlt();
		u16 alt = (u16)sensor.Get_RelaAlt_mm();
		if(pwm==1000)
			pwm = 0;
		else pwm++;
		fsmc.Write16b(REG_PWM1,1000+pwm);
		fsmc.Write16b(3,1000+pwm);
		fsmc.Write16b(4,1000+pwm);
		fsmc.Write16b(5,1000+pwm);
		fsmc.Write16b(6,1000+pwm);
		fsmc.Write16b(7,1000+pwm);
		fsmc.Write16b(8,1000+pwm);
		fsmc.Write16b(9,1000+pwm);	
		OS_CRITICAL_ENTER();									//进入临界区
		Debug_log("opt:%d,%d,%x,%x.\r\n",opt.dx,opt.dy,opt.motion,opt.quality);
		Debug_log("alt:%d mm.\r\n",alt);
		Debug_log("imu_tmp: %.4f\r\n",imu_tmp);
		
		Debug_log("press: %f\r\n",press);
		OS_CRITICAL_EXIT();										//退出临界区
		LED2=0;
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); 	//延时200ms
		LED2=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); 	//延时500ms
	}
}

/*  函数名：Task_SENSOR_PRO
	功  能：传感器数据处理
*/
void Task_SENSOR_PRO(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	CPU_TS TsOfPost;

	static float float_num=0.01;
	static u8 cnt = 0;
	float dat1[][3]={1.0f,1.0f,1.0f,
					 2.0f,2.0f,2.0f,
					 3.0f,3.0f,3.0f};
	float dat2[][3]={1.0f,1.0f,1.0f,
					 1.0f,1.0f,1.0f,
					 1.5f,1.5f,1.5f};
	float dat3[4]={1.0f,1.0f,1.0f,1.0f};
	math::Matrix3 m1(dat1),m2(dat2);
	math::Quaternion q1(dat3);
	
	while(1)
	{
		m1+=m2;
		q1.normalize();
		float_num+=0.01f;
		//阻塞任务直到按键被按下！
		OSSemPend ((OS_SEM   *)&g_sem_sensor_rdy,
             (OS_TICK   )10,                     //如果这个参数设置为0就一直等待下去
             (OS_OPT    )OS_OPT_PEND_BLOCKING,  //如果没有信号量可用就等待
             (CPU_TS   *)&TsOfPost,             //这个参数是指向存放信号量被提交、强制解除等待状态、或者信号量被删除的时间戳        
             (OS_ERR   *)&err);
		if(err!=OS_ERR_NONE)					//很可能超时了，由中断脚在系统初始时就为低造成的，读取传感器就可以了。
		{
			sensor.Update();
		}
		math::Vector3 acc=sensor.Get_RawAcc();
		if(cnt>=10)
		{
			cnt = 0;
			OS_CRITICAL_ENTER();									//进入临界区
			Debug_dat(3,(int)acc[0],(int)acc[1],(int)acc[2]);
			LED3 = !LED3;
			OS_CRITICAL_EXIT();										//退出临界区
		}
		else{
			cnt++;
		}
			
//		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //延时1s
	}
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

