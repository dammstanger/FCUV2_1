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
#include "Log_data_local.h"
/****************************变量定义*********************************************/
OS_SEM g_sem_sensor_rdy;					//传感器数据到位信号量
OS_SEM g_sem_datlog;						//数据记录触发

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
	OSSemCreate(&g_sem_datlog,(CPU_CHAR*)"DATLOG",0,&err);
	
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
	//创建Datalog任务
	OSTaskCreate((OS_TCB     *)&DATALOG_TCB,                    	// 任务控制块指针          
               (CPU_CHAR   *)"DATALOG",		                    	// 任务名称
               (OS_TASK_PTR )Task_Datalog, 	                  		// 任务代码指针
               (void       *)0,			                      	// 传递给任务的参数parg
               (OS_PRIO     )TASK_DATALOG_PRIO,			     		// 任务优先级
               (CPU_STK    *)&Datalog_Stk[0],	                	// 任务堆栈基地址
               (CPU_STK_SIZE)TASK_DATALOG_STK_SIZE_LIMIT,			// 堆栈剩余警戒线
               (CPU_STK_SIZE)TASK_DATALOG_STK_SIZE,			    	// 堆栈大小
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
//	CPU_SR_ALLOC();

	float dat[]={1.0f,2.0f,3.0f};
	math::Vector3 t(dat);
	float dat2[]={1.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,
					1.0f,0.0f,1.0f,};
	math::Matrix3 M(dat2);
	while(1)
	{
		Vector3 v=M*t;
//		OS_CRITICAL_ENTER();									//进入临界区
//		Debug_log("v=%.2f,%.2f,%.2f \n\r",v[0],v[1],v[2]);
//		OS_CRITICAL_EXIT();										//退出临界区
		LED2=0;
		OSTimeDlyHMSM(0,0,0,100,OS_OPT_TIME_HMSM_STRICT,&err); 	//延时200ms
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
//	CPU_SR_ALLOC();
	CPU_TS TsOfPost;

	static u16 cnt1 = 0;
	static u8 sampcnt = 0;
	
	//启动fatfs文件系统
	while(logdat.Fsys_Init(&Workspace_1,&Filestc_1)!=FR_OK)		//初始化文件系统，过载SD卡
	{
		Debug_log("Mount SD card failed!\r\n");	
	}
	
	u32 total,free;
	logdat.Fsys_Getfree(&total,&free);
	Debug_log("SD Total Size:%d KB\r\n",total);					//显示容量
	Debug_log("SD Free Size:%d KB\r\n",free);					//显示容量
	
	while(1)
	{
		//阻塞任务直到超时！
		OSSemPend ((OS_SEM   *)&g_sem_sensor_rdy,
				 (OS_TICK   )10,                     //如果这个参数设置为0就一直等待下去
				 (OS_OPT    )OS_OPT_PEND_BLOCKING,  //如果没有信号量可用就等待
				 (CPU_TS   *)&TsOfPost,             //这个参数是指向存放信号量被提交、强制解除等待状态、或者信号量被删除的时间戳        
				 (OS_ERR   *)&err);
		if(err!=OS_ERR_NONE)					//很可能超时了，由中断脚在系统初始时就为低造成的，读取传感器就可以了。
		{
			sensor.Update();
			Debug_log("time out!!!\r\n");
		}
//		//获取系统时间
//		OS_TICK tim = OSTimeGet(&err);

		u8 sta = sensor.Get_status();								//获取状态
		
		//数据记录对象获取数据状态
		logdat.GetDataRdySta(sta);	
		
		//清除数据更新位，表示处理过
		sensor.Clear_status(ALL_RDY);
		
		if(sta&IMU_RDY)												//采样计数
			sampcnt++;
		
		if(sampcnt==IMU_Sampintvl&&cnt1<500)						//所以数据的记录以IMU数据的周期*10为标准，IMU数据更新最快
		{
			sampcnt = 0;
			cnt1++;
			//发送信号量
			OSSemPost ((OS_SEM  *)&g_sem_datlog,(OS_OPT)OS_OPT_POST_ALL,(OS_ERR  *)&err);
		}
			
//		if(sta&PRESS_RDY)
//		{
//			OS_CRITICAL_ENTER();									//进入临界区
//			Debug_dat(1,tim);
//			Debug_dat(6,(int)sta,(int)opt.quality,(int)opt.dx,(int)opt.dy,(int)press,(int)dist);
//			Debug_dat(6,(int)sta,(int)tim_imu,(int)tim_mag,(int)tim_opt,(int)tim_prss,(int)tim_sonar);
//			OS_CRITICAL_EXIT();										//退出临界区
//		}
	}//end of while(1)
}


/*  函数名：Task_Datalog
	功  能：数据记录
*/
void Task_Datalog(void *p_arg)
{
	OS_ERR err;
	CPU_TS TsOfPost;
	
	static u32 tim_imu_l = 0;
	static u32 tim_mag_l = 0;
	static u32 tim_opt_l = 0;
	static u32 tim_prss_l = 0;
	static u32 tim_sonar_l = 0;

	Debug_log("first log data!\r\n");
	
	//新建记录文件，不用加后缀，默认txt
	u8 ret = logdat.Fsys_Openfile("IMU");				
	if(ret) Debug_log("Creat file error:%d!\r\n",ret);
	
	while(1)
	{
		//阻塞任务直到超时！
		OSSemPend ((OS_SEM   *)&g_sem_datlog,
				 (OS_TICK   )100,                     //10ms如果这个参数设置为0就一直等待下去
				 (OS_OPT    )OS_OPT_PEND_BLOCKING,  //如果没有信号量可用就等待
				 (CPU_TS   *)&TsOfPost,             //这个参数是指向存放信号量被提交、强制解除等待状态、或者信号量被删除的时间戳        
				 (OS_ERR   *)&err);
		if(err!=OS_ERR_NONE)					    //很可能超时了，由中断脚在系统初始时就为低造成的，读取传感器就可以了。
		{
			Debug_log("sem_wait error!!!\r\n");
			if(logdat.file->fs!=NULL)				//关闭只执行一次，关闭后文件指针=NULL
			{
				Debug_log("close file!!!\r\n");
				logdat.Fsys_Closefile();	
			}
		}
		else{
			math::Vector3 accraw=sensor.Get_RawAcc();
	//		accraw*=MPU_ACC_mps2;		//转换到m/s^2
	//		accraw *=100.0f;			//放大100倍
			math::Vector3 gyroraw=sensor.Get_RawGyro();
	//		gyroraw*=MPU_GYRO_dps;		//转换到deg/s
	//		gyroraw *=100.0f;			//放大100倍
			math::Vector3 magraw=sensor.Get_RawMag();
	//		magraw.normalized();
	//		magraw *=100.0f;			//放大100倍

			OPTFLW opt=sensor.Get_Optflw_Raw();
			int press = (int)sensor.Get_AbsAlt();
			int dist = sensor.Get_RelaAlt_mm();
			
			u32 tim_imu = sensor.Get_IMU_Timp_ms();
			u32 tim_mag = sensor.Get_MAG_Timp_ms();
			u32 tim_opt = sensor.Get_ADNS_Timp_ms();
			u32 tim_prss= sensor.Get_MS5611_Timp_ms();
			u32 tim_sonar=sensor.Get_SR04_Timp_ms();
			
			if(logdat.datbuf_valib<STRINGLEN_MAX)							//可用缓存小于一次采集生成的数据字符串最大长度
			{
				
//				Debug_log("valib:%d ,Log data!\r\n",logdat.datbuf_valib);
				
				ret = logdat.Fsys_Logdat(logdat.datbuf,logdat.datbuf_used);					//录入数据
				if(ret)
				{
					Debug_log("Log data error:%d !\r\n",ret);
				}
				logdat.Datbuf_Reset();										//复位缓存				
//				Debug_log("after reset buf Size:%d KB\r\n",strlen(logdat.datbuf));
				
			}
			
			//数据转成字符串存入缓存Datbuf
			logdat.Datbuf_IMUdataCov((int)tim_imu,(int)accraw[0],(int)accraw[1],(int)accraw[2],(int)gyroraw[0],(int)gyroraw[1],(int)gyroraw[2]);
			
			logdat.Datbuf_MagdataCov((int)tim_mag,(int)magraw[0],(int)magraw[1],(int)magraw[2]);
			
			logdat.Datbuf_OPTFdataCov((int)tim_opt,opt.dx,opt.dy,opt.quality);
			
			logdat.Datbuf_PrssdataCov((int)tim_prss,press);
			
			logdat.Datbuf_SonardataCov((int)tim_sonar,dist);			//
			
			//检查缓存使用情况
			logdat.Datbuf_SpaceChk();								

//			Debug_log("buf Size:%d.\r\n",logdat.datbuf_used);
			LED3 = !LED3;	
			Debug_log("%d. %d. %d. %d. %d\r\n",tim_imu,tim_mag,tim_opt,tim_prss,tim_sonar);
//			Debug_dat(6,(int)logdat.logdat_sta,(int)(tim_imu - tim_imu_l),(int)(tim_mag - tim_mag_l),(int)(tim_opt - tim_opt_l),(int)(tim_prss - tim_prss_l),(int)(tim_sonar - tim_sonar_l));
			tim_imu_l = tim_imu;
			tim_mag_l = tim_mag;
			tim_opt_l = tim_opt;
			tim_prss_l = tim_prss;
			tim_sonar_l = tim_sonar;
		}//end of else
	}//end of while(1)
}



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

