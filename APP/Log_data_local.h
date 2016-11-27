/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Log_data_local.h
 * ��	��	������SD�����ݼ�¼
 *                    
 * ʵ��ƽ̨	��FCUV2
 * Ӳ������	��
 * �� 	��	��
 * ������ϵ	��
 * ��汾	��V1.0.0
 * ����ʱ��	��2016.11.25
 * ���༭	��2016.11.25
 **-------------------------------------------------------------------------------

 * ��	��	��Damm Stanger
 * ��	��	��dammstanger@qq.com
**********************************************************************************/
#ifndef __LOG_DATA_LOCAL_H_
#define __LOG_DATA_LOCAL_H_	
/****************************����ͷ�ļ�*******************************************/
#include "sys.h"
#include "sys_code_ctl.h"
#include "ff.h"
#include "string"

using namespace std;

//�洢����
#define TYPE_IMU				0x01
#define TYPE_MAG				0x02
#define TYPE_OPTF				0x04
#define TYPE_PRESS				0x08
#define TYPE_SONAR				0x10

//��󻺴�ɼ���
#define IMU_MAX_cnt				10		//��󻺴�ɼ���
#define MAG_MAX_cnt				10
#define OPTF_MAX_cnt			10
#define PRESS_MAX_cnt			20
#define SONAR_MAX_cnt			20

//���������
#define IMU_Sampintvl			2		//���������		0��ʾ�޼��
#define MAG_Sampintvl			2
#define OPTF_Sampintvl			0
#define PRESS_Sampintvl			0
#define SONAR_Sampintvl			0
/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�ඨ��*********************************************/

class Logdata
{
	public:
		FATFS *fs;			//�߼����̹�����.	 
		FIL *file;	  		//�ļ�1
		UINT br,bw;			//��д����
		FILINFO fileinfo;	//�ļ���Ϣ
		DIR dir;  			//Ŀ¼	
		string datbuf[5];
	
		Logdata():IMUcnt(0),MAGcnt(0),OPTFcnt(0),PRESScnt(0),SONARcnt(0)
		{
			
		}
		~Logdata(){}
			
		u8 Fsys_Init(FATFS* workspace,FIL* filestc);
			
		u8 Fsys_Getfree(u32 *total,u32 *free);
			
		bool Cov_Storedat(const u8 type,...);
			
		u8 Fsys_Logdat(const TCHAR* path,const char* dat,u16 datlenth);
			
	private:
		u8 IMUcnt ;
		u8 MAGcnt ;
		u8 OPTFcnt ;
		u8 PRESScnt ;
		u8 SONARcnt ;
	
};

extern Logdata logdat;
extern FATFS Workspace_1;
extern FIL Filestc_1;
	 
#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










