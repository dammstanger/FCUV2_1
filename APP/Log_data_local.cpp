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

//#include <string.h>
/****************************��������*********************************************/

/****************************��������*********************************************/

/****************************�������*******************************************/
FATFS Workspace_1;
FIL Filestc_1;
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



u8 Logdata::Fsys_Logdat(const TCHAR* path,const char* dat,u16 datlenth)
{
	u8 ret;
	//���������ļ�������д
	ret=f_open(file,path,FA_WRITE|FA_OPEN_ALWAYS);
	if(ret==FR_OK)
	{	
//		Debug_log("succeeded open!\r\n");
		//��λ���ļ���β ������ļ�����ں���д���������һ�䣬����Ḳ�ǿ�ʼ����
		ret = f_lseek(file,file->fsize);
		if(ret)
		{
			Debug_log("file seek failed,error:%d .\r\n",ret);
			goto file_close;
		}
		
		//д����
		ret=f_write(file,dat,datlenth,&bw);		
		
		if(ret||bw!=datlenth)
		{
			Debug_log("write file failed!error:%d,setnum:%d, realnum:%d.\r\n",ret,datlenth,bw);
		}
//		else
//			Debug_log("write file succeed!\r\n");
		
file_close:ret = f_close(file);
		if(ret)
		{	
			Debug_log("file closed failed! error:%d \r\n",ret);
			return ret;
		}
	}
	else Debug_log("open failed error:%d \r\n",ret);
	return ret;
}


////num:�������ݵĸ������ڿɱ�����ĵ�һ��
////�����������ͣ�int

//bool Logdata::Cov_Storedat(const u8 type,...)
//{
//	va_list arg_ptr;
//	u8 cnt;					
//	
//	
//	va_start(arg_ptr,type);			//��ȡ��һ�������ĵ�ַ�������arg_ptr
//	switch(type)
//	{
//		case TYPE_IMU:{
//			int dat[7];
//			int lenth = 29;
//			dat[0] = va_arg(arg_ptr,int);//ÿ�ε���va_arg�����޸��ö���arg_ptr���Ӷ�ʹ�ö���ָ������б��е���һ������
//			dat[1] = va_arg(arg_ptr,int);
//			dat[2] = va_arg(arg_ptr,int);
//			dat[3] = va_arg(arg_ptr,int);
//			dat[4] = va_arg(arg_ptr,int);
//			dat[5] = va_arg(arg_ptr,int);
//			dat[6] = va_arg(arg_ptr,int);
//			
//			string str;
//			sprintf(str,"%d\r%d\r%d\r%d\r%d\r%d\r%d\r\n",dat[0],dat[1],dat[2],dat[3],dat[4],dat[5],dat[6]);
//			strcat(datbuf[0],p);
//		}
//		break;	//
//		case TYPE_MAG:cnt=4;break;
//		case TYPE_OPTF:cnt=4;break;
//		case TYPE_PRESS:
//		case TYPE_SONAR:cnt=2;break;
//		default:break;
//	}
//	
//	
//	return ;
//}



/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/










