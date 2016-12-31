/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��FCU_app.cpp
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

/****************************����ͷ�ļ�*******************************************/
#include "includes.h"
#include "FCU_app.h"
#include "usart.h"
#include "FSMC.h"
#include "led.h"
#include "cpp_Math.h"
#include "Sensor.h"
#include "Log_data_local.h"
/****************************��������*********************************************/
OS_SEM g_sem_sensor_rdy;

//  ��������Task_Start
//	��  �ܣ�������������ϵͳ�ĸ���ģ�顣
void Task_Start(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();			//����жϵı���
	p_arg = p_arg;
	
	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif

#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	

	//�����ź���
	OSSemCreate(&g_sem_sensor_rdy,(CPU_CHAR*)"SENS_RDY",0,&err);
	//�����ٽ���
	OS_CRITICAL_ENTER();	
	//����LED����
	OSTaskCreate((OS_TCB     *)&LED_TCB,                    	// ������ƿ�ָ��          
               (CPU_CHAR   *)"LED",		                    	// ��������
               (OS_TASK_PTR )Task_LED, 	                  		// �������ָ��
               (void       *)0,			                      	// ���ݸ�����Ĳ���parg
               (OS_PRIO     )TASK_LED_PRIO,			     		// �������ȼ�
               (CPU_STK    *)&LED_Stk[0],	                	// �����ջ����ַ
               (CPU_STK_SIZE)TASK_LED_STK_SIZE_LIMIT,			// ��ջʣ�ྯ����
               (CPU_STK_SIZE)TASK_LED_STK_SIZE,			    	// ��ջ��С
               (OS_MSG_QTY  )0,			                      	// �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      	// ʱ��Ƭ��תʱ��
               (void       *)0,			                      	// ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// ����ѡ��
               (OS_ERR     *)&err);		                    	// ����ֵ
//	//����Sensor_Process����
	OSTaskCreate((OS_TCB     *)&SENSOR_PRO_TCB,                 // ������ƿ�ָ��          
               (CPU_CHAR   *)"SENSOR_PRO",		                // ��������
               (OS_TASK_PTR )Task_SENSOR_PRO, 	                // �������ָ��
               (void       *)0,			                      	// ���ݸ�����Ĳ���parg
               (OS_PRIO     )TASK_SENSOR_PRO_PRIO,			    // �������ȼ�
               (CPU_STK    *)&SENSOR_PRO_Stk[0],	            // �����ջ����ַ
               (CPU_STK_SIZE)TASK_SENSOR_PRO_STK_SIZE_LIMIT,	// ��ջʣ�ྯ����
               (CPU_STK_SIZE)TASK_SENSOR_PRO_STK_SIZE,			// ��ջ��С
               (OS_MSG_QTY  )0,			                      	// �ɽ��յ������Ϣ������
               (OS_TICK     )0,			                      	// ʱ��Ƭ��תʱ��
               (void       *)0,			                      	// ������ƿ���չ��Ϣ
               (OS_OPT      )(OS_OPT_TASK_STK_CHK | 
                              OS_OPT_TASK_STK_CLR),	      		// ����ѡ��
               (OS_ERR     *)&err);		                    	// ����ֵ
	//�˳��ٽ���
	OS_CRITICAL_EXIT();	
	//����ɾ���Լ�	
	OSTaskDel(&START_TCB,&err);							 
}




/*  ��������Task_LED
	��  �ܣ�LED����
*/
void Task_LED(void *p_arg)
{
	OS_ERR err;
//	CPU_SR_ALLOC();
//	u8 ret;
	
//	//����fatfs�ļ�ϵͳ
//	ret = logdat.Fsys_Init(&Workspace_1,&Filestc_1);				//��ʼ���ļ�ϵͳ������SD��
//	if(ret==FR_OK)
//	{
//		u32 total,free;
//		logdat.Fsys_Getfree(&total,&free);
//		Debug_log("SD Total Size:%d KB\r\n",total);					//��ʾ����
//		Debug_log("SD Free Size:%d KB\r\n",free);					//��ʾ����
//		
//		char tmp[]= "125\t124\t125\r\n123.2\t124.56789\t125.1\r\n";
//		u8 len = strlen(tmp);
//		Debug_log("String length:%d \r\n",len);
//		logdat.Fsys_Logdat("IMU.txt",tmp,len);
//	}
//	else
//	{
//		Debug_log("file system failed,error: %d \r\n",ret);
//	}

	
//	static u16 pwm=0;
	float dat[]={1.0f,2.0f,3.0f};
	math::Vector3 t(dat);
	float dat2[]={1.0f,1.0f,0.0f,
					0.0f,1.0f,0.0f,
					1.0f,0.0f,1.0f,};
	math::Matrix3 M(dat2);
	while(1)
	{
		Vector3 v=M*t;
//		OS_CRITICAL_ENTER();									//�����ٽ���
//		Debug_log("v=%.2f,%.2f,%.2f \n\r",v[0],v[1],v[2]);
//		OS_CRITICAL_EXIT();										//�˳��ٽ���
		LED2=0;
		OSTimeDlyHMSM(0,0,0,200,OS_OPT_TIME_HMSM_STRICT,&err); 	//��ʱ200ms
		LED2=1;
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_HMSM_STRICT,&err); 	//��ʱ500ms
	}
}

