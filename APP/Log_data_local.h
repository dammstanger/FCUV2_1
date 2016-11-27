/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Log_data_local.h
 * 描	述	：本地SD卡数据记录
 *                    
 * 实验平台	：FCUV2
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：V1.0.0
 * 创建时间	：2016.11.25
 * 最后编辑	：2016.11.25
 **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************/
#ifndef __LOG_DATA_LOCAL_H_
#define __LOG_DATA_LOCAL_H_	
/****************************包含头文件*******************************************/
#include "sys.h"
#include "sys_code_ctl.h"
#include "ff.h"
#include "string"

using namespace std;

//存储类型
#define TYPE_IMU				0x01
#define TYPE_MAG				0x02
#define TYPE_OPTF				0x04
#define TYPE_PRESS				0x08
#define TYPE_SONAR				0x10

//最大缓存采集数
#define IMU_MAX_cnt				10		//最大缓存采集数
#define MAG_MAX_cnt				10
#define OPTF_MAX_cnt			10
#define PRESS_MAX_cnt			20
#define SONAR_MAX_cnt			20

//采样间隔数
#define IMU_Sampintvl			2		//采样间隔数		0表示无间隔
#define MAG_Sampintvl			2
#define OPTF_Sampintvl			0
#define PRESS_Sampintvl			0
#define SONAR_Sampintvl			0
/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类定义*********************************************/

class Logdata
{
	public:
		FATFS *fs;			//逻辑磁盘工作区.	 
		FIL *file;	  		//文件1
		UINT br,bw;			//读写变量
		FILINFO fileinfo;	//文件信息
		DIR dir;  			//目录	
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










