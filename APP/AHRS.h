/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：AHRS.H
 * 描	述	：航姿参考系统类
 *                    
 * 实验平台	：
 * 硬件连接	：
 * 版 	本	：
 * 从属关系	：
 * 库版本	：
 * 创建时间	：2016.9.28
 * 最后编辑	：2016.9.28
  **-------------------------------------------------------------------------------

 * 作	者	：Damm Stanger
 * 邮	箱	：dammstanger@qq.com
**********************************************************************************************/

#ifndef __AHRS_H_
#define __AHRS_H_

/****************************包含头文件*******************************************/

#include "stm32f4xx.h"
#include "Sensor.h"
#include "Quaternion.h"
/****************************宏定义***********************************************/
typedef struct {
	Vector3 att_euler;
	Vector3 angvel;
}AHRSstrc;

class AHRS{
	public :
		
	private :
		void Quaterion_CF(Vector3 gyro,Vector3 acc,float T);
		AHRSstrc ahrs_dat;
		
		
};

#endif
/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

