/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------�ļ���Ϣ----------------------------------------------------------
 * �ļ���	��Log_data_local.cpp
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
**********************************************************************************************/

/****************************����ͷ�ļ�*******************************************/
#include "Log_data_local.h"
#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�������*******************************************/
//��ZI-data�����������Flash�У�������RW-data
FATFS Workspace_1;		//�����ļ�ϵͳ���ݽṹ
FIL Filestc_1;			//Ŀ���ļ��ṹ��

Logdata logdat;
/****************************��������*********************************************/

u8 Logdata::Fsys_Init(FATFS* workspace,FIL* filestc)
{
	u8 ret=0;
	
	fs=workspace;			//Ϊ����i�����������ڴ�	
	if(fs==NULL)return 0xff;
	
	file=filestc;			//Ϊfile�����ڴ�

	if(file==NULL)return 0xff;  //������һ��ʧ��,��ʧ��.		
	
	ret = f_mount(fs,"0:",1); 	//����SD�� 
	if(ret==0)
		Debug_log("Fat mount SDcard OK!\r\n");
	else
		Debug_log("Fat mount SDcard failed!\r\n");
	
	return ret;
}


//�õ�����ʣ������
//drv:���̱��("0:"/"1:")
//total:������	 ����λKB��
//free:ʣ������	 ����λKB��
//����ֵ:0,����.����,�������
u8 Logdata::Fsys_Getfree(u32 *total,u32 *free)
{
	FATFS *fs1;
	u8 res;
    u32 fre_clust=0, fre_sect=0, tot_sect=0;
    //�õ�������Ϣ�����д�����
    res =(u32)f_getfree("0", (DWORD*)&fre_clust, &fs1);
    if(res==0)
	{											   
	    tot_sect=(fs1->n_fatent-2)*fs1->csize;	//�õ���������
	    fre_sect=fre_clust*fs1->csize;			//�õ�����������	   
#if _MAX_SS!=512				  				//������С����512�ֽ�,��ת��Ϊ512�ֽ�
		tot_sect*=fs1->ssize/512;
		fre_sect*=fs1->ssize/512;
#endif	  
		*total=tot_sect>>1;	//��λΪKB
		*free=fre_sect>>1;	//��λΪKB 
 	}
	return res;
}	

//����·�����������ļ�������ļ��Ѵ��ڣ��򴴽��µ��ļ�������Ϊָ�����Ƽ���ţ���data,data1.... ���üӺ�׺��Ĭ��txt
//
u8 Logdata::Fsys_Openfile(const TCHAR* path)
{
	u8 ret;
	char path_new[20];
	u8 num = 0;
	sprintf(path_new,"%s.txt",path);
	
	//�������ļ�������д
	do{
		ret = f_open(file,path_new,FA_WRITE|FA_CREATE_NEW);
		if(ret==FR_EXIST)
		{
			 Debug_log("file %s is already exist!\r\n",path_new);
			 sprintf(path_new,"%s%d.txt",path,++num);			//��ָ�����ƻ����ϸ���β��
			if(num==0) break;									//�����,�˳�while
		}
	}while(ret==FR_EXIST);
	
	return ret;
}


//���ļ�д�����ݣ�һ�������ļ��Ѵ򿪵�����£���Ĭ�϶Ե�ǰ�򿪵��ļ�д��
u8 Logdata::Fsys_Logdat(const char* dat,u16 datlenth)
{
	u8 ret;

//		//��λ���ļ���β ������ļ�����ں���д���������һ�䣬����Ḳ�ǿ�ʼ����
//		ret = f_lseek(file,file->fsize);
//		if(ret)
//		{
//			Debug_log("file seek failed,error:%d .\r\n",ret);
//			goto file_close;
//		}
		
		//д����
		ret=f_write(file,dat,datlenth,&bw);		
		
		if(ret||bw!=datlenth)
		{
			Debug_log("write file failed!error:%d,setnum:%d, realnum:%d.\r\n",ret,datlenth,bw);
		}
		else
			Debug_log("write file succeed!\r\n");
		
		ret = f_sync(file);			//ˢ�»���
		if(ret)
		{	
			Debug_log("file sync failed! error:%d \r\n",ret);
			return ret;
		}
	return ret;
}

//�ر��ļ�
u8 Logdata::Fsys_Closefile()
{
	u8 ret = f_close(file);			//�ر��ļ�
	if(ret)
	{	
		Debug_log("file closed failed! error:%d \r\n",ret);
		return ret;
	}
	return ret;
}

//����ת��
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
	datbuf[0] = NULL;			//��һ���ַ���Ϊ��
	datbuf_used = 0;
	datbuf_valib= CACHE_SIZE;
}

void Logdata::GetDataRdySta(const u8 sta)
{
	logdat_sta |= sta;
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










