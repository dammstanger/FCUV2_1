/******************** (C) COPYRIGHT 2016 DammStanger *****************************************
**--------------文件信息----------------------------------------------------------
 * 文件名	：Sensor.cpp
 * 描	述	：传感器类
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

/****************************包含头文件*******************************************/
#include "Sensor.h"
/****************************宏定义***********************************************/

/****************************变量声明*********************************************/

/****************************变量定义*********************************************/

/****************************类对象定义*********************************************/
Sensor sensor;

/****************************函数声明*********************************************/

//=======读取MPU传感器数据======================
void Sensor::MPU_AccTempGyro_Read(void)
{
	u32 tmp[7];
	fsmc.ReadBuf32(ACC_X,tmp,7);
	acc_raw[0]=(s16)tmp[0];
	acc_raw[1]=(s16)tmp[1];
	acc_raw[2]=(s16)tmp[2];
	imu_temp=(s16)tmp[3];
	gyro_raw[0]=(s16)tmp[4];
	gyro_raw[1]=(s16)tmp[5];
	gyro_raw[2]=(s16)tmp[6];
	
}

//=======读取MPU传感器数据======================
void Sensor::MPU_AccGyro_Calib(bool tempin)
{
	Vector3 acc_r;				//原始加速度矢量
	acc_r[0]=(float)acc_raw[0];
	acc_r[1]=(float)acc_raw[1];
	acc_r[2]=(float)acc_raw[2];
	
	Vector3 acc_offs(Acc_OFFS);					//
	Matrix<3,3> M_acc_sins(Acc_SINS);			//校正综合系数阵
	
	Vector3 acc_t = acc_r*MPU_ACC_mps2-acc_offs;//转换单位后，单位：m/s^2 
	
	acc = M_acc_sins*acc_t;						//校正后加速度矢量，单位m/s^2
	
	//
	Vector3 g_raw;
	g_raw[0]=(float)gyro_raw[0];
	g_raw[1]=(float)gyro_raw[1];
	g_raw[2]=(float)gyro_raw[2];

	Vector3 g_offs(Gyro_tmp_k);
	if(tempin==true)
	{
		g_offs.set(Gyro_tmp_k);					//是否可以
		g_offs = g_offs*imu_temp+Gyro_tmp_b;
		
		gyro = g_raw - g_offs;					//消除零偏
		
	}
	else{										//不考虑温度
		g_offs.set(Gyro_OFFS);					
		gyro = g_raw - g_offs;					
	}
	
}

//获取温度
//Temperature in degrees C = (TEMP_OUT Register Value as a signed quantity)/340 + 35
float Sensor::Get_IMUTemp(void)
{
	
	return imu_temp/340.0f+35;
}

//返回浮点型加计原始值
Vector3 Sensor::Get_RawAcc(void)
{
	
	Vector3 res;
	res[0]=(float)acc_raw[0];
	res[1]=(float)acc_raw[1];
	res[2]=(float)acc_raw[2];
	return res; 
}

//返回加值
Vector3 Sensor::Get_Acc(void)
{
	return acc; 
}

//返回浮点型的陀螺仪原始值
Vector3 Sensor::Get_RawGyro(void)
{
	Vector3 res;
	res[0]=(float)gyro_raw[0];
	res[1]=(float)gyro_raw[1];
	res[2]=(float)gyro_raw[2];
	return res; 
	
}

//返回角速度值
Vector3 Sensor::Get_Gyro(void)
{
	return gyro;
}

void Sensor::MPU_Mag_Read(void)
{
	u32 tmp[3];
	fsmc.ReadBuf32(MAG_X,tmp,3);
	mag_raw[0]=(s16)tmp[0];
	mag_raw[1]=(s16)tmp[1];
	mag_raw[2]=(s16)tmp[2];
}
	
/*地磁矢量校准 % 椭球方程可写为：((X-X0)'*R')*(R *(X-X0)) = 1
% 因此椭球点为：X_sphere = R *(X-X0);
% 标准圆球点为：X = inv(R)*X_sphere + X0
%   Ae = [a d e; d b f; e f c] 为椭球的形状参数
%   X0 为椭球的中心点坐标：
%   X0 = -Ae^-1/[p q r]'
*/
void Sensor::MPU_Mag_Calib(void)
{
	
	Vector3 mag_r;				//原始地磁矢量
	mag_r[0]=(float)mag_r[0];
	mag_r[1]=(float)mag_r[1];
	mag_r[2]=(float)mag_r[2];
	Vector3 mag_offs(Mag_OFFS);					//
	Matrix<3,3> M_acc_sins(Mag_SINS);			//校正综合系数阵
	
	Vector3 acc_t = M_acc_sins*mag_r;// + mag_offs;//校准到单位圆
	
	acc = acc_t.normalized();					//归一化
}

void Sensor::MS5611_Press_Read(void)
{
	
	u32 tmp = fsmc.Read32b(ALT_PRESS);
	press = tmp/100.0f;
	
}

float Sensor::Get_AbsAlt(void)
{
	return press;				//原始的press放大了100倍;
}

void Sensor::SR04_Alt_Read(void)
{
	alt_rela = fsmc.Read16b(ALT_ULTRA);
}

u16 Sensor::Get_RelaAlt_mm(void)
{
	return alt_rela;
}

void Sensor::ADNS_Read(void)
{
	u16 tmp[4];
	fsmc.ReadBuf16(OPFL_MOTION,tmp,4);
	optflw.motion = (bool)tmp[0]&0x80;			//哪一位有待查证
	optflw.quality = (u8)tmp[1];
	optflw.dx = (s8)tmp[2];
	optflw.dy = (s8)tmp[3];
}

//
//	void Sensor::Optflw_distcal(void)
//	{
//		
//	}

OPTFLW Sensor::Get_Optflw_Raw(void)
{
	return optflw;
}

u8 Sensor::Get_PicQuality(void)
{
	return optflw.quality;
}

s8 Sensor::Get_RawDx(void)
{
	return optflw.dx;
}	

s8 Sensor::Get_RawDy(void)
{
	return optflw.dy;
}


bool Sensor::Update(void)
{
	sens_sta = fsmc.Read16b(REG_STA);
	
	if(sens_sta&MIU_RDY)
	{
		MPU_AccTempGyro_Read();
	}
	if(sens_sta&MAG_RDY)
	{
		MPU_Mag_Read();
	}
	if(sens_sta&OPTF_RDY)
	{
		ADNS_Read();
	}
	if(sens_sta&ULTRS_RDY)
	{
		SR04_Alt_Read();
	}
	if(sens_sta&PRESS_RDY)
	{
		MS5611_Press_Read();
	}
	if(sens_sta>0)
		return true;
	else
		return false;
}


/******************* (C) COPYRIGHT 2016 DammStanger *****END OF FILE************/

