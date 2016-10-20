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
	CPU_SR_ALLOC();
//		for(ts=0;ts<10;ts++)
//		{				
////			tmp = fsmc.Read32b(ts);
////			USART1_Sendbyte(tmp>>8);
////			USART1_Sendbyte(tmp);         					//�򴮿�1��������
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
		OS_CRITICAL_ENTER();									//�����ٽ���
		Debug_log("opt:%d,%d,%x,%x.\r\n",opt.dx,opt.dy,opt.motion,opt.quality);
		Debug_log("alt:%d mm.\r\n",alt);
		Debug_log("imu_tmp: %.4f\r\n",imu_tmp);
		
		Debug_log("press: %f\r\n",press);
		OS_CRITICAL_EXIT();										//�˳��ٽ���
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
		//��������ֱ�����������£�
		OSSemPend ((OS_SEM   *)&g_sem_sensor_rdy,
             (OS_TICK   )10,                     //��������������Ϊ0��һֱ�ȴ���ȥ
             (OS_OPT    )OS_OPT_PEND_BLOCKING,  //���û���ź������þ͵ȴ�
             (CPU_TS   *)&TsOfPost,             //���������ָ�����ź������ύ��ǿ�ƽ���ȴ�״̬�������ź�����ɾ����ʱ���        
             (OS_ERR   *)&err);
		if(err!=OS_ERR_NONE)					//�ܿ��ܳ�ʱ�ˣ����жϽ���ϵͳ��ʼʱ��Ϊ����ɵģ���ȡ�������Ϳ����ˡ�
		{
			sensor.Update();
		}
		math::Vector3 acc=sensor.Get_RawAcc();
		if(cnt>=10)
		{
			cnt = 0;
			OS_CRITICAL_ENTER();									//�����ٽ���
			Debug_dat(3,(int)acc[0],(int)acc[1],(int)acc[2]);
			LED3 = !LED3;
			OS_CRITICAL_EXIT();										//�˳��ٽ���
		}
		else{
			cnt++;
		}
			
//		OSTimeDlyHMSM(0,0,1,0,OS_OPT_TIME_HMSM_STRICT,&err); //��ʱ1s
	}
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

