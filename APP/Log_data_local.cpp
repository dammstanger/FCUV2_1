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

//#include <string.h>
/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类对象定义*******************************************/
FATFS Workspace_1;
FIL Filestc_1;
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



u8 Logdata::Fsys_Logdat(const TCHAR* path,const char* dat,u16 datlenth)
{
	u8 ret;
	//创建过打开文件，允许写
	ret=f_open(file,path,FA_WRITE|FA_OPEN_ALWAYS);
	if(ret==FR_OK)
	{	
//		Debug_log("succeeded open!\r\n");
		//定位到文件结尾 如果打开文件后接在后面写，则加上这一句，否则会覆盖开始数据
		ret = f_lseek(file,file->fsize);
		if(ret)
		{
			Debug_log("file seek failed,error:%d .\r\n",ret);
			goto file_close;
		}
		
		//写数据
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


////num:调试数据的个数，在可变参数的第一个
////输入数据类型：int

//bool Logdata::Cov_Storedat(const u8 type,...)
//{
//	va_list arg_ptr;
//	u8 cnt;					
//	
//	
//	va_start(arg_ptr,type);			//获取第一个参数的地址，存放于arg_ptr
//	switch(type)
//	{
//		case TYPE_IMU:{
//			int dat[7];
//			int lenth = 29;
//			dat[0] = va_arg(arg_ptr,int);//每次调用va_arg都会修改用对象arg_ptr，从而使该对象指向参数列表中的下一个参数
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