/*  ��������Task_SENSOR_PRO
	��  �ܣ����������ݴ���
*/
void Task_SENSOR_PRO(void *p_arg)
{
	OS_ERR err;
//	CPU_SR_ALLOC();
	CPU_TS TsOfPost;

	static u8 cnt = 0;
	static u16 cnt1= 0;
	static u8 sampcnt = 0;
	
	//����fatfs�ļ�ϵͳ
	while(logdat.Fsys_Init(&Workspace_1,&Filestc_1)!=FR_OK)		//��ʼ���ļ�ϵͳ������SD��
	{
		Debug_log("Mount SD card failed!\r\n");	
	}
	
	u32 total,free;
	logdat.Fsys_Getfree(&total,&free);
	Debug_log("SD Total Size:%d KB\r\n",total);					//��ʾ����
	Debug_log("SD Free Size:%d KB\r\n",free);					//��ʾ����
	
	while(1)
	{
		//��������ֱ�����������£�
		OSSemPend ((OS_SEM   *)&g_sem_sensor_rdy,
				 (OS_TICK   )10,                     //��������������Ϊ0��һֱ�ȴ���ȥ
				 (OS_OPT    )OS_OPT_PEND_BLOCKING,  //���û���ź������þ͵ȴ�
				 (CPU_TS   *)&TsOfPost,             //���������ָ�����ź������ύ��ǿ�ƽ���ȴ�״̬�������ź�����ɾ����ʱ���        
				 (OS_ERR   *)&err);
		if(err!=OS_ERR_NONE)					//�ܿ��ܳ�ʱ�ˣ����жϽ���ϵͳ��ʼʱ��Ϊ����ɵģ���ȡ�������Ϳ����ˡ�
		{
			sensor.Update();
			Debug_log("time out!!!\r\n");
		}
		
		math::Vector3 accraw=sensor.Get_RawAcc();
		accraw*=MPU_ACC_mps2;		//ת����m/s^2
		accraw *=100.0f;			//�Ŵ�100��
		math::Vector3 gyroraw=sensor.Get_RawGyro();
		gyroraw*=MPU_GYRO_dps;		//ת����deg/s
		gyroraw *=100.0f;			//�Ŵ�100��
		math::Vector3 magraw=sensor.Get_RawMag();
//		magraw.normalized();
//		magraw *=100.0f;			//�Ŵ�100��
		
		OPTFLW opt=sensor.Get_Optflw_Raw();
		int press = (int)sensor.Get_AbsAlt();
		int dist = sensor.Get_RelaAlt_mm();
		
		u32 tim_imu = sensor.Get_ADNS_Timp_ms();
		u32 tim_mag = sensor.Get_MAG_Timp_us();
		u32 tim_opt = sensor.Get_ADNS_Timp_ms();
		u32 tim_prss= sensor.Get_MS5611_Timp_ms();
		u32 tim_soner=sensor.Get_SR04_Timp_ms();

		u8 sta = sensor.Get_status();								//��ȡ״̬
//		printf("A:%d, %d\r\n\n",g_STA,sta);
		
		logdat.GetDataRdySta(sta);
		if(sta&IMU_RDY)												//��������
			sampcnt++;
		
		if(sampcnt==IMU_Sampintvl&&cnt1<500)									//�������ݵļ�¼��IMU���ݵ�����*2Ϊ��׼��IMU���ݸ������
		{
			sampcnt = 0;
			cnt1++;
			if(logdat.datbuf_valib<STRINGLEN_MAX)
			{
				Debug_log("valib:%d ,Log data!\r\n",logdat.datbuf_valib);
				logdat.Fsys_Logdat("IMU.txt",logdat.datbuf,logdat.datbuf_used);		//¼������
				logdat.Datbuf_Reset();												//��λ����
				
				Debug_log("after reset buf Size:%d KB\r\n",strlen(logdat.datbuf));
			}
			Debug_log("data ready sta:%d time:%d,%d,%d,%d,%d \r\n",logdat.logdat_sta,tim_imu,tim_mag,tim_opt,tim_prss,tim_soner);
			//
			logdat.Datbuf_IMUdataCov(1,(int)accraw[0],(int)accraw[1],(int)accraw[2],(int)gyroraw[0],(int)gyroraw[1],(int)gyroraw[2]);
			
			logdat.Datbuf_MagdataCov(2,(int)magraw[0],(int)magraw[1],(int)magraw[2]);
			
			logdat.Datbuf_OPTFdataCov(3,opt.dx,opt.dy,opt.quality);
			
			logdat.Datbuf_PrssdataCov(4,press);
			
			logdat.Datbuf_SonardataCov(5,dist);			//
			
			logdat.Datbuf_SpaceChk();								//��黺��ʹ�����
			Debug_log(" buf Size:%d.\r\n",logdat.datbuf_used);
			LED3 = !LED3;
		}

		if(cnt>=30)
		{
			cnt = 0;
			
//			OS_CRITICAL_ENTER();									//�����ٽ���
//			Debug_dat(6,(int)magraw[0],(int)magraw[1],(int)magraw[2],(int)mag[0],(int)mag[1],(int)mag[2]);
//			LED3 = !LED3;
//			OS_CRITICAL_EXIT();										//�˳��ٽ���
		}
		else{
			cnt++;
		}
			
//		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
	}
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

