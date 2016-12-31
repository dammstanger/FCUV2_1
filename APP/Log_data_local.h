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
#define LOG_IMU_RDY					0x01
#define LOG_MAG_RDY					0x02
#define LOG_OPTF_RDY				0x04
#define LOG_PRESS_RDY				0x08
#define LOG_SONAR_RDY				0x10

//���������
#define IMU_Sampintvl			10		//���������		0��ʾ�޼��
#define MAG_Sampintvl			0
#define OPTF_Sampintvl			0
#define PRESS_Sampintvl			0
#define SONAR_Sampintvl			0

//һ������ַ�������Ԥ��
#define STRINGLEN_MAX			112

//�����С
#define CACHE_SIZE				612
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
		char* datbuf;		//���ݻ���ָ��
		u16 datbuf_used;		//��������
		u16 datbuf_valib;
		u8 logdat_sta;
		Logdata():datbuf_used(0),datbuf_valib(CACHE_SIZE),logdat_sta(0) //:IMUcnt(0),MAGcnt(0),OPTFcnt(0),PRESScnt(0),SONARcnt(0)
		{
			datbuf = new char[CACHE_SIZE];
		}
		~Logdata()
		{
			delete[]datbuf;
		}
			
		u8 Fsys_Init(FATFS* workspace,FIL* filestc);
			
		u8 Fsys_Getfree(u32 *total,u32 *free);
			
		u8 Fsys_Logdat(const TCHAR* path,const char* dat,u16 datlenth);
		
		void Datbuf_IMUdataCov(int time,int ax,int ay,int az,int gx,int gy,int gz);
		void Datbuf_OPTFdataCov(int time,int x,int y,int qual);
		void Datbuf_MagdataCov(int time,int mx,int my,int mz);
		void Datbuf_PrssdataCov(int time,int p);
		void Datbuf_SonardataCov(int time,u16 h);
		void Datbuf_SpaceChk();

		void Datbuf_Store(char* dat);
		void Datbuf_Reset();
		
		void GetDataRdySta(const u8 sta);
	private:
		
//		u8 IMUcnt ;
//		u8 MAGcnt ;
//		u8 OPTFcnt ;
//		u8 PRESScnt ;
//		u8 SONARcnt ;
	
};

extern Logdata logdat;
extern FATFS Workspace_1;
extern FIL Filestc_1;
	 
#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










