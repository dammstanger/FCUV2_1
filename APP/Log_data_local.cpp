/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Log_data_local.cpp
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
**********************************************************************************************/

/****************************包含头文件*******************************************/
#include "Log_data_local.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类对象定义*******************************************/
//在ZI-data区，不会放在Flash中，区别于RW-data
FATFS Workspace_1;		//磁盘文件系统数据结构
FIL Filestc_1;			//目标文件结构体

Logdata logdat;
/****************************函数声明*********************************************/

u8 Logdata::Fsys_Init(FATFS* workspace,FIL* filestc)
{
	u8 ret=0;
	
	fs=workspace;			//为磁盘i工作区申请内存	
	if(fs==NULL)return 0xff;
	
	file=filestc;			//为file申请内存

	if(file==NULL)return 0xff;  //申请有一个失败,即失败.		
	
	ret = f_mount(fs,"0:",1); 	//挂载SD卡 
	if(ret==0)
		Debug_log("Fat mount SDcard OK!\r\n");
	else
		Debug_log("Fat mount SDcard failed!\r\n");
	
	return ret;
}


//得到磁盘剩余容量
//drv:磁盘编号("0:"/"1:")
//total:总容量	 （单位KB）
//free:剩余容量	 （单位KB）
//返回值:0,正常.其他,错误代码
u8 Logdata::Fsys_Getfree(u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
    u32 fre_clust=0, fre_sect=0, tot_sect=0;
    //得到磁盘信息及空闲簇数量
    res =(u32)f_getfree("0", (DWORD*)&fre_clust, &fs1);
    if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//得到总扇区数
	    fre_sect=fre_clust*fs1->csize;			//得到空闲扇区数	   
#if _MAX_SS!=512				  				//扇区大小不是512字节,则转换为512字节
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	//单位为KB
		*free=fre_sect>>1;	//单位为KB 
 	}
	return res;
}	

//根据路径创建并打开文件，如果文件已存在，则创建新的文件，名称为指定名称加序号：如data,data1.... 不用加后缀，默认txt
//
u8 Logdata::Fsys_Openfile(const TCHAR* path)
{
	u8 ret;
	char path_new[20];
	u8 num = 0;
	sprintf(path_new,"%s.txt",path);
	
	//创建打开文件，允许写
	do{
		ret = f_open(file,path_new,FA_WRITE|FA_CREATE_NEW);
		if(ret==FR_EXIST)
		{
			 Debug_log("file %s is already exist!\r\n",path_new);
			 sprintf(path_new,"%s%d.txt",path,++num);			//在指定名称基础上附加尾号
			if(num==0) break;									//已溢出,退出while
		}
	}while(ret==FR_EXIST);
	
	return ret;
}


//对文件写入数据，一定用在文件已打开的情况下，且默认对当前打开的文件写入
u8 Logdata::Fsys_Logdat(const char* dat,u16 datlenth)
{
	u8 ret;

//		//定位到文件结尾 如果打开文件后接在后面写，则加上这一句，否则会覆盖开始数据
//		ret = f_lseek(file,file->fsize);
//		if(ret)
//		{
//			Debug_log("file seek failed,error:%d .\r\n",ret);
//			goto file_close;
//		}
		
		//写数据
		ret=f_write(file,dat,datlenth,&bw);		
		
		if(ret||bw!=datlenth)
		{
			Debug_log("write file failed!error:%d,setnum:%d, realnum:%d.\r\n",ret,datlenth,bw);
		}
		else
			Debug_log("write file succeed!\r\n");
		
		ret = f_sync(file);			//刷新缓存
		if(ret)
		{	
			Debug_log("file sync failed! error:%d \r\n",ret);
			return ret;
		}
	return ret;
}

//关闭文件
u8 Logdata::Fsys_Closefile()
{
	u8 ret = f_close(file);			//关闭文件
	if(ret)
	{	
		Debug_log("file closed failed! error:%d \r\n",ret);
		return ret;
	}
	return ret;
}

//数据转换
void Logdata::Datbuf_IMUdataCov(u32 time,int ax,int ay,int az,int gx,int gy,int gz)
{
		char str[50];	
		logdat_sta &= ~LOG_IMU_RDY;
		sprintf(str,"%d\t%d\t%d\t%d\t%d\t%d\t%d\t",time,ax,ay,az,gx,gy,gz);
//		Debug_log("inner: %s,%d \r\n",str,strlen(str));	
		strcat(datbuf,str);
}


void Logdata::Datbuf_MagdataCov(u32 time,int mx,int my,int mz)
{
	char str[30];
	if(logdat_sta&LOG_MAG_RDY)
	{
		logdat_sta &= ~LOG_MAG_RDY;
		sprintf(str,"%d\t%d\t%d\t%d\t",time,mx,my,mz);	
	}
	else
		sprintf(str,"\t\t\t\t");	
	strcat(datbuf,str);
}

void Logdata::Datbuf_OPTFdataCov(u32 time,int x,int y,int qual)
{
	char str[30];
	if(logdat_sta&LOG_OPTF_RDY)
	{
		logdat_sta &= ~LOG_OPTF_RDY;
		sprintf(str,"%d\t%d\t%d\t%d\t",time,x,y,qual);	
	}
	else
		sprintf(str,"\t\t\t\t");	
		strcat(datbuf,str);
}


void Logdata::Datbuf_PrssdataCov(u32 time,int p)
{
	char str[30];
	if(logdat_sta&LOG_PRESS_RDY)
	{
		logdat_sta &= ~LOG_PRESS_RDY;
		sprintf(str,"%d\t%d\t",time,p);	
	}
	else
		sprintf(str,"\t\t");	
		strcat(datbuf,str);
}

void Logdata::Datbuf_SonardataCov(u32 time,u16 h)
{
	char str[30];
	if(logdat_sta&LOG_SONAR_RDY)
	{
		logdat_sta &= ~LOG_SONAR_RDY;
		sprintf(str,"%d\t%d\t\r\n",time,h);
	}
	else
		sprintf(str,"\t\t\r\n");
		strcat(datbuf,str);
}

void Logdata::Datbuf_SpaceChk()
{
	datbuf_used = strlen(datbuf);
	datbuf_valib= CACHE_SIZE-datbuf_used;
}

void Logdata::Datbuf_Reset()
{
	datbuf[0] = NULL;			//第一个字符改为空
	datbuf_used = 0;
	datbuf_valib= CACHE_SIZE;
}

void Logdata::GetDataRdySta(const u8 sta)
{
	logdat_sta |= sta;
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










